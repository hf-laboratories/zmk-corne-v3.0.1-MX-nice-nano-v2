# ZMK Configuration Changes

This document describes the recent configuration changes made to this keyboard.

## Changes Implemented

### 1. ZMK Studio Support
- **Enabled**: `CONFIG_ZMK_STUDIO=y`
- ZMK Studio allows real-time keymap editing and configuration through a web interface
- Connect your keyboard via USB and visit [ZMK Studio](https://zmk.studio) to configure it

### 2. QWERTY Keymap
- **Base Layer (Layer 0)**: Standard QWERTY layout
  - Top row: Q W E R T Y U I O P
  - Home row: A S D F G H J K L ;
  - Bottom row: Z X C Y V B N M , . /
  - Modifiers: Tab, Ctrl, Shift, GUI/Win, Alt
  
- **Lower Layer (Layer 1)**: Numbers and Bluetooth
  - Number row 1-0
  - Bluetooth pairing controls (BT 1-5, Clear)
  - Arrow keys

- **Raise Layer (Layer 2)**: Symbols
  - Special characters: ! @ # $ % ^ & * ( )
  - Brackets and braces
  - Minus, equals, plus, underscore

- **Adjust Layer (Layer 3)**: Function keys and RGB
  - F1-F12 function keys
  - RGB controls (toggle, hue, saturation, brightness, speed, effects)

### 3. RGB LED Configuration
- **Enabled**: `CONFIG_ZMK_RGB_UNDERGLOW=y`
- **Driver**: WS2812 LED strip support enabled
- **LED Count**: 21 LEDs per side (42 total for split keyboard)
- **Default Settings**:
  - Effect: Breathing (effect #2)
  - Hue: 180° (Cyan)
  - Saturation: 100%
  - Brightness: 50%
  - Auto-start: Enabled

#### RGB Controls
Access RGB controls on Layer 3 (hold both lower and raise keys):
- `RGB_TOG`: Toggle LEDs on/off
- `RGB_HUI/HUD`: Increase/decrease hue
- `RGB_SAI/SAD`: Increase/decrease saturation
- `RGB_BRI/BRD`: Increase/decrease brightness
- `RGB_SPI/SPD`: Increase/decrease animation speed
- `RGB_EFF`: Cycle through effects

### 4. Per-Key Reactive Lighting (Pulse on Keypress)
**NOTE**: True per-key reactive lighting (pulse animation on individual keypress) is **not currently supported** in mainline ZMK firmware. 

The current configuration provides:
- ✅ RGB underglow with various animation effects
- ✅ Global lighting controls
- ✅ Multiple color modes and animations

To achieve per-key reactive effects, you would need:
- A custom ZMK fork (e.g., [extra-salad/zmk-per-key-rgb](https://github.com/extra-salad/zmk-per-key-rgb))
- Hardware with per-key RGB LEDs (current Corne v3 typically uses underglow)
- Custom firmware modifications

**Track the feature request**: https://github.com/zmkfirmware/zmk/issues/554

## Device Tree Overlay
A `corne.overlay` file has been added to configure the LED hardware:
- Defines SPI3 pinout for LED communication
- Configures WS2812 LED strip parameters
- Sets up 21 LEDs per side with proper color mapping (GRB order)

## Power Management
The existing power management settings have been preserved:
- Sleep timeout: 30 minutes
- Idle timeout: 2 minutes
- External power control enabled
- Low debounce times for responsive typing (1ms press, 5ms release)

## Bluetooth
- Bluetooth TX power: +8 dBm for better range
- Experimental BLE features enabled
- Supports up to 5 paired devices

## Building the Firmware
The GitHub Actions workflow automatically builds firmware for:
- `nice_nano_v2` + `corne_left`
- `nice_nano_v2` + `corne_right`

Firmware files are available in the GitHub Actions artifacts after each successful build.

## Additional Resources
- [ZMK Documentation](https://zmk.dev/)
- [ZMK Studio](https://zmk.studio)
- [Corne Keyboard](https://github.com/foostan/crkbd)
