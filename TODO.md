# TODO.md

## Current Status

**Task**: Troubleshoot a build issue with keymap-drawer where it's failing to generate keymap visualizations for an Iris Rev 8 keyboard.

**Error**: `Could not find layout "QWERTY" in available physical layouts, available options are: ['LAYOUT']`

**Current Progress**: 
- ✅ Firmware compilation succeeds (UF2 file generated)
- ✅ Main keymap visualization generation works (keymap.png and keymap.svg)
- ✅ Fixed layout specification issue by explicitly using `-k keebio/iris/rev8 -l LAYOUT`
- ✅ Build completes successfully with main visualization
- ❌ Individual layer generation still failing with argument parsing error

**What Was Fixed**: 
- Modified entry.sh to explicitly specify layout parameters in draw commands (lines 92 and 106)
- Added `-k keebio/iris/rev8 -l LAYOUT` to both complete and individual layer draw commands
- Fixed flag from `--layers` to `-s` for layer selection
- Main keymap visualization now generates correctly

**What Remains to Be Done**: 
1. Fix individual layer generation command syntax in entry.sh
2. Verify that all 6 individual layer images are generated correctly
3. Clean up any debug output that was added during troubleshooting

## Files & Changes

**Files Modified**:
- `/home/nebula/Coding/iris-rev8-fun/entry.sh`: 
  - Modified to explicitly specify layout parameters in draw commands (lines 92 and 106)
  - Removed debug output (lines 87-88 in an earlier iteration)
  - Changed individual layer generation from `-l "$layer_name"` to `--layers "$layer_name"` (line 106)
  - Added `-k keebio/iris/rev8 -l LAYOUT` to both complete and individual layer draw commands

**Files Read/Analyzed**:
- `/tmp/keymap-drawer/README.md`: Documentation showing keymap-drawer usage and installation
- `/tmp/keymap-drawer/KEYMAP_SPEC.md`: YAML specification for keymap format
- `/tmp/keymap-drawer/resources/qmk_keyboard_mappings.yaml`: QMK keyboard aliases
- `/home/nebula/Coding/iris-rev8-fun/keymap.c`: Main keymap file with 6 layers (QWERTY, NUM, SYM_NAV, MEDIA_MOUSE, GAMING, MACRO)
- `/home/nebula/Coding/iris-rev8-fun/keymap-drawer-config.yaml`: Styling configuration

**Key Files Not Yet Touched**:
- Individual layer SVG/PNG files (may need generation)
- The UF2 file generation (working correctly)

**File Paths and Important Code Locations**:
- `/home/nebula/Coding/iris-rev8-fun/entry.sh:92-94` - Complete keymap draw command with explicit layout specs
- `/home/nebula/Coding/iris-rev8-fun/entry.sh:106` - Individual layer draw command
- `/home/nebula/Coding/iris-rev8-fun/keymap.c:18-25` - Layer definitions
- `/home/nebula/Coding/iris-rev8-fun/keymap.c:237-307` - Layer implementations using LAYOUT()

## Technical Context

**Architecture Decisions Made**:
- Containerized build process using Podman
- Explicitly specify layout parameters to avoid keymap-drawer confusing layer names with layout names
- Use `-k keebio/iris/rev8 -l LAYOUT` to explicitly specify physical layout and layout name

**Patterns Being Followed**:
- YAML construction with explicit layout section followed by layers section
- CLI parameter overrides for layout specification
- Debugging by examining error messages and YAML structure

**Libraries/Frameworks Being Used**:
- QMK CLI for firmware compilation
- keymap-drawer 0.22.1 for keymap visualization
- Pydantic for validation
- ImageMagick for SVG to PNG conversion

**Commands That Worked**:
- `qmk c2json -kb keebio/iris/rev8 -km reverie -o /tmp/keymap.json`
- `keymap parse -q /tmp/keymap.json --layer-names QWERTY NUM SYM_NAV MEDIA_MOUSE GAMING MACRO -o /tmp/logical_layers.yaml`
- `keymap -c config.yaml draw -k keebio/iris/rev8 -l LAYOUT /tmp/final_keymap.yaml -o keymap.svg`

**Commands That Failed**:
- `keymap draw keymap.yaml` (initial attempt - error: Could not find layout "QWERTY")
- Individual layer generation with `-l` flag (error: invalid option)
- Individual layer generation with `--layers` flag (error: unrecognized option)

**Environment Details**:
- Python 3.13 in container
- keymap-drawer 0.22.1
- QMK Firmware 0.30.12
- Debian stable-slim container
- Podman runtime

## Strategy & Approach

**Overall Approach**:
1. Identified that keymap-drawer was treating layer names as layout names
2. Fixed by explicitly specifying layout parameters in CLI commands
3. Used CLI parameter overrides instead of relying on YAML layout field

**Why This Approach Chosen**:
- The error showed keymap-drawer looking for "QWERTY" as a layout name
- CLI overrides take precedence over YAML layout field
- This avoids modifying the generated YAML structure

**Key Insights or Gotchas Discovered**:
- keymap-drawer distinguishes between physical layouts and logical layers
- Layer names (QWERTY, NUM, etc.) are not the same as layout names (LAYOUT)
- The `--layers` flag is not a valid option in keymap-drawer

**Assumptions Made**:
- keebio/iris/rev8 has only one physical layout called "LAYOUT"
- The layer names in keymap.c are correctly defined
- keymap-drawer should work with explicit layout specifications

**Blockers or Risks Identified**:
- CLI flag compatibility issues between keymap-drawer versions
- Build process takes several minutes, making iteration slow

## Exact Next Steps

1. **Check if individual layer images were generated**:
   ```bash
   ls -la ./assets/
   ```

2. **If individual layers are missing, fix the individual layer generation**:
   ```bash
   # Try different flag combinations
   keymap -c keymap-drawer-config.yaml draw -k keebio/iris/rev8 -l LAYOUT --layer QWERTY /tmp/final_keymap.yaml -o ./assets/keymap-qwerty.svg
   ```

3. **Test all 6 layers**:
   ```bash
   for layer in QWERTY NUM SYM_NAV MEDIA_MOUSE GAMING MACRO; do
     keymap -c keymap-drawer-config.yaml draw -k keebio/iris/rev8 -l LAYOUT --layer "$layer" /tmp/final_keymap.yaml -o "./assets/keymap-${layer,,}.svg"
   done
   ```

4. **Clean up debug output**:
   ```bash
   # Remove any remaining debug lines from entry.sh
   ```

5. **Final verification**:
   ```bash
   ls -la ./assets/
   # Should show 12 files (6 SVG + 6 PNG files)
   ```