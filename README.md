# Iris Reverie

My Keebio Iris Rev 8 custom keymap called "Reverie" -- a productivity-focused layout with RGB lighting and tap dance functionality.

![My Iris Rev 8 alongside my other daily driver trackballs and keyboards](keyboard-pic.jpg "My Iris Rev 8")

## Features

- **Per-layer RGB lighting** with distinct colors for each layer
- **Tap dance keys** for advanced functionality (numbers 1-5 switch layers on double-hold)
- **Containerized builds** using Podman for reproducible compilation
- **keymap-drawer integration** that automatically generates a PNG cheatsheet of all keymap layers
- **Custom macros** including TURBO and JIGGLER functionality

## Layer Architecture

![Complete Keymap](assets/keymap.png "Complete Reverie Keymap")

## Tap Dance Keys

| Key | Variable | Behavior |
|-----|----------|----------|
| `~`/`Esc` | `TD(TD_GRV_ESC)` | Single tap: `~`, Double tap: `Esc` |
| `1` | `TD(TD_1_FN)` | Single tap: `1`, Double-hold: Switch to FUNCTION layer |
| `2` | `TD(TD_2_NUM)` | Single tap: `2`, Double-hold: Switch to NUMBERS layer |
| `3` | `TD(TD_3_SYS)` | Single tap: `3`, Double-hold: Switch to SYSTEM layer |
| `4` | `TD(TD_4_GAME)` | Single tap: `4`, Double-hold: Switch to GAMING layer |
| `5` | `TD(TD_5_MACRO)` | Single tap: `5`, Double-hold: Switch to MACRO layer |
| `6` | `TD(TD_6_BS)` | Single tap: `6`, Double-hold: Switch to BASE layer |
| `9` | `TD(TD_9_MIN)` | Single tap: `9`, Tap-hold: `-` |
| `0` | `TD(TD_0_EQ)` | Single tap: `0`, Tap-hold: `=` |
| `Enter` | `TD(TD_ENT_BSLS)` | Single tap: `Enter`, Tap-hold: `\` |
| `\` | `TD(TD_BSLS_RSFT)` | Single tap: `\`, Tap-hold: `Right Shift` |
| `Left Shift` | `TD(TD_LSFT_CAPS)` | Single tap: `Left Shift`, Double tap: `Caps Lock` |
| `Left Ctrl` (Gaming layer) | `TD(TD_LCTL_GAME)` | Single tap: `Left Ctrl`, Double-hold: Switch to GAMING layer |
| `Left Ctrl` (Function layer) | `TD(TD_LCTL_BASE)` | Single tap: `Left Ctrl`, Double-hold: Switch to BASE layer |
| `Media Previous` | `TD(TD_MEDIA_PREV)` | Single tap: `Media Previous`, Double tap: `Browser Back` |
| `Media Play/Pause` | `TD(TD_MEDIA_PLAY)` | Single tap: `Media Play/Pause`, Double tap: `Browser Home` |
| `Media Next` | `TD(TD_MEDIA_NEXT)` | Single tap: `Media Next`, Double tap: `Browser Forward` |

## Build Instructions

Podman is required by build.sh.

### Building Firmware

1. **Clone or navigate to the repository**

2. **Run the build script:**
   ```bash
   ./build.sh
   ```

3. **The build process will:**
   - Download/Update QMK firmware
   - Build the container environment
   - Compile your firmware uf2 and keymap png/svg images
   - Output the files to `./build-volume/build-output/`
   - Copy the new keymap image to the assets folder so it will show in README.md

### Flashing Firmware

1. **Prepare both keyboard halves:**
   - Double-press the reset button under each half
   - Each half will appear as a USB storage device

2. **Flash the firmware:**
   - Mount both keyboard filesystems
   - Copy the `keebio_iris_rev8_reverie.uf2` file to both halves
   - The keyboards will automatically reboot with the new firmware

## Troubleshooting

### Build Issues
- Ensure Podman is running: `podman info`
- Clean build artifacts: `rm -rf build-volume/qmk_firmware/.build`
- Check container logs for detailed error messages

### Flashing Issues
- Ensure both halves are in bootloader mode (reset button double-press)
- Try different USB cables if the drives don't appear
- Verify the UF2 file size
