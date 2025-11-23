/*
 * Copyright (c) 2024 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>
#include <drivers/led/ws2812.h>

#include <zmk/event_manager.h>
#include <zmk/events/activity_state_changed.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/hid.h>
#include <zmk/keymap.h>

LOG_MODULE_REGISTER(rgb_led, CONFIG_ZMK_LOG_LEVEL);

#if IS_ENABLED(CONFIG_ZMK_RGB_PER_KEY)

// RGB LED state structure
struct rgb_led_state {
    bool enabled;
    uint8_t brightness;
    uint8_t hue;
    uint8_t saturation;
    uint8_t effect;
    bool needs_update;
};

static struct rgb_led_state state = {
    .enabled = IS_ENABLED(CONFIG_ZMK_RGB_ON_START),
    // Scale config values (0-100/0-360) to driver range (0-255)
    .brightness = (CONFIG_ZMK_RGB_BRI_START * 255) / 100,
    .hue = (CONFIG_ZMK_RGB_HUE_START * 255) / 360,
    .saturation = (CONFIG_ZMK_RGB_SAT_START * 255) / 100,
    .effect = CONFIG_ZMK_RGB_EFF_START,
    .needs_update = true,
};

// Simple HSV to RGB conversion
static void hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b) {
    uint8_t region, remainder, p, q, t;
    
    if (s == 0) {
        *r = v;
        *g = v;
        *b = v;
        return;
    }
    
    region = h / 43;
    remainder = (h - (region * 43)) * 6;
    
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;
    
    switch (region) {
        case 0:
            *r = v; *g = t; *b = p;
            break;
        case 1:
            *r = q; *g = v; *b = p;
            break;
        case 2:
            *r = p; *g = v; *b = t;
            break;
        case 3:
            *r = p; *g = q; *b = v;
            break;
        case 4:
            *r = t; *g = p; *b = v;
            break;
        default:
            *r = v; *g = p; *b = q;
            break;
    }
}

#define LED_STRIP_NODE DT_NODELABEL(rgb_leds)
static const struct device *led_strip = DEVICE_DT_GET(LED_STRIP_NODE);

// Update all LEDs based on current state
static void rgb_led_update_leds(void) {
    if (!device_is_ready(led_strip)) {
        LOG_ERR("LED strip device not ready");
        return;
    }

    if (!state.enabled) {
        // Turn off all LEDs
        LOG_DBG("LEDs disabled, turning off");
        ws2812_clear(led_strip);
        return;
    }
    
    uint8_t r, g, b;
    hsv_to_rgb(state.hue, state.saturation, state.brightness, &r, &g, &b);
    
    LOG_DBG("Updating LEDs: H=%d S=%d V=%d -> R=%d G=%d B=%d", 
            state.hue, state.saturation, state.brightness, r, g, b);
    
    // Update all LEDs
    for (int i = 0; i < CONFIG_ZMK_RGB_LED_COUNT; i++) {
        ws2812_set_pixel(led_strip, i, r, g, b);
    }
    ws2812_update(led_strip);
}

// Work handler for LED updates
// ...existing code...

// Work handler for LED updates
static void rgb_led_work_handler(struct k_work *work) {
    if (state.needs_update) {
        rgb_led_update_leds();
        state.needs_update = false;
    }
}

K_WORK_DEFINE(rgb_led_work, rgb_led_work_handler);

// Event handlers
static int rgb_led_activity_event_listener(const zmk_event_t *eh) {
    const struct zmk_activity_state_changed *activity_event = as_zmk_activity_state_changed(eh);
    
    if (activity_event == NULL) {
        return 0;
    }
    
#if IS_ENABLED(CONFIG_ZMK_RGB_AUTO_OFF_IDLE)
    if (activity_event->state == ZMK_ACTIVITY_IDLE) {
        LOG_DBG("Activity idle, disabling LEDs");
        state.enabled = false;
        state.needs_update = true;
        k_work_submit(&rgb_led_work);
    } else if (activity_event->state == ZMK_ACTIVITY_ACTIVE) {
        LOG_DBG("Activity active, enabling LEDs");
        state.enabled = true;
        state.needs_update = true;
        k_work_submit(&rgb_led_work);
    }
#endif
    
    return 0;
}

static int rgb_led_keycode_event_listener(const zmk_event_t *eh) {
#if IS_ENABLED(CONFIG_ZMK_RGB_EFFECT_TYPING_HEATMAP)
    // Note: as_zmk_keycode_state_changed is not available in this ZMK version
    // Keeping this as a placeholder for future implementation
    const struct zmk_keycode_state_changed *keycode_event = as_zmk_keycode_state_changed(eh);
    
    if (keycode_event == NULL || !keycode_event->state) {
        return 0;
    }
    
    // Trigger LED update on keypress for typing effects
    state.needs_update = true;
    k_work_submit(&rgb_led_work);
#endif
    
    return 0;
}

static int rgb_led_layer_event_listener(const zmk_event_t *eh) {
#if IS_ENABLED(CONFIG_ZMK_RGB_EFFECT_LAYER_INDICATOR)
    // Note: as_zmk_layer_state_changed is not available in this ZMK version
    // Keeping this as a placeholder for future implementation
    const struct zmk_layer_state_changed *layer_event = as_zmk_layer_state_changed(eh);
    
    if (layer_event == NULL) {
        return 0;
    }
    
    LOG_DBG("Layer changed to %d", layer_event->layer);
    
    // Update hue based on layer (simple effect)
    state.hue = (layer_event->layer * 60) % 360;
    state.needs_update = true;
    k_work_submit(&rgb_led_work);
#endif
    
    return 0;
}

ZMK_LISTENER(rgb_led_activity, rgb_led_activity_event_listener);
ZMK_SUBSCRIPTION(rgb_led_activity, zmk_activity_state_changed);

#if IS_ENABLED(CONFIG_ZMK_RGB_EFFECT_TYPING_HEATMAP)
ZMK_LISTENER(rgb_led_keycode, rgb_led_keycode_event_listener);
ZMK_SUBSCRIPTION(rgb_led_keycode, zmk_keycode_state_changed);
#endif

#if IS_ENABLED(CONFIG_ZMK_RGB_EFFECT_LAYER_INDICATOR)
ZMK_LISTENER(rgb_led_layer, rgb_led_layer_event_listener);
ZMK_SUBSCRIPTION(rgb_led_layer, zmk_layer_state_changed);
#endif

// Initialization
static int rgb_led_init(void) {
    LOG_INF("Initializing RGB LED subsystem");
    
    // Initial LED update
    state.needs_update = true;
    k_work_submit(&rgb_led_work);
    
    return 0;
}

SYS_INIT(rgb_led_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

#endif // CONFIG_ZMK_RGB_PER_KEY
