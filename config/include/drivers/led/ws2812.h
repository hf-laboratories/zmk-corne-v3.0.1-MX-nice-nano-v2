/*
 * Copyright (c) 2024 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 */

#ifndef ZEPHYR_DRIVERS_LED_WS2812_H_
#define ZEPHYR_DRIVERS_LED_WS2812_H_

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief WS2812 LED Driver API
 */

/**
 * @brief Set a single LED pixel color
 *
 * @param dev Pointer to the device structure
 * @param index LED index (0-based)
 * @param r Red value (0-255)
 * @param g Green value (0-255)
 * @param b Blue value (0-255)
 * @return 0 on success, negative errno code on failure
 */
typedef int (*ws2812_set_pixel_t)(const struct device *dev, uint16_t index,
                                  uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Update/refresh all LEDs with current pixel data
 *
 * @param dev Pointer to the device structure
 * @return 0 on success, negative errno code on failure
 */
typedef int (*ws2812_update_t)(const struct device *dev);

/**
 * @brief Clear all LEDs (turn them off)
 *
 * @param dev Pointer to the device structure
 * @return 0 on success, negative errno code on failure
 */
typedef int (*ws2812_clear_t)(const struct device *dev);

/**
 * @brief WS2812 driver API structure
 */
struct ws2812_driver_api {
    ws2812_set_pixel_t set_pixel;
    ws2812_update_t update;
    ws2812_clear_t clear;
};

/**
 * @brief Set a single LED pixel color
 *
 * @param dev Pointer to the device structure
 * @param index LED index (0-based)
 * @param r Red value (0-255)
 * @param g Green value (0-255)
 * @param b Blue value (0-255)
 * @return 0 on success, negative errno code on failure
 */
static inline int ws2812_set_pixel(const struct device *dev, uint16_t index,
                                   uint8_t r, uint8_t g, uint8_t b) {
    const struct ws2812_driver_api *api =
        (const struct ws2812_driver_api *)dev->api;
    
    if (api->set_pixel == NULL) {
        return -ENOTSUP;
    }
    
    return api->set_pixel(dev, index, r, g, b);
}

/**
 * @brief Update/refresh all LEDs with current pixel data
 *
 * @param dev Pointer to the device structure
 * @return 0 on success, negative errno code on failure
 */
static inline int ws2812_update(const struct device *dev) {
    const struct ws2812_driver_api *api =
        (const struct ws2812_driver_api *)dev->api;
    
    if (api->update == NULL) {
        return -ENOTSUP;
    }
    
    return api->update(dev);
}

/**
 * @brief Clear all LEDs (turn them off)
 *
 * @param dev Pointer to the device structure
 * @return 0 on success, negative errno code on failure
 */
static inline int ws2812_clear(const struct device *dev) {
    const struct ws2812_driver_api *api =
        (const struct ws2812_driver_api *)dev->api;
    
    if (api->clear == NULL) {
        return -ENOTSUP;
    }
    
    return api->clear(dev);
}

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_DRIVERS_LED_WS2812_H_ */
