/*
 * Copyright (c) 2024 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_ws2812

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <string.h>

LOG_MODULE_REGISTER(ws2812, CONFIG_ZMK_LOG_LEVEL);

// Forward declaration of API structure
struct ws2812_driver_api {
    int (*set_pixel)(const struct device *dev, uint16_t index, uint8_t r, uint8_t g, uint8_t b);
    int (*update)(const struct device *dev);
    int (*clear)(const struct device *dev);
};

struct ws2812_config {
    const struct gpio_dt_spec pin;
    const struct gpio_dt_spec pin_secondary;
    bool has_secondary;
    uint16_t chain_length;
};

struct ws2812_data {
    uint8_t *pixels;
    bool initialized;
};

static int ws2812_init(const struct device *dev) {
    const struct ws2812_config *config = dev->config;
    struct ws2812_data *data = dev->data;
    
    if (!device_is_ready(config->pin.port)) {
        LOG_ERR("GPIO port not ready");
        return -ENODEV;
    }
    
    int ret = gpio_pin_configure_dt(&config->pin, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        LOG_ERR("Failed to configure GPIO pin");
        return ret;
    }

    if (config->has_secondary) {
        if (!device_is_ready(config->pin_secondary.port)) {
            LOG_ERR("Secondary GPIO port not ready");
            return -ENODEV;
        }
        ret = gpio_pin_configure_dt(&config->pin_secondary, GPIO_OUTPUT_INACTIVE);
        if (ret < 0) {
            LOG_ERR("Failed to configure secondary GPIO pin");
            return ret;
        }
    }
    
    // Allocate memory for pixel data (3 bytes per LED: RGB)
    data->pixels = k_malloc(config->chain_length * 3);
    if (!data->pixels) {
        LOG_ERR("Failed to allocate pixel buffer");
        return -ENOMEM;
    }
    
    // Initialize all LEDs to off
    memset(data->pixels, 0, config->chain_length * 3);
    data->initialized = true;
    
    LOG_INF("WS2812 initialized with %d LEDs", config->chain_length);
    return 0;
}

static int ws2812_set_pixel(const struct device *dev, uint16_t index, uint8_t r, uint8_t g, uint8_t b) {
    const struct ws2812_config *config = dev->config;
    struct ws2812_data *data = dev->data;
    
    if (!data->initialized) {
        return -ENODEV;
    }
    
    if (index >= config->chain_length) {
        return -EINVAL;
    }
    
    // Store RGB values
    data->pixels[index * 3] = r;
    data->pixels[index * 3 + 1] = g;
    data->pixels[index * 3 + 2] = b;
    
    return 0;
}

static int ws2812_update(const struct device *dev) {
    const struct ws2812_config *config = dev->config;
    struct ws2812_data *data = dev->data;
    
    if (!data->initialized) {
        return -ENODEV;
    }
    
    // Disable interrupts during transmission
    unsigned int key = irq_lock();
    
    // Send reset signal (low for 50+ microseconds)
    gpio_pin_set_dt(&config->pin, 0);
    if (config->has_secondary) {
        gpio_pin_set_dt(&config->pin_secondary, 0);
    }
    k_busy_wait(50);
    
    // Send pixel data using bit-banging
    // WS2812 timing: 0 = 400ns high + 850ns low, 1 = 800ns high + 450ns low
    for (uint16_t i = 0; i < config->chain_length * 3; i++) {
        uint8_t byte = data->pixels[i];
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (byte & 0x80) {
                // Send '1' bit
                gpio_pin_set_dt(&config->pin, 1);
                if (config->has_secondary) gpio_pin_set_dt(&config->pin_secondary, 1);
                k_busy_wait(1);  // ~800ns
                gpio_pin_set_dt(&config->pin, 0);
                if (config->has_secondary) gpio_pin_set_dt(&config->pin_secondary, 0);
                k_busy_wait(0);  // ~450ns
            } else {
                // Send '0' bit
                gpio_pin_set_dt(&config->pin, 1);
                if (config->has_secondary) gpio_pin_set_dt(&config->pin_secondary, 1);
                k_busy_wait(0);  // ~400ns
                gpio_pin_set_dt(&config->pin, 0);
                if (config->has_secondary) gpio_pin_set_dt(&config->pin_secondary, 0);
                k_busy_wait(1);  // ~850ns
            }
            byte <<= 1;
        }
    }
    
    // Send reset signal
    gpio_pin_set_dt(&config->pin, 0);
    if (config->has_secondary) {
        gpio_pin_set_dt(&config->pin_secondary, 0);
    }
    k_busy_wait(50);
    
    irq_unlock(key);
    
    return 0;
}

static int ws2812_clear(const struct device *dev) {
    const struct ws2812_config *config = dev->config;
    struct ws2812_data *data = dev->data;
    
    if (!data->initialized) {
        return -ENODEV;
    }
    
    memset(data->pixels, 0, config->chain_length * 3);
    return ws2812_update(dev);
}

// Device API structure matching the header
static const struct ws2812_driver_api ws2812_api = {
    .set_pixel = ws2812_set_pixel,
    .update = ws2812_update,
    .clear = ws2812_clear,
};

#define WS2812_DEVICE_INIT(inst)                                           \
    static const struct ws2812_config ws2812_config_##inst = {            \
        .pin = GPIO_DT_SPEC_GET(DT_DRV_INST(inst), pin),                 \
        .pin_secondary = GPIO_DT_SPEC_GET_OR(DT_DRV_INST(inst), pin_secondary, {0}), \
        .has_secondary = DT_INST_NODE_HAS_PROP(inst, pin_secondary),     \
        .chain_length = DT_INST_PROP(inst, chain_length),                \
    };                                                                     \
                                                                           \
    static struct ws2812_data ws2812_data_##inst = {                      \
        .initialized = false,                                              \
    };                                                                     \
                                                                           \
    DEVICE_DT_INST_DEFINE(inst,                                           \
                          ws2812_init,                                     \
                          NULL,                                            \
                          &ws2812_data_##inst,                            \
                          &ws2812_config_##inst,                          \
                          POST_KERNEL,                                     \
                          CONFIG_KERNEL_INIT_PRIORITY_DEVICE,              \
                          &ws2812_api);

DT_INST_FOREACH_STATUS_OKAY(WS2812_DEVICE_INIT)
