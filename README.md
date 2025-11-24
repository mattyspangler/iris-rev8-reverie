# Iris Reverie

My Keebio Iris Rev 8 custom keymap called "Reverie" -- a productivity-focused layout with RGB lighting and tap dance functionality.

![My Iris Rev 8](keyboard-pic.jpg "My Iris Rev 8")

## Features

- **Per-layer RGB lighting** with distinct colors for each layer
- **Tap dance keys** for advanced functionality (numbers 1-5 switch layers on double-hold)
- **Containerized builds** using Podman for reproducible compilation
- **keymap-drawer integration** that automatically generates a PNG cheatsheet of all keymap layers
- **Custom macros** including TURBO and JIGGLER functionality

## Layer Architecture

![Complete Keymap](assets/keymap.png "Complete Reverie Keymap")

### QWERTY (Layer 0) - Purple

**Base typing layer with advanced tap dance functionality:**

#### Tap Dance Functions
- **`~` (grave)**: Single tap for `~`, double tap for `Esc`
- **`1`**: Single tap for `1`, double-tap and hold for FUNCTION layer
- **`2`**: Single tap for `2`, double-tap and hold for NUMBERS layer  
- **`3`**: Single tap for `3`, double-tap and hold for SYSTEM layer
- **`4`**: Single tap for `4`, double-tap and hold for GAMING layer
- **`5`**: Single tap for `5`, double-tap and hold for MACRO layer
- **`6`**: Single tap for `6`, double-tap and hold for BASE layer
- **`9`**: Single tap for `9`, double-tap and hold for minus (-)
- **`0`**: Single tap for `0`, double-tap and hold for equals (=)
- **`Enter`**: Single tap for Enter, double-tap and hold for backslash (\)
- **`Backslash`**: Single tap for backslash (\), double-tap and hold for right shift
- **`Left Shift`**: Single tap for shift, double tap for `Caps Lock`
- **`Left Ctrl`**: Single tap for ctrl, double-tap and hold for BASE layer
- **Media keys**: Double-tap for browser navigation (back/home/forward)

#### Momentary Layers
- **`[` (left bracket)**: Hold for temporary NUM layer access
- **`]` (right bracket)**: Hold for temporary NUM layer access

### NUMBERS (Layer 1) - Green

**Numpad and F-key layout:**

- **Top row**: F10-F12, Print Screen, Scroll Lock
- **Right side**: Full numpad layout with mathematical operators (+, -, *, /)
- **Navigation**: Page Up/Down, Home, End, Insert, Delete
- **Function keys**: F1-F9 in left side cluster

### SYMBOLS (Layer 2) - Red

**Symbols and navigation:**

- **Right side**: Symbol characters and brackets
- **Navigation**: Arrow keys (up, down, left, right)
- **Media controls**: Volume down, mute, volume up in thumb cluster


### SYSTEM (Layer 3) - Yellow

**System administration and media:**

- **Mouse controls**: Precise mouse movement and scrolling
- **My Computer**: Quick access to file explorer
- **Media controls**: Previous track, play/pause, next track
- **Audio controls**: Volume down, mute, volume up
- **Browser navigation**: Media keys double-tap for browser back/home/forward

### GAMING (Layer 4) - Blue

**Dedicated gaming layout:**

- **Clean WASD**: Standard FPS gaming controls
- **Number row**: Standard 1-0 number keys
- **Punctuation**: Standard punctuation layout
- **Minimal interference**: No complex modifiers during gaming

### MACRO (Layer 5) - Pink

**Macros, RGB, and music:**

- **Dynamic Macros**: Record/play macros 1 and 2
- **Music Controls**: Music on/off, next track, toggle
- **RGB Controls**: Brightness up/down, toggle, mode forward
- **Auto Shift**: AS_TOGG for automatic capitalization
- **Layer Navigation**: Quick return to BASE and GAMING layers
- **Macro Keys**: `T` for TURBO toggle, `J` for JIGGLER toggle

## Build Instructions

### Prerequisites
- Podman (or Docker) for containerized builds
- Git for cloning repositories

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
