# Complete ZMK Build Configurables Reference

This document provides a comprehensive reference for all configuration options available in a ZMK (Zephyr Mechanical Keyboard) firmware build. ZMK uses two primary configuration mechanisms: **Kconfig** (for firmware features) and **Devicetree** (for hardware and keymaps).

## Table of Contents

1. [Configuration System Overview](#configuration-system-overview)
2. [Kconfig Options](#kconfig-options)
   - [System Configuration](#system-configuration)
   - [Keyboard Identity](#keyboard-identity)
   - [HID & USB Configuration](#hid--usb-configuration)
   - [Bluetooth Configuration](#bluetooth-configuration)
   - [Split Keyboard Configuration](#split-keyboard-configuration)
   - [Power Management](#power-management)
   - [Lighting Configuration](#lighting-configuration)
   - [Display Configuration](#display-configuration)
   - [Behavior Configuration](#behavior-configuration)
   - [Advanced Features](#advanced-features)
   - [Debugging & Logging](#debugging--logging)
3. [Devicetree Configuration](#devicetree-configuration)
   - [Keymap Structure](#keymap-structure)
   - [Behaviors](#behaviors)
   - [Hardware Definitions](#hardware-definitions)
4. [Build Configuration](#build-configuration)
5. [Configuration Examples](#configuration-examples)

---

## Configuration System Overview

### Kconfig (.conf files)
- **Purpose**: Controls compile-time firmware features and settings
- **Location**: `config/<keyboard_name>.conf`
- **Format**: `CONFIG_OPTION_NAME=y` or `CONFIG_OPTION_NAME=value`
- **Scope**: Global firmware behavior, feature enablement

### Devicetree (.keymap, .overlay, .dts files)
- **Purpose**: Describes hardware layout, keymaps, and device-specific settings
- **Location**: `config/<keyboard_name>.keymap` and `config/<keyboard_name>.overlay`
- **Format**: C-like hierarchical syntax with nodes and properties
- **Scope**: Hardware description, keymap definitions, per-key behaviors

### Build Configuration (build.yaml)
- **Purpose**: Defines which boards and shields to build
- **Location**: `build.yaml` in repository root
- **Format**: YAML with board/shield combinations

---

## Kconfig Options

All Kconfig options are set in `.conf` files using the format `CONFIG_<OPTION>=<value>`.

### System Configuration

#### Basic System Options

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_HEAP_MEM_POOL_SIZE` | int | varies | Size of heap memory pool in bytes |
| `CONFIG_MAIN_STACK_SIZE` | int | 2048 | Size of main thread stack |
| `CONFIG_SYSTEM_WORKQUEUE_STACK_SIZE` | int | 2048 | Size of system workqueue stack |
| `CONFIG_ZMK_SETTINGS_SAVE_DEBOUNCE` | int | 60000 | Milliseconds to wait before saving settings (60s default) |
| `CONFIG_ZMK_SETTINGS_RESET_ON_START` | bool | n | Reset all settings to default on boot |

#### Keyboard Scanning (Kscan)

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_KSCAN_DEBOUNCE_PRESS_MS` | int | 5 | Debounce time for key press in milliseconds |
| `CONFIG_ZMK_KSCAN_DEBOUNCE_RELEASE_MS` | int | 5 | Debounce time for key release in milliseconds |
| `CONFIG_ZMK_KSCAN_MATRIX_POLLING` | bool | n | Use polling instead of interrupts for matrix scan |
| `CONFIG_ZMK_KSCAN_DEBOUNCE_METHOD_GLOBAL_DEFER` | bool | y | Use global defer debouncing method |

### Keyboard Identity

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_KEYBOARD_NAME` | string | "" | Display name of keyboard (shown to OS) |
| `CONFIG_USB_DEVICE_VID` | hex | 0x1D50 | USB Vendor ID |
| `CONFIG_USB_DEVICE_PID` | hex | 0x615E | USB Product ID |
| `CONFIG_USB_DEVICE_MANUFACTURER` | string | "ZMK Project" | USB manufacturer string |
| `CONFIG_USB_DEVICE_PRODUCT` | string | varies | USB product string |

### HID & USB Configuration

#### HID Report Configuration

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_HID_REPORT_TYPE_NKRO` | bool | n | Enable N-Key Rollover (NKRO) mode |
| `CONFIG_ZMK_HID_REPORT_TYPE_HKRO` | bool | y | Enable traditional 6-key rollover mode |
| `CONFIG_ZMK_HID_KEYBOARD_REPORT_SIZE` | int | 6 | Number of simultaneous keys in HKRO mode |
| `CONFIG_ZMK_HID_KEYBOARD_NKRO_EXTENDED_REPORT` | bool | n | Include F13-F24 and international keys in NKRO |
| `CONFIG_ZMK_HID_INDICATORS` | bool | y | Enable HID indicator state reception (Caps Lock LED, etc.) |

#### Consumer & Media Keys

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_HID_CONSUMER_REPORT_SIZE` | int | 6 | Number of simultaneous consumer keys |
| `CONFIG_ZMK_HID_CONSUMER_REPORT_USAGES_FULL` | bool | y | Full consumer key set (best compatibility) |
| `CONFIG_ZMK_HID_CONSUMER_REPORT_USAGES_BASIC` | bool | n | Basic consumer keys only (iPad compatibility) |

#### USB Configuration

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_USB` | bool | y | Enable USB connectivity |
| `CONFIG_ZMK_USB_BOOT` | bool | n | Enable USB boot protocol support |
| `CONFIG_ZMK_USB_LOGGING` | bool | n | Enable USB logging (for debugging) |

### Bluetooth Configuration

#### Basic Bluetooth

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_BLE` | bool | y | Enable Bluetooth LE support |
| `CONFIG_ZMK_BLE_CLEAR_BONDS_ON_START` | bool | n | Clear all Bluetooth bonds on startup |
| `CONFIG_ZMK_BLE_CONSUMER_REPORT_QUEUE_SIZE` | int | 5 | Consumer report queue size |
| `CONFIG_ZMK_BLE_KEYBOARD_REPORT_QUEUE_SIZE` | int | 5 | Keyboard report queue size |
| `CONFIG_ZMK_BLE_INIT_PRIORITY` | int | 50 | BLE initialization priority |
| `CONFIG_ZMK_BLE_THREAD_PRIORITY` | int | 5 | BLE thread priority |
| `CONFIG_ZMK_BLE_THREAD_STACK_SIZE` | int | 512 | BLE thread stack size |
| `CONFIG_ZMK_BLE_PASSKEY_ENTRY` | bool | n | Require passkey for Bluetooth pairing |
| `CONFIG_ZMK_BLE_EXPERIMENTAL_FEATURES` | bool | n | Enable experimental BLE features |

#### Bluetooth Profiles

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_BT_MAX_CONN` | int | 5 | Maximum simultaneous BLE connections |
| `CONFIG_BT_MAX_PAIRED` | int | 5 | Maximum paired devices |

#### Bluetooth TX Power

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_BT_CTLR_TX_PWR_MINUS_20` | bool | n | -20 dBm TX power (lowest) |
| `CONFIG_BT_CTLR_TX_PWR_MINUS_16` | bool | n | -16 dBm TX power |
| `CONFIG_BT_CTLR_TX_PWR_MINUS_12` | bool | n | -12 dBm TX power |
| `CONFIG_BT_CTLR_TX_PWR_MINUS_8` | bool | n | -8 dBm TX power |
| `CONFIG_BT_CTLR_TX_PWR_MINUS_4` | bool | n | -4 dBm TX power |
| `CONFIG_BT_CTLR_TX_PWR_0` | bool | y | 0 dBm TX power (default) |
| `CONFIG_BT_CTLR_TX_PWR_PLUS_2` | bool | n | +2 dBm TX power |
| `CONFIG_BT_CTLR_TX_PWR_PLUS_3` | bool | n | +3 dBm TX power |
| `CONFIG_BT_CTLR_TX_PWR_PLUS_4` | bool | n | +4 dBm TX power |
| `CONFIG_BT_CTLR_TX_PWR_PLUS_5` | bool | n | +5 dBm TX power |
| `CONFIG_BT_CTLR_TX_PWR_PLUS_6` | bool | n | +6 dBm TX power |
| `CONFIG_BT_CTLR_TX_PWR_PLUS_7` | bool | n | +7 dBm TX power |
| `CONFIG_BT_CTLR_TX_PWR_PLUS_8` | bool | n | +8 dBm TX power (highest, best range) |

#### Bluetooth Device Information

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_BT_DEVICE_NAME` | string | "ZMK Keyboard" | Bluetooth device name |
| `CONFIG_BT_DIS_MODEL` | string | varies | Device Information Service model |
| `CONFIG_BT_DIS_MANUF` | string | "ZMK Project" | Device Information Service manufacturer |

### Split Keyboard Configuration

#### Split Basic Settings

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_SPLIT` | bool | n | Enable split keyboard support |
| `CONFIG_ZMK_SPLIT_ROLE_CENTRAL` | bool | n | Set this half as central (host-facing) |
| `CONFIG_ZMK_SPLIT_ROLE_PERIPHERAL` | bool | n | Set this half as peripheral |

#### Split Transport

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_SPLIT_BLE` | bool | y | Use Bluetooth for split communication |
| `CONFIG_ZMK_SPLIT_SERIAL` | bool | n | Use serial/UART for split communication |

#### Split BLE Settings

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_SPLIT_BLE_CENTRAL_POSITION_QUEUE_SIZE` | int | 5 | Central position queue size |
| `CONFIG_ZMK_SPLIT_BLE_PERIPHERAL_POSITION_QUEUE_SIZE` | int | 5 | Peripheral position queue size |
| `CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_FETCHING` | bool | y | Fetch battery level from peripheral |
| `CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_PROXY` | bool | y | Proxy peripheral battery to host |

### Power Management

#### Sleep Configuration

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_SLEEP` | bool | n | Enable deep sleep mode |
| `CONFIG_ZMK_IDLE_TIMEOUT` | int | 30000 | Idle timeout in milliseconds (30s default) |
| `CONFIG_ZMK_IDLE_SLEEP_TIMEOUT` | int | 900000 | Sleep timeout in milliseconds (15m default) |

#### External Power

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_EXT_POWER` | bool | y | Enable external power control |

#### Battery

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_BATTERY_REPORTING` | bool | n | Enable battery level reporting |
| `CONFIG_ZMK_BATTERY_REPORT_INTERVAL` | int | 60 | Battery report interval in seconds |

### Lighting Configuration

#### RGB Underglow

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_RGB_UNDERGLOW` | bool | n | Enable RGB underglow support |
| `CONFIG_WS2812_STRIP` | bool | n | Enable WS2812 LED strip driver |
| `CONFIG_ZMK_RGB_UNDERGLOW_EXT_POWER` | bool | y | Control underglow via external power |
| `CONFIG_ZMK_RGB_UNDERGLOW_ON_START` | bool | y | Turn on underglow at startup |
| `CONFIG_ZMK_RGB_UNDERGLOW_AUTO_OFF_IDLE` | bool | n | Turn off underglow when idle |
| `CONFIG_ZMK_RGB_UNDERGLOW_AUTO_OFF_USB` | bool | n | Turn off underglow on USB disconnect |

#### RGB Underglow Effects & Defaults

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_RGB_UNDERGLOW_HUE_START` | int | 0 | Starting hue (0-359) |
| `CONFIG_ZMK_RGB_UNDERGLOW_SAT_START` | int | 100 | Starting saturation (0-100) |
| `CONFIG_ZMK_RGB_UNDERGLOW_BRT_START` | int | 100 | Starting brightness (0-100) |
| `CONFIG_ZMK_RGB_UNDERGLOW_SPD_START` | int | 3 | Starting animation speed (1-5) |
| `CONFIG_ZMK_RGB_UNDERGLOW_EFF_START` | int | 0 | Starting effect (0=solid, 1=breathe, 2=spectrum, 3=swirl) |
| `CONFIG_ZMK_RGB_UNDERGLOW_HUE_STEP` | int | 10 | Hue adjustment step size |
| `CONFIG_ZMK_RGB_UNDERGLOW_SAT_STEP` | int | 10 | Saturation adjustment step size |
| `CONFIG_ZMK_RGB_UNDERGLOW_BRT_STEP` | int | 10 | Brightness adjustment step size |
| `CONFIG_ZMK_RGB_UNDERGLOW_BRT_MIN` | int | 0 | Minimum brightness value |
| `CONFIG_ZMK_RGB_UNDERGLOW_BRT_MAX` | int | 100 | Maximum brightness value |

#### Backlight (Single-Color LEDs)

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_BACKLIGHT` | bool | n | Enable backlight support |
| `CONFIG_ZMK_BACKLIGHT_BRT_START` | int | 40 | Starting brightness (0-100) |
| `CONFIG_ZMK_BACKLIGHT_BRT_STEP` | int | 20 | Brightness adjustment step |
| `CONFIG_ZMK_BACKLIGHT_ON_START` | bool | y | Turn on backlight at startup |
| `CONFIG_ZMK_BACKLIGHT_AUTO_OFF_IDLE` | bool | n | Turn off backlight when idle |
| `CONFIG_ZMK_BACKLIGHT_AUTO_OFF_USB` | bool | n | Turn off backlight on USB disconnect |

### Display Configuration

#### Display Basic Settings

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_DISPLAY` | bool | n | Enable display support (OLED, E-Paper, etc.) |
| `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE` | bool | y | Blank display when idle |
| `CONFIG_ZMK_DISPLAY_DEDICATED_THREAD` | bool | n | Use dedicated thread for display updates |
| `CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_STACK_SIZE` | int | 2048 | Display thread stack size |
| `CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_PRIORITY` | int | 5 | Display thread priority |

#### Display Status Screen

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN` | bool | y | Use built-in status screen |
| `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM` | bool | n | Use custom status screen |

#### Display Widgets

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_WIDGET_LAYER_STATUS` | bool | y | Show active layer |
| `CONFIG_ZMK_WIDGET_BATTERY_STATUS` | bool | y | Show battery status |
| `CONFIG_ZMK_WIDGET_OUTPUT_STATUS` | bool | y | Show output (USB/BLE) status |
| `CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS` | bool | n | Show peripheral status (split keyboards) |
| `CONFIG_ZMK_WIDGET_WPM_STATUS` | bool | n | Show words per minute |

### Behavior Configuration

#### Behavior Queue

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_BEHAVIORS_QUEUE_SIZE` | int | 512 | Size of behavior event queue |

#### Caps Word

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_BEHAVIOR_CAPS_WORD` | bool | y | Enable caps word behavior |
| `CONFIG_ZMK_BEHAVIOR_CAPS_WORD_CONTINUATIONS` | string | "_" | Characters that don't break caps word |
| `CONFIG_ZMK_BEHAVIOR_CAPS_WORD_INVERT_ON_SHIFT` | bool | n | Invert behavior when shift is held |

#### Key Toggle

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_BEHAVIOR_KEY_TOGGLE` | bool | y | Enable key toggle behavior |

#### Soft Off

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_BEHAVIOR_SOFT_OFF` | bool | n | Enable soft off behavior |

#### Mod-Morph

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_BEHAVIOR_MOD_MORPH` | bool | y | Enable mod-morph behavior |

#### Macro

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_MACRO_DEFAULT_WAIT_MS` | int | 15 | Default wait time between macro events |
| `CONFIG_ZMK_MACRO_DEFAULT_TAP_MS` | int | 30 | Default tap duration for macro events |

### Advanced Features

#### ZMK Studio

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_STUDIO` | bool | n | Enable ZMK Studio for runtime configuration |
| `CONFIG_ZMK_STUDIO_LOCKING` | bool | y | Require unlock to access Studio features |

#### Combo

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_COMBO_MAX_PRESSED_COMBOS` | int | 4 | Maximum simultaneously active combos |
| `CONFIG_ZMK_COMBO_MAX_COMBOS_PER_KEY` | int | 5 | Maximum combos per physical key |
| `CONFIG_ZMK_COMBO_MAX_KEYS_PER_COMBO` | int | 4 | Maximum keys in a single combo |

#### Mouse Emulation

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_MOUSE` | bool | n | Enable mouse emulation |
| `CONFIG_ZMK_MOUSE_TICK_DURATION` | int | 8 | Mouse movement tick duration in ms |

#### Words Per Minute (WPM)

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_WPM` | bool | n | Enable WPM tracking |

#### Encoders

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_EC11` | bool | n | Enable EC11 rotary encoder support |
| `CONFIG_EC11_TRIGGER_GLOBAL_THREAD` | bool | n | Use global thread for encoder events |

### Debugging & Logging

#### Logging

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_LOG_LEVEL` | int | 4 | Log level (0=off, 1=error, 2=warn, 3=info, 4=debug) |
| `CONFIG_LOG_PROCESS_THREAD_STARTUP_DELAY_MS` | int | 0 | Delay before log thread starts |
| `CONFIG_LOG_BUFFER_SIZE` | int | 1024 | Log buffer size in bytes |

#### USB Logging

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_ZMK_USB_LOGGING` | bool | n | Enable logging over USB CDC |

#### RTT Logging

| Option | Type | Default | Description |
|--------|------|---------|-------------|
| `CONFIG_LOG_BACKEND_RTT` | bool | n | Enable RTT logging backend |
| `CONFIG_USE_SEGGER_RTT` | bool | n | Enable SEGGER RTT support |

---

## Devicetree Configuration

Devicetree files define hardware layout, keymaps, and device-specific configurations using a hierarchical syntax.

### Keymap Structure

#### Basic Keymap Node

```dts
/ {
    keymap {
        compatible = "zmk,keymap";
        
        layer_name {
            label = "Layer Name";
            bindings = <
                &kp A &kp B &kp C
                &kp D &kp E &kp F
            >;
        };
    };
};
```

#### Keymap Properties

| Property | Type | Description |
|----------|------|-------------|
| `compatible` | string | Must be "zmk,keymap" |
| `label` | string | Human-readable layer name |
| `bindings` | array | List of key bindings for this layer |

### Behaviors

Behaviors are actions assigned to keys. They are referenced using `&behavior_name`.

#### Common Built-in Behaviors

| Behavior | Usage | Description |
|----------|-------|-------------|
| `&kp` | `&kp KEY` | Key press: sends keycode on press/release |
| `&mo` | `&mo LAYER` | Momentary layer: activates layer while held |
| `&to` | `&to LAYER` | To layer: switches to layer until changed |
| `&tog` | `&tog LAYER` | Toggle layer: toggles layer on/off |
| `&lt` | `&lt LAYER KEY` | Layer-tap: layer when held, key when tapped |
| `&mt` | `&mt MOD KEY` | Mod-tap: modifier when held, key when tapped |
| `&sk` | `&sk MOD` | Sticky key: modifier stays active for next key |
| `&sl` | `&sl LAYER` | Sticky layer: layer stays active for next key |
| `&trans` | `&trans` | Transparent: passes through to lower layer |
| `&none` | `&none` | None: does nothing |
| `&reset` | `&reset` | Reset: restarts the keyboard |
| `&bootloader` | `&bootloader` | Bootloader: enters bootloader/DFU mode |
| `&bt` | `&bt BT_CMD` | Bluetooth: Bluetooth commands |
| `&out` | `&out OUT_CMD` | Output: switch between USB/BLE |
| `&ext_power` | `&ext_power EP_CMD` | External power: control external power |
| `&rgb_ug` | `&rgb_ug RGB_CMD` | RGB underglow: control RGB lighting |
| `&bl` | `&bl BL_CMD` | Backlight: control backlight |
| `&caps_word` | `&caps_word` | Caps word: capitalize next word |
| `&key_repeat` | `&key_repeat` | Repeat last key |
| `&gresc` | `&gresc` | Grave escape: ` normally, ESC with shift/GUI |
| `&sys_reset` | `&sys_reset` | System reset |
| `&studio_unlock` | `&studio_unlock` | Unlock ZMK Studio |

#### Hold-Tap Behavior

Hold-tap allows different actions for tap vs hold:

```dts
/ {
    behaviors {
        ht_example: hold_tap_example {
            compatible = "zmk,behavior-hold-tap";
            label = "HOLD_TAP_EXAMPLE";
            #binding-cells = <2>;
            tapping-term-ms = <200>;
            quick-tap-ms = <0>;
            flavor = "tap-preferred";
            bindings = <&kp>, <&kp>;
        };
    };
};
```

##### Hold-Tap Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `tapping-term-ms` | int | 200 | Time in ms to distinguish tap from hold |
| `quick-tap-ms` | int | 0 | Quick tap window to force tap behavior |
| `flavor` | string | "hold-preferred" | Behavior preference (see below) |
| `retro-tap` | bool | false | Tap if released after tapping-term without other keys |
| `hold-trigger-key-positions` | array | [] | Keys that trigger hold (for home row mods) |

##### Hold-Tap Flavors

| Flavor | Description |
|--------|-------------|
| `tap-preferred` | Prefer tap behavior; hold only if held past tapping-term without other keys |
| `hold-preferred` | Prefer hold behavior; tap only if released before tapping-term |
| `balanced` | Hold if another key is pressed before release, otherwise tap |
| `tap-unless-interrupted` | Tap unless another key is pressed during tapping-term |

#### Macro Behavior

```dts
/ {
    macros {
        macro_example: macro_example {
            compatible = "zmk,behavior-macro";
            label = "MACRO_EXAMPLE";
            #binding-cells = <0>;
            bindings = <&kp A &kp B &kp C>;
        };
    };
};
```

##### Macro Special Actions

| Action | Description |
|--------|-------------|
| `&macro_press` | Press specified keys |
| `&macro_release` | Release specified keys |
| `&macro_tap` | Tap specified keys |
| `&macro_wait_time` | Wait specified milliseconds |
| `&macro_tap_time` | Set tap duration |
| `&macro_pause_for_release` | Pause until macro key is released |

#### Mod-Morph Behavior

Different output based on active modifiers:

```dts
/ {
    behaviors {
        mm_example: mod_morph_example {
            compatible = "zmk,behavior-mod-morph";
            label = "MOD_MORPH_EXAMPLE";
            #binding-cells = <0>;
            bindings = <&kp A>, <&kp B>;
            mods = <(MOD_LSFT|MOD_RSFT)>;
        };
    };
};
```

#### Combo Behavior

Multiple keys pressed simultaneously:

```dts
/ {
    combos {
        compatible = "zmk,combos";
        
        combo_example {
            timeout-ms = <50>;
            key-positions = <0 1>;
            bindings = <&kp ESC>;
        };
    };
};
```

### Hardware Definitions

#### Matrix Transform

Defines how physical switch positions map to logical key positions:

```dts
/ {
    chosen {
        zmk,matrix-transform = &default_transform;
    };
    
    default_transform: keymap_transform_0 {
        compatible = "zmk,matrix-transform";
        columns = <12>;
        rows = <4>;
        map = <
            RC(0,0) RC(0,1) RC(0,2) // ... 
        >;
    };
};
```

#### RGB LED Configuration

```dts
&spi3 {
    led_strip: ws2812@0 {
        compatible = "worldsemi,ws2812-spi";
        chain-length = <21>;
        spi-max-frequency = <4000000>;
        color-mapping = <LED_COLOR_ID_GREEN LED_COLOR_ID_RED LED_COLOR_ID_BLUE>;
    };
};

/ {
    chosen {
        zmk,underglow = &led_strip;
    };
};
```

##### LED Properties

| Property | Description |
|----------|-------------|
| `chain-length` | Number of LEDs in the strip |
| `spi-max-frequency` | SPI communication frequency |
| `color-mapping` | RGB color channel order (GRB, RGB, etc.) |

#### Encoder Configuration

```dts
&left_encoder {
    status = "okay";
    a-gpios = <&pro_micro 21 GPIO_PULL_UP>;
    b-gpios = <&pro_micro 20 GPIO_PULL_UP>;
    resolution = <4>;
};

/ {
    sensors {
        compatible = "zmk,keymap-sensors";
        sensors = <&left_encoder>;
    };
};
```

#### Display Configuration

```dts
&pro_micro_i2c {
    status = "okay";
    
    oled: ssd1306@3c {
        compatible = "solomon,ssd1306fb";
        reg = <0x3c>;
        width = <128>;
        height = <32>;
    };
};

/ {
    chosen {
        zephyr,display = &oled;
    };
};
```

---

## Build Configuration

### build.yaml Structure

```yaml
include:
  - board: nice_nano_v2
    shield: corne_left
  - board: nice_nano_v2
    shield: corne_right
    cmake-args: -DCONFIG_ZMK_USB_LOGGING=y
    artifact-name: corne_right_with_logging
```

#### Build Configuration Options

| Field | Description |
|-------|-------------|
| `board` | Target microcontroller board (e.g., nice_nano_v2, pro_micro) |
| `shield` | Keyboard shield/PCB (e.g., corne_left, corne_right) |
| `cmake-args` | Additional CMake arguments for this build |
| `artifact-name` | Custom name for build artifact |

### West Manifest (west.yml)

```yaml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
  projects:
    - name: zmk
      remote: zmkfirmware
      revision: main
      import: app/west.yml
  self:
    path: config
```

---

## Configuration Examples

### Example 1: Basic Wireless Keyboard

**corne.conf:**
```ini
# Keyboard Identity
CONFIG_ZMK_KEYBOARD_NAME="My Corne"

# Bluetooth
CONFIG_ZMK_BLE=y
CONFIG_BT_CTLR_TX_PWR_PLUS_8=y

# Power Management
CONFIG_ZMK_SLEEP=y
CONFIG_ZMK_IDLE_TIMEOUT=30000
CONFIG_ZMK_IDLE_SLEEP_TIMEOUT=900000

# Battery
CONFIG_ZMK_BATTERY_REPORTING=y
```

### Example 2: Split Keyboard with RGB

**corne.conf:**
```ini
# Split Configuration
CONFIG_ZMK_SPLIT=y
CONFIG_ZMK_SPLIT_BLE=y

# RGB Underglow
CONFIG_ZMK_RGB_UNDERGLOW=y
CONFIG_WS2812_STRIP=y
CONFIG_ZMK_RGB_UNDERGLOW_EXT_POWER=y
CONFIG_ZMK_RGB_UNDERGLOW_ON_START=y
CONFIG_ZMK_RGB_UNDERGLOW_BRT_START=50
CONFIG_ZMK_RGB_UNDERGLOW_HUE_START=180
CONFIG_ZMK_RGB_UNDERGLOW_SAT_START=100
CONFIG_ZMK_RGB_UNDERGLOW_EFF_START=2

# Power saving for RGB
CONFIG_ZMK_RGB_UNDERGLOW_AUTO_OFF_IDLE=n
CONFIG_ZMK_RGB_UNDERGLOW_AUTO_OFF_USB=n
```

### Example 3: USB-Only Keyboard with Display

**keyboard.conf:**
```ini
# Disable Bluetooth
CONFIG_ZMK_BLE=n

# USB
CONFIG_ZMK_USB=y

# Display
CONFIG_ZMK_DISPLAY=y
CONFIG_ZMK_WIDGET_LAYER_STATUS=y
CONFIG_ZMK_WIDGET_BATTERY_STATUS=n
CONFIG_ZMK_WIDGET_OUTPUT_STATUS=y
CONFIG_ZMK_WIDGET_WPM_STATUS=y
```

### Example 4: Low Latency Gaming Setup

**keyboard.conf:**
```ini
# Fast debouncing
CONFIG_ZMK_KSCAN_DEBOUNCE_PRESS_MS=1
CONFIG_ZMK_KSCAN_DEBOUNCE_RELEASE_MS=5

# NKRO for gaming
CONFIG_ZMK_HID_REPORT_TYPE_NKRO=y

# Disable power saving
CONFIG_ZMK_SLEEP=n
CONFIG_ZMK_IDLE_TIMEOUT=0

# Disable lighting to reduce latency
CONFIG_ZMK_RGB_UNDERGLOW=n
```

### Example 5: Advanced Keymap with Hold-Tap

**keyboard.keymap:**
```dts
#include <behaviors.dtsi>
#include <dt-bindings/zmk/keys.h>
#include <dt-bindings/zmk/bt.h>

/ {
    behaviors {
        hm: homerow_mods {
            compatible = "zmk,behavior-hold-tap";
            label = "HOMEROW_MODS";
            #binding-cells = <2>;
            tapping-term-ms = <200>;
            quick-tap-ms = <150>;
            flavor = "balanced";
            bindings = <&kp>, <&kp>;
        };
    };

    keymap {
        compatible = "zmk,keymap";

        default_layer {
            bindings = <
                &kp Q       &kp W       &kp E       &kp R       &kp T
                &hm LGUI A  &hm LALT S  &hm LCTRL D &hm LSHFT F &kp G
                &kp Z       &kp X       &kp C       &kp V       &kp B
            >;
        };
    };
};
```

### Example 6: Combo Configuration

**keyboard.keymap:**
```dts
/ {
    combos {
        compatible = "zmk,combos";
        
        combo_esc {
            timeout-ms = <50>;
            key-positions = <0 1>;
            bindings = <&kp ESC>;
        };
        
        combo_tab {
            timeout-ms = <50>;
            key-positions = <10 11>;
            bindings = <&kp TAB>;
        };
    };
};
```

---

## Additional Resources

### Official Documentation
- [ZMK Firmware Documentation](https://zmk.dev/docs)
- [ZMK Configuration Overview](https://zmk.dev/docs/config)
- [ZMK GitHub Repository](https://github.com/zmkfirmware/zmk)
- [Zephyr Project Documentation](https://docs.zephyrproject.org)

### Community Resources
- [ZMK Discord Community](https://zmk.dev/community/discord/join)
- [Awesome ZMK](https://github.com/mctechnology17/awesome-zmk) - Curated list of ZMK resources
- [ZMK Cheat Sheet](https://peccu.github.io/zmk-cheat-sheet/)
- [Keymap Editor](https://nickcoutsos.github.io/keymap-editor/)

### Tools
- [ZMK Studio](https://zmk.studio) - Real-time configuration tool
- [Keymap Drawer](https://caksoylar.github.io/keymap-drawer) - Visual keymap generator

---

## Notes

1. **Compile-time Configuration**: All ZMK settings are applied at compile time. You must rebuild and flash firmware for changes to take effect.

2. **Priority**: User config files take precedence over default configurations.

3. **Split Keyboards**: Can use shared configs or separate configs for left/right halves.

4. **Validation**: Use the ZMK build system to validate your configuration before flashing.

5. **Defaults**: When a config option is not specified, ZMK uses sensible defaults defined in the firmware.

6. **Compatibility**: Some options may be hardware-specific and only work with certain boards or shields.

---

**Document Version**: 1.0  
**Last Updated**: 2025  
**ZMK Version**: Compatible with ZMK main branch
