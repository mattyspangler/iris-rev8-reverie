# AGENTS.md

This document provides essential information for AI agents working with the Iris Rev 8 QMK keymap repository.

## Project Overview

This is "Reverie" - a sophisticated custom QMK firmware keymap for the Keebio Iris Rev 8 split ergonomic keyboard, created by Matthew Spangler. It features a 6-layer productivity-focused layout with advanced RGB lighting, tap dance functionality, custom macros, and automatic keymap visualization generation.

## Build System & Architecture

### Containerized Build Process
This project uses a reproducible containerized build system:
1. **Primary build**: `./build.sh` - Complete automated build using Podman
2. **Container**: `Containerfile` - Debian-based with QMK toolchain, keymap-drawer, ImageMagick
3. **Entry script**: `entry.sh` - Handles QMK setup, compilation, and visualization
4. **Outputs**: 
   - UF2 firmware in `./build-volume/build-output/`
   - Keymap visualizations in `./assets/` (PNG/SVG)

### Build Workflow
```bash
./build.sh  # Complete build with firmware + visualizations
```

The build process:
1. Clones/updates QMK firmware repository
2. Builds reproducible container environment
3. Compiles firmware for keebio/iris/rev8 with "reverie" keymap
4. Generates keymap visualizations using keymap-drawer
5. Copies assets to repo root for README display

## Key Components

### Core Files
- **keymap.c** (608 lines) - Complete keymap with layers, tap dances, RGB
- **config.h** - Hardware configuration (68 LEDs, split settings)
- **rules.mk** - Feature flags (RGBLIGHT_ENABLE=yes, TAP_DANCE_ENABLE=yes)
- **build.sh** - Build orchestrator with asset copying
- **Containerfile** - Reproducible build environment
- **entry.sh** - Container script with QMK compilation + visualization
- **keymap-drawer-config.yaml** - Visualization configuration

### Tooling
- **QuantumDuck/** - Ducky Script to QMK converter tool
- **assets/** - Auto-generated keymap visualizations
- **build-volume/** - Container build artifacts

## Keymap Architecture

### Layer System (6 layers)
1. **QWERTY (Layer 0)** - Purple RGB - Base typing with advanced tap dances
2. **NUM (Layer 1)** - Red RGB - F-keys, numpad, basic mouse controls
3. **SYM_NAV (Layer 2)** - Azure RGB - Symbols and navigation combined
4. **MEDIA_MOUSE (Layer 3)** - Orange/Yellow RGB - Media controls and advanced mouse
5. **GAMING (Layer 4)** - Blue RGB - Clean gaming layout
6. **MACRO (Layer 5)** - White RGB - Custom utilities (TURBO, JIGGLER, reset)

### Special Features
- **Tap Dance System**: Numbers 1-5 double-hold for layer switching, plus utility dances
- **RGB Lighting**: 68 LEDs with per-layer HSV colors using RGBLIGHT layers
- **Split Keyboard**: EE_HANDS for automatic handedness detection
- **Custom Macros**: TURBO (rapid-fire) and JIGGLER (mouse movement simulator)
- **Momentary Layers**: Toggle access via bracket keys
- **Auto-visualization**: PNG generation matching RGB layer colors

### RGB Architecture
- Each keymap layer has corresponding RGB light layer
- Specific HSV colors: QWERTY (Purple), NUM (Red), SYM_NAV (Azure), MEDIA_MOUSE (Orange), GAMING (Blue), MACRO (White)
- 68 total LEDs with detailed index mapping in comments
- Layer state changes trigger automatic RGB updates

## Development Guidelines

### Code Conventions
- Use `_______` for transparent keys (readability over `KC_TRNS`)
- Layer aliases defined (`QWERTY_LAYER`, etc.)
- ASCII art comments for visual layout mapping
- Structured tap dance implementation with helper functions
- Comprehensive LED index documentation

### Naming Conventions
- Tap dances: `TD_X_LY` format (character + layer)
- Layers: Descriptive names with underscores
- RGB layers: Match keymap layer naming
- Custom keycodes: Uppercase descriptive names

### Build Configuration Rules
- RGBLIGHT_ENABLE must be `yes` for RGB layers
- RGB_MATRIX_ENABLE must be `no` (conflicts with RGBLIGHT)
- LTO_ENABLE enabled for firmware size optimization
- MOUSEKEY_ENABLE required for mouse functionality
- SPLIT_LAYER_STATE_ENABLE for split layer synchronization

## Common Tasks

### Building Firmware
```bash
./build.sh  # Complete build with visualizations
```
Handles: QMK repo management, container build, compilation, UF2 generation, keymap visualization.

### Adding New Layer
1. Add enum to `iris_layers`
2. Define layer alias (`#define NEW_LAYER _NEW_LAYER`)
3. Create keymap layout in `keymaps[]`
4. Add RGB light layer definition with HSV colors
5. Update `MY_LIGHT_LAYERS` array
6. Update `layer_state_set_user()` function

### Adding Tap Dance
1. Add to `tap_dance_codes` enum
2. Implement `finished` and `reset` functions
3. Add to `tap_dance_actions` array
4. Use `TD()` macro in keymap

### Flashing Firmware
1. Double-press reset buttons on both halves
2. Copy `keebio_iris_rev8_reverie.uf2` to both USB drives
3. Keyboards auto-reboot with new firmware

## Keymap Visualization System

### Automatic Generation
- Uses keymap-docker to convert QMK C keymap to JSON, then to SVG/PNG
- Individual layer PNGs generated with descriptive names
- Colors match RGB layer schemes
- Assets automatically copied to repo root `./assets/`

### Visualization Files
- `assets/keymap.png` - Complete keyboard layout
- `assets/keymap-{layer}.png` - Individual layer layouts
- `assets/*.svg` - Source SVG files

## Container Dependencies

### Build Tools
- QMK firmware build environment
- ARM/AVR cross-compilers (gcc-arm-none-eabi, gcc-avr)
- Python3 with keymap-drawer
- ImageMagick for SVG→PNG conversion
- Git and build essentials

### Important Container Details
- Fixed environment ensures reproducible builds
- All visualization tools pre-installed
- No conditional tool detection needed
- Build fails fast if dependencies missing

## Troubleshooting

### Build Issues
- **RGB not working**: Verify RGBLIGHT_ENABLE=yes and RGB_MATRIX_ENABLE=no in rules.mk
- **Compilation fails**: Check container logs, clean with `rm -rf build-volume/qmk_firmware/.build`
- **Layer switching broken**: Verify SPLIT_LAYER_STATE_ENABLE in config.h
- **Visualization missing**: Check keymap-drawer installation and JSON conversion

### Flashing Issues
- Both halves must be in bootloader mode (double-tap reset)
- Try different USB cables/ports
- Verify UF2 file integrity
- Check for filesystem mounting issues

### Common Fixes
- Remove conflicting `keymap.json`/`keymap.yaml` files (handled automatically)
- Rebuild container: `podman build -t qmkbuild -f Containerfile .`
- Clean QMK build: `rm -rf build-volume/qmk_firmware`

## Repository Context

This is a mature, well-documented keyboard configuration focused on productivity and gaming. The layer system provides efficient access to symbols, navigation, and media controls while maintaining a clean base layer. The containerized build system ensures reproducible compilation, while automatic visualization generation makes the layout easily shareable and documentable.

The keymap represents a sophisticated approach to split keyboard ergonomics with extensive customization and professional-grade tooling.