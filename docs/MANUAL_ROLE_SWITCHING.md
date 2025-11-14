# Manual Role Switching Guide (Advanced)

## Warning

⚠️ **This is an advanced procedure** that requires creating custom shield definitions and is not recommended for most users. The standard left-as-central configuration is sufficient for nearly all use cases.

## Overview

This guide explains how to manually switch which half of your Corne keyboard acts as the central (USB-connected) device. This is **NOT automatic** - you must manually flash firmware and reset pairings each time you want to switch.

## Prerequisites

- Understanding of ZMK firmware architecture
- Ability to modify devicetree shield definitions
- Comfortable with flashing firmware and troubleshooting
- Patience (the switching process takes 15-20 minutes each time)

## Why This Is Complicated

The standard ZMK corne shields (`corne_left` and `corne_right`) have their central/peripheral roles defined in the upstream ZMK repository. To create a reversed configuration, you would need to:

1. Create custom shield definitions (e.g., `corne_left_as_peripheral` and `corne_right_as_central`)
2. Copy and modify the shield configuration files from the ZMK repository
3. Invert the keymap so the physical keys match the expected layout
4. Set up build configurations for both orientations
5. Maintain these custom shields as ZMK updates

## Alternatives

### Option A: Choose One Side (Recommended)
Simply decide that the left half will always be your central and always connect it to USB. This is how 95%+ of split keyboard users operate.

### Option B: Use a USB Hub/Dock
Keep a USB hub or dock on each side of your desk. Move your computer's USB cable to the appropriate hub. This lets you "switch sides" from the computer's perspective without re-flashing.

### Option C: Wait for ZMK Updates
Monitor the ZMK project for automatic role switching support. If this feature is added in the future, this repository can be updated to support it.

## Conclusion

Manual role switching is technically possible but impractical for regular use. The time and effort required to switch (15-20 minutes) makes it unsuitable as a solution for the original problem statement.

**Recommendation:** Use the standard left-as-central configuration and always connect the left half to USB. If you need the keyboard on the other side of your workspace, move the entire keyboard or use a longer USB cable.

For the vast majority of users, this is the most practical and reliable solution.
