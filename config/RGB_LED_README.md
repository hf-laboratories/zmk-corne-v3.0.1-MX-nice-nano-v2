# RGB Per-Key LED Driver

This module provides RGB per-key LED support for ZMK firmware.

## Structure

```
config/
├── CMakeLists.txt                      # Build configuration
├── Kconfig                             # Configuration options
├── drivers/led/
│   └── ws2812.c                       # WS2812 LED driver
├── dts/bindings/led/
│   ├── zmk,ws2812.yaml                # WS2812 devicetree binding
│   └── zmk,rgb-animations.yaml        # RGB animations binding
├── include/drivers/led/
│   └── ws2812.h                       # Driver API header
└── src/rgb_led/
    └── rgb_led.c                      # RGB LED behavior implementation
```

## Features

- **WS2812 LED Driver**: Bit-banging GPIO driver for WS2812/SK6812 RGB LEDs
- **HSV Color Support**: HSV to RGB conversion for easy color manipulation
- **Effect Support**:
  - Static color
  - Typing heatmap (triggered by keypress)
  - Layer indicators (color changes based on layer)
  - Breathing effect
- **Event Integration**: Responds to ZMK events (activity, keypress, layer changes)
- **Power Management**: Auto-off when idle or USB disconnected

## Configuration

The following options are available in `Kconfig`:

- `CONFIG_ZMK_RGB_PER_KEY` - Enable per-key RGB support
- `CONFIG_ZMK_RGB_LED_COUNT` - Number of LEDs (default: 42)
- `CONFIG_ZMK_RGB_ON_START` - Turn on LEDs at startup
- `CONFIG_ZMK_RGB_AUTO_OFF_IDLE` - Auto-off when idle
- `CONFIG_ZMK_RGB_AUTO_OFF_USB` - Auto-off when USB disconnected
- `CONFIG_ZMK_RGB_*_START` - Initial hue, saturation, brightness, effect
- `CONFIG_ZMK_RGB_*_STEP` - Adjustment steps
- `CONFIG_ZMK_RGB_EFFECT_*` - Enable specific effects

## Devicetree

Define your LED strip in devicetree:

```dts
/ {
    rgb_leds: ws2812 {
        compatible = "zmk,ws2812";
        label = "PerKeyRGB";
        chain-length = <42>;
        color-order = <GRB>;
        pin = <&gpio0 13>;
    };
};
```

## Implementation Notes

### WS2812 Driver (drivers/led/ws2812.c)

The WS2812 driver implements bit-banging over GPIO to control WS2812/SK6812 LEDs:

- **Timing**: Uses `k_busy_wait()` for precise timing control
- **Protocol**: Implements WS2812 timing (0: 400ns high + 850ns low, 1: 800ns high + 450ns low)
- **Buffer**: Maintains RGB pixel buffer in memory
- **Thread-safe**: Disables interrupts during transmission

### RGB LED Behavior (src/rgb_led/rgb_led.c)

The RGB LED behavior integrates with ZMK's event system:

- **Event Listeners**: Subscribes to activity, keycode, and layer events
- **Work Queue**: Uses kernel work queue for non-blocking LED updates
- **HSV Conversion**: Converts HSV color space to RGB for easier color manipulation
- **Effects**: Implements various lighting effects based on keyboard state

## Limitations

- **Timing Accuracy**: Bit-banging may not be perfectly accurate on all platforms
- **Performance**: Disabling interrupts during transmission may impact real-time performance
- **Basic Implementation**: This is a simplified implementation for demonstration
- **No SPI Support**: Uses GPIO bit-banging instead of SPI for broader compatibility

## Future Improvements

- Add SPI-based WS2812 driver for better performance
- Implement more sophisticated effects
- Add user-configurable color mappings
- Add brightness ramping/fading
- Support for different LED chipsets
- Per-key color configuration via devicetree
