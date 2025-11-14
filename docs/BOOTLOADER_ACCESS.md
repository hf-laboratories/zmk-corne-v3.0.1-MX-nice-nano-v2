# Bootloader Access Guide

## Overview

This keyboard is configured with convenient key combinations to enter bootloader mode for firmware flashing. You no longer need to physically access the reset button on your nice!nano controllers.

## Accessing Bootloader Mode

### Via Keymap (Recommended)

To enter bootloader mode on either half:

1. **Hold Lower + Raise** to access the Adjust layer (Layer 3)
2. **Press the bootloader key** for the half you want to flash:
   - **Left half bootloader**: 6th key on the second row (left side) - where 'T' would be shifted right
   - **Right half bootloader**: 1st key on the second row (right side) - where 'Y' would be
3. The half will disconnect and appear as a USB drive named "NICENANO"
4. Drag and drop the firmware `.uf2` file to flash

### Key Positions

```
Adjust Layer (Hold Lower + Raise):

Left Half:                    Right Half:
┌────┬────┬────┬────┬────┬────┐  ┌────┬────┬────┬────┬────┬────┐
│ F1 │ F2 │ F3 │ F4 │ F5 │ F6 │  │ F7 │ F8 │ F9 │F10 │F11 │F12 │
├────┼────┼────┼────┼────┼────┤  ├────┼────┼────┼────┼────┼────┤
│RGB │HUI │SAI │BRI │SPI │BTLD│  │BTLD│    │    │    │    │    │
├────┼────┼────┼────┼────┼────┤  ├────┼────┼────┼────┼────┼────┤
│TOG │HUD │SAD │BRD │SPD │RST │  │RST │    │    │    │    │    │
└────┴────┴────┼────┼────┼────┤  ├────┼────┼────┼────┴────┴────┘
               │    │    │    │  │    │    │    │
               └────┴────┴────┘  └────┴────┴────┘

BTLD = Bootloader key (enter bootloader mode)
RST  = Soft reset key (restart firmware)
```

### Reset Keys (Soft Reset)

Also on the Adjust layer, there are soft reset keys:
- **Left half reset**: 6th key on the third row (left side)
- **Right half reset**: 1st key on the third row (right side)

These perform a soft reset (restart the firmware) without entering bootloader mode. Useful for:
- Restarting the keyboard after configuration changes
- Recovering from a frozen state
- Resetting without re-flashing

## When to Use Each Method

### Use Bootloader Keys When:
✅ Flashing new firmware  
✅ Updating to a new keymap  
✅ The keyboard is responsive and working

### Use Physical Reset Button When:
✅ The keyboard is completely unresponsive  
✅ The firmware is corrupted and keys don't work  
✅ You haven't flashed the firmware with bootloader keys yet

## Physical Reset Button (Fallback)

If the keyboard is unresponsive and the bootloader keys don't work:

1. Locate the reset button on your nice!nano (small button labeled RST or RESET)
2. **Double-tap** the reset button quickly
3. The controller will enter bootloader mode
4. The board will appear as "NICENANO" USB drive

## Flashing Process

1. **Enter bootloader mode** using one of the methods above
2. Wait for the "NICENANO" drive to appear
3. **Drag and drop** the appropriate `.uf2` firmware file:
   - Left half: Flash with `*_left*.uf2` file
   - Right half: Flash with `*_right*.uf2` file
4. The board will automatically reboot with new firmware
5. The USB drive will disappear when flashing is complete

## Important Notes

### For Split Keyboards
- Each half must be flashed independently
- The bootloader key on the left side only affects the left controller
- The bootloader key on the right side only affects the right controller
- When flashing both halves, do one at a time

### After Flashing
- If you flash major changes, you may need to:
  - Clear Bluetooth pairings (use BT_CLR on Layer 1)
  - Re-pair both halves with each other
  - Re-pair with your computer

### ZMK Studio
- This keyboard supports ZMK Studio for live keymap editing
- You can modify the bootloader key positions using ZMK Studio
- Access ZMK Studio at [zmk.studio](https://zmk.studio) when connected via USB

## Troubleshooting

**Problem**: Bootloader key doesn't work  
**Solution**: 
1. Make sure you're holding Lower + Raise to access the Adjust layer
2. Try the other reset method (physical button)
3. Check if the firmware is corrupted - re-flash using physical reset

**Problem**: Wrong half enters bootloader  
**Solution**: 
- Make sure you're pressing the bootloader key on the correct side
- Left side bootloader key is on the left half, right side key is on the right half

**Problem**: USB drive doesn't appear  
**Solution**:
1. Try a different USB cable
2. Try a different USB port
3. Make sure you double-tapped the reset button quickly
4. Check that your computer recognizes USB drives

## Summary

With the bootloader keys configured in the keymap, you have easy access to firmware flashing without needing to physically access the reset buttons on your controllers. This makes updates and keymap changes much more convenient!

**Quick Reference:**
- **Bootloader**: Hold Lower + Raise, then press bootloader key (6th position on row 2 for each half)
- **Soft Reset**: Hold Lower + Raise, then press reset key (6th position on row 3 for each half)
- **Physical Reset**: Double-tap the RST button on the nice!nano
