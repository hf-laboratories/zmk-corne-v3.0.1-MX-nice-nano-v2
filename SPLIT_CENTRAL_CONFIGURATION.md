# Split Keyboard Central Configuration Guide

## Request: Both Halves as Central with USB Auto-Detection

### The Request
The goal was to configure both halves of the Corne keyboard as central, with automatic role switching based on USB connection:
- When USB is connected to the left half: operate normally (left=central, right=peripheral)
- When USB is connected to the right half: swap roles (right=central, left=peripheral) with inverted keymap

### Why This Isn't Possible with ZMK

**ZMK firmware does not support automatic USB-based role detection or switching.** This is a fundamental limitation of the current ZMK architecture.

#### Technical Limitations

1. **Fixed Roles at Compile Time**
   - Split keyboard roles (central vs peripheral) are determined at firmware compile time
   - The role is baked into the firmware via `CONFIG_ZMK_SPLIT_ROLE_CENTRAL` setting
   - Cannot be changed at runtime based on USB connection status

2. **Only Central Can Communicate with Host**
   - Only the half flashed as "central" can act as a USB keyboard
   - The peripheral half, even when connected via USB, cannot present itself as a keyboard device
   - USB on peripheral is only used for charging and firmware flashing

3. **No USB Detection Logic**
   - ZMK does not have built-in logic to detect which half is connected via USB
   - No mechanism exists to dynamically switch roles or remap the keymap based on USB connection

4. **Architecture Design**
   - The split architecture assumes one half is always central and handles all HID communication
   - Peripherals only send matrix scan data to the central
   - Changing this would require fundamental firmware architecture changes

#### Community Discussion

This feature has been requested by the ZMK community multiple times, but remains unimplemented:
- Feature requests exist but are not on the immediate roadmap
- Would require substantial firmware development
- May conflict with other ZMK features and assumptions

### Available Workarounds

While automatic role switching isn't possible, here are the available options:

#### Option 1: Choose One Central (Recommended)
**Best for most users**

Simply decide which half will always be your central (typically left) and always plug that half into USB. This is the standard ZMK split keyboard configuration.

- ✅ Simple and reliable
- ✅ No extra flashing or configuration needed
- ✅ Current configuration already supports this
- ❌ Must always use the same half for USB connection

#### Option 2: Manual Firmware Swapping (Advanced)
**For users who need to switch USB sides occasionally**

This approach requires maintaining two sets of firmware builds and manually re-flashing when you want to switch which side connects via USB.

**Setup Required:**
1. Create two firmware build sets:
   - Set A: Left as central, Right as peripheral (standard)
   - Set B: Right as central, Left as peripheral (reversed)

2. For Set B, create an inverted keymap where:
   - The right side's keymap matches what the left side normally has
   - The left side's keymap matches what the right side normally has

3. When switching USB sides:
   - Flash both halves with the appropriate firmware set
   - Reset Bluetooth pairings on both halves
   - Re-pair the halves with each other
   - Re-pair with your computer

**Pros:**
- ✅ Can use either half with USB
- ✅ Maintains full split functionality

**Cons:**
- ❌ Requires manual re-flashing (10-15 minutes process)
- ❌ Need to maintain two separate firmware configurations
- ❌ Must clear Bluetooth pairings each time
- ❌ Cannot hot-swap; requires full re-configuration

#### Option 3: Independent Halves (Not Recommended)
**For extreme use cases only**

Configure each half as a completely independent keyboard (non-split mode).

**Pros:**
- ✅ Both halves work independently via USB

**Cons:**
- ❌ Loses all split keyboard features
- ❌ No communication between halves
- ❌ Layers don't sync
- ❌ Each half appears as separate keyboard to OS
- ❌ Complex keymap management
- ❌ Not the intended use case for split keyboards

### Recommended Configuration

For this repository, we recommend **Option 1** (standard left-as-central configuration), which is already implemented.

**Current Configuration:**
- Left half: Central (connects to computer via USB or Bluetooth)
- Right half: Peripheral (connects wirelessly to left half)
- Full keymap functionality across both halves
- ZMK Studio support for easy keymap editing

**To use your keyboard:**
1. Power on both halves
2. Connect the **left half** to your computer via USB or Bluetooth
3. Both halves will communicate via Bluetooth automatically
4. All keys on both halves will work as expected

### Future Possibilities

If ZMK adds support for automatic role switching in the future, this repository can be updated. Monitor these resources:

- [ZMK GitHub Repository](https://github.com/zmkfirmware/zmk)
- [ZMK Discord Community](https://zmk.dev/community/discord/invite)
- [ZMK Split Keyboard Documentation](https://zmk.dev/docs/features/split-keyboards)

### Technical Reference

For those interested in the technical details:

**Current Build Configuration** (build.yaml):
```yaml
include:
  - board: nice_nano_v2
    shield: corne_left    # Central role defined in ZMK shield
  - board: nice_nano_v2
    shield: corne_right   # Peripheral role defined in ZMK shield
```

**Relevant Configuration Options:**
- `CONFIG_ZMK_SPLIT=y` - Enables split keyboard support
- `CONFIG_ZMK_SPLIT_BLE=y` - Uses Bluetooth for split communication
- `CONFIG_ZMK_SPLIT_ROLE_CENTRAL` - Set by the shield definition (corne_left vs corne_right)

The central/peripheral designation comes from the ZMK shield definitions themselves, which are part of the upstream ZMK firmware repository.

### Conclusion

While automatic USB-based role switching would be a convenient feature, it is not currently possible with ZMK firmware. The standard left-as-central configuration provides reliable split keyboard functionality. Users who absolutely need to switch USB sides can use the manual firmware swapping approach, though this is cumbersome and not recommended for regular use.

For most users, choosing one half as your permanent central and consistently using it for USB connectivity is the best approach.
