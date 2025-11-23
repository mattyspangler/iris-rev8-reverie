# TODO - Keymap Issues and Improvements

## High Priority Issues

### 1. Incorrect HSV Color Values
- **Line 49**: `HSV_NUMBERS_BLUE 0, 255, 255` - This is actually RED (HSV hue 0) not blue
  - Should be something like `240, 255, 255` for actual blue to match "#2000ff"
- **Line 50**: `HSV_SYMBOLS_RED 0, 255, 255` - This is correct for red
- **Line 51**: `HSV_SYSTEM_YELLOW 44, 255, 255` - This appears more orange than yellow
  - Should verify if this matches the intended "Busy Bee" yellow color (#f6ff00)

### 2. Missing TURBO Macro Implementation  
- **Lines 609-618**: `turbo_macro` variable is toggled but no actual turbo functionality implemented
- Either implement the turbo feature (rapid key sending) or remove incomplete code

### 3. Empty SYMBOLS Layer
- **Lines 298-310**: Entire SYMBOLS layer filled with `KC_TRNS` (transparent keys)
- Either populate with actual symbols/characters or remove the layer entirely

### 4. Tap Dance Array Size Mismatch
- **Line 106**: `static tap_state_t tap_state[5]` - Array size hardcoded to 5
- **Lines 122-240**: There are actually 5 tap dance functions (dance_1 through dance_5)
- **CRITICAL**: Array should match number of tap dances, but currently uses direct indexing [0]-[4]

## Medium Priority Improvements

### 5. Hardcoded RGB Layer Indices
- **Lines 553-558**: RGB layer indices hardcoded (1-6) instead of using enum values
- Should use `_FUNCTION`, `_NUMBERS`, etc. for better maintainability
- **CRITICAL**: RGB layer 0 (_BASE) is missing from layer_state_set_user() function

### 6. Code Duplication in Tap Dances
- **Lines 122-240**: Five nearly identical tap dance functions
- Consider refactoring into a single parameterized function to reduce maintenance burden

### 7. Magic Numbers Need Documentation
- **Lines 569-570**: Numbers 13 and 37 in jiggle function need explanation
- **Lines 572, 577**: Delays 10000 and 30000 need comments explaining purpose
- **Line 581**: Counter resets at 1000 - why this number?

### 8. Global Variable Naming
- **Lines 562-564**: Global variables `counter`, `c1`, `c2` need proper prefixes
- Should be something like `jiggle_counter`, `jiggle_c1`, `jiggle_c2`

### 9. Inconsistent Key Definitions in MACRO Layer
- **Line 342**: Mix of `_______` and `_______` (should be consistent)
- **Line 346**: Uses `JIGGLER` but other macros use `TURBO` - inconsistent placement

### 10. Performance Issue in Jiggle Function
- **Line 591**: `do_jiggle()` called on every matrix scan when enabled
- This could cause performance issues - consider using timers instead

## Low Priority Enhancements

### 11. Add Function Documentation
- Add function headers explaining purpose of complex functions like `do_jiggle()`
- Document RGB layer purposes and color choices

### 12. Consider Adding Combos
- Could add key combinations for common functions
- Example: Ctrl+C, Ctrl+V, etc. as single key presses

### 13. Feature Completeness Check
- Verify all declared features are fully implemented
- Consider adding more utility macros if needed

### 14. RGB Layer Base State Issue
- **Lines 552-550**: `_BASE` layer handled in `default_layer_state_set_user()` but not in `layer_state_set_user()`
- Could cause inconsistent RGB behavior when switching back to base layer

## Completed ✅

- [x] Fixed enum/alias consistency in tap dances
- [x] Updated tap dance comments to match actual functionality  
- [x] Added descriptive comments to tap_dance_actions array
- [x] Fixed layer extraction in build system
- [x] Resolved text contrast in keymap visualizations
- [x] Enabled dark mode for better visibility

## Critical Issues to Address Immediately

1. **RGB layer 0 missing** - Base layer RGB may not work properly when switching layers
2. **HSV color mismatch** - Numbers layer shows red instead of intended blue
3. **Tap dance array bounds** - While currently functional, direct indexing is risky

## Notes

- The current tap dance layer switching logic is correct and intentional
- Build system is working properly with automatic visualization generation
- All 13 visualization files (1 complete + 6 individual layers × 2 formats) are generating correctly
- Text contrast is now working with white text on colored backgrounds
- The jiggle macro implementation uses polling which may impact performance