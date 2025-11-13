# ZMK Configuration for Corne v3 with nice!nano v2

This document describes the complete configuration for this wireless Corne v3 keyboard with nice!nano v2 controllers.

## Complete Configuration Overview

This keyboard is configured with:
- ✅ Corne v3 hardware
- ✅ nice!nano v2 controllers (both halves)
- ✅ Wireless operation (Bluetooth Low Energy)
- ✅ Per-key RGB LEDs (21 LEDs per side, 42 total)
- ✅ No nice!view displays
- ✅ No OLED displays
- ✅ ZMK Studio support for real-time configuration
- ✅ USB and Bluetooth connectivity
- ✅ Battery monitoring and reporting
- ✅ No-PIN pairing for Bluetooth
- ✅ Split keyboard support with BLE communication
- ✅ Basic 4-layer keymap

## Detailed Configuration

### 1. Split Keyboard Configuration
- **Split Mode**: `CONFIG_ZMK_SPLIT=y`
- **Bluetooth Split Transport**: `CONFIG_ZMK_SPLIT_BLE=y`
- **Left Half**: Central (connects to computer via USB or Bluetooth)
- **Right Half**: Peripheral (connects wirelessly to left half)
- Both halves communicate via BLE
- The left (central) half handles all HID communication with the host computer

### 2. ZMK Studio Support
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
- **Driver**: `CONFIG_WS2812_STRIP=y` - WS2812 LED strip support
- **LED Count**: 21 LEDs per side (42 total for split keyboard)
- **External Power Control**: `CONFIG_ZMK_RGB_UNDERGLOW_EXT_POWER=y`
- **Auto-start**: Enabled (LEDs turn on at boot)
- **Default Settings**:
  - Effect: Breathing (effect #2)
  - Hue: 180° (Cyan)
  - Saturation: 100%
  - Brightness: 50%
  - Auto-off on USB disconnect: Disabled

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

### 5. Display Configuration
- **OLED**: Disabled (`CONFIG_ZMK_DISPLAY=n`)
- **nice!view**: Not configured (displays disabled)
- **Custom Status Screen**: Disabled (`CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM=n`)

This configuration prioritizes battery life by disabling power-hungry display features.

### 6. Battery Configuration
- **Battery Reporting**: `CONFIG_ZMK_BATTERY_REPORTING=y`
- Battery level is reported over BLE to connected devices
- The nice!nano v2 has built-in battery monitoring circuitry
- Battery percentage is visible on connected devices (computers, phones, tablets)

### 7. Bluetooth Configuration
- **TX Power**: `CONFIG_BT_CTLR_TX_PWR_PLUS_8=y` (+8 dBm for better range)
- **Experimental BLE Features**: `CONFIG_ZMK_BLE_EXPERIMENTAL_FEATURES=y`
- **No-PIN Pairing**: `CONFIG_ZMK_BLE_PASSKEY_ENTRY=n`
  - Bluetooth devices can pair without entering a PIN code
  - Simplifies the pairing process
  - Still secure through standard BLE encryption
- **Multiple Device Support**: Up to 5 paired devices
- **Profile Switching**: Use Bluetooth layer keys (BT 1-5) to switch between paired devices

### 8. USB Configuration
- USB connectivity enabled by default on nice!nano v2
- Supports both USB HID and USB charging
- Can switch between USB and Bluetooth output modes
- When connected via USB, battery charges automatically

### 9. Power Management
- **Sleep Mode**: `CONFIG_ZMK_SLEEP=y`
- **Sleep Timeout**: 30 minutes (1,800,000 ms)
- **Idle Timeout**: 2 minutes (120,000 ms)
- **External Power Control**: `CONFIG_ZMK_EXT_POWER=y`
- **Low Debounce Times**: 
  - Press: 1ms (`CONFIG_ZMK_KSCAN_DEBOUNCE_PRESS_MS=1`)
  - Release: 5ms (`CONFIG_ZMK_KSCAN_DEBOUNCE_RELEASE_MS=5`)
- Optimized for responsive typing while maintaining battery efficiency

## Device Tree Overlay
A `corne.overlay` file configures the LED hardware:
- Defines SPI3 pinout for LED communication (pin P0.06)
- Configures WS2812 LED strip parameters
- Sets up 21 LEDs per side with proper color mapping (GRB order)
- Selects the 5-column matrix transform for the Corne layout

## Building the Firmware
The GitHub Actions workflow automatically builds firmware for:
- `nice_nano_v2` + `corne_left` (Central)
- `nice_nano_v2` + `corne_right` (Peripheral)

### How to Flash
1. Download the firmware files from GitHub Actions artifacts
2. Connect the keyboard half via USB
3. Double-tap the reset button to enter bootloader mode
4. The keyboard will appear as a USB drive
5. Drag and drop the appropriate `.uf2` file to the drive
6. The keyboard will automatically reboot with new firmware

### First-Time Setup
1. Flash both halves with their respective firmware
2. Power on both halves simultaneously (or within a few seconds)
3. The halves will pair automatically via Bluetooth
4. Connect the left (central) half to your computer via Bluetooth or USB

## Configuration Summary

| Feature | Configuration | Status |
|---------|--------------|--------|
| Controllers | nice!nano v2 | ✅ |
| Wireless | Bluetooth LE | ✅ |
| Split Communication | BLE | ✅ |
| Per-Key RGB | 21 LEDs/side | ✅ |
| ZMK Studio | Enabled | ✅ |
| Display | Disabled | ✅ |
| Battery Reporting | Enabled | ✅ |
| No-PIN Pairing | Enabled | ✅ |
| USB Support | Enabled | ✅ |
| Multi-Device | 5 Profiles | ✅ |

## Additional Resources
- [ZMK Documentation](https://zmk.dev/)
- [ZMK Studio](https://zmk.studio)
- [Corne Keyboard](https://github.com/foostan/crkbd)
- [ZMK Split Keyboard Guide](https://zmk.dev/docs/features/split-keyboards)
- [nice!nano Documentation](https://nicekeyboards.com/docs/nice-nano/)
