# AGENTS.md - Iris Rev 8 Reverie Keymap Repository

This document provides essential information for agents working with this QMK firmware repository for the Keebio Iris Rev 8 keyboard running the "Reverie" custom keymap.

## Project Overview

This is a QMK firmware repository for the Keebio Iris Rev 8 split ortholinear keyboard with a custom productivity-focused keymap called "Reverie". The project features:

- Containerized builds using Podman/Docker for reproducible compilation
- Per-layer RGB lighting with distinct colors
- Advanced tap dance functionality
- Automated keymap visualization generation
- Custom macros including TURBO and JIGGLER functionality

## Essential Commands

### Build Firmware
```bash
./build.sh
```
This command:
- Downloads/updates QMK firmware
- Builds container environment 
- Compiles firmware UF2 file and keymap visualizations
- Outputs files to `./build-volume/build-output/`
- Copies new keymap images to `./assets/` folder

### Clean Build Artifacts
```bash
rm -rf build-volume/qmk_firmware/.build
```

### Check Container Runtime
```bash
podman info
```

## Core Files and Structure

### Keymap Files
- `keymap.c` - Main keymap definition with layer layouts, tap dances, and custom keycodes
- `config.h` - Hardware configuration and feature flags
- `rules.mk` - QMK build configuration and feature enables
- `keymap-drawer-config.yaml` - Visualization styling configuration

### Build System
- `build.sh` - Main build script that orchestrates the entire build process
- `Containerfile` - Container definition with QMK dependencies
- `entry.sh` - Container entry point script that handles QMK setup and compilation
- `.gitignore` - Excludes `build-volume/`, `.env`, and `TODO.md`

### Generated Content
- `./build-volume/build-output/` - Compiled UF2 firmware and generated assets
- `./assets/` - Keymap visualization images (PNG/SVG) used in README.md

## Keymap Architecture

### Layer System
The keymap uses 7 layers with specific naming conventions:

```c
enum iris_layers {
    _BASE,        // QWERTY base layer (Purple)
    _FUNCTION,    // Function keys (Green) 
    _NUMBERS,     // Numpad and F-keys (Blue)
    _SYMBOLS,     // Symbols and navigation (Red)
    _SYSTEM,      // Mouse/media controls (Yellow)
    _GAMING,      // Gaming layout (Turquoise)
    _MACRO,       // Macros and RGB controls (Pink)
};
```

**IMPORTANT**: When adding new layers, follow the 8-step pattern documented in `keymap.c:15-23`.

### Tap Dance System
Extensive tap dance functionality for layer switching and dual-purpose keys:
- Numbers 1-5 double-hold switches to respective layers
- Grave double-tap for Escape
- Left Shift double-tap for Caps Lock
- Various utility tap dances for punctuation and media controls

### RGB Lighting
Per-layer RGB lighting with HSV color definitions matching the visualization colors. RGBLIGHT_ENABLE must be `yes` and RGB_MATRIX_ENABLE must be `no`.

## Build Process Flow

1. **Setup**: `build.sh` copies keymap files to build volume
2. **Container Build**: Creates QMK build environment with all dependencies
3. **QMK Setup**: Clones/updates QMK firmware, installs requirements, initializes submodules
4. **Compilation**: Builds firmware UF2 file for `keebio/iris/rev8` keyboard
5. **Visualization**: Generates keymap diagrams using keymap-drawer tool
6. **Asset Management**: Copies generated images to assets folder

## Development Patterns

### Adding New Layers
1. Add enum entry in `_iris_layers` with `_PREFIX` format
2. Add layer alias `#define LAYER_NAME _LAYER_NAME`
3. Define HSV color constant
4. Add to `keymaps[]` array in correct order
5. Add to `MY_LIGHT_LAYERS` array
6. Add case to `layer_state_set_user()` function
7. Add CSS styling in `keymap-drawer-config.yaml`
8. Add text contrast rule for proper readability

### Custom Keycodes
Custom keycodes are defined in `enum custom_keycodes` with `SAFE_RANGE`. Current implementations:
- `TURBO` - Toggle rapid-fire functionality
- `JIGGLER` - Toggle mouse jiggling

### Configuration Management
- Split keyboard settings in `config.h` (EE_HANDS, SPLIT_LAYER_STATE_ENABLE)
- Feature toggles in `rules.mk` (RGBLIGHT_ENABLE, TAP_DANCE_ENABLE, etc.)
- Build-time hardware configuration in `entry.sh` (QMK_KEYBOARD, QMK_KEYMAP)

## Testing and Validation

### Build Validation
- Build script exits on any failure
- Container ensures reproducible builds
- Generated UF2 file should appear in `./build-volume/build-output/`

### Visual Validation  
- Keymap visualizations automatically generated
- Individual layer images created for each defined layer
- Images copied to `./assets/` for README.md display

## Troubleshooting

### Build Issues
- Ensure Podman is running: `podman info`
- Check container logs for detailed errors
- Verify all keymap files are present and syntactically correct
- Clean build artifacts if needed

### Flashing Issues
- Both keyboard halves must be in bootloader mode (double-press reset)
- Verify UF2 file size and integrity
- Try different USB cables if drives don't appear

## Tools and Dependencies

### Container Dependencies
- QMK CLI tools and Python environment
- AVR/ARM toolchains for compilation
- keymap-drawer for visualization generation
- ImageMagick for SVG to PNG conversion

### External Tools
- Podman or Docker for containerization
- Git for QMK repository management

## Special Considerations

- The build process is fully containerized for reproducibility
- Layer names are automatically extracted from keymap.c enum for visualization
- RGB lighting colors are coordinated between code and visualization
- The repository includes QuantumDuck tool for converting Ducky Scripts to QMK macros
- All generated content is excluded from version control via .gitignore