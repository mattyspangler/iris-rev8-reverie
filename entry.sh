#!/bin/bash

set -euo pipefail

readonly QMK_DIR="/build-volume/qmk_firmware"
readonly KEYMAP_DIR="/build-volume/qmk_firmware/keyboards/keebio/iris/keymaps/reverie"
readonly CUSTOM_KEYMAP_DIR="/build-volume/custom-keymap"
readonly BUILD_OUTPUT_DIR="/build-volume/build-output"
readonly ASSETS_DIR="/build-volume/build-output/assets"

# Hardware configuration - change these if targeting different keyboard
readonly QMK_KEYBOARD="keebio/iris/rev8"
readonly QMK_KEYMAP="reverie"
readonly QMK_LAYOUT="LAYOUT"

# Extract layer names from keymap.c enum (remove _ prefix and trailing punctuation)
readonly LAYER_NAMES=$(awk '/enum iris_layers {/,/^}/ { if (/_[A-Z_]+[,;]/) print $1 }' "$CUSTOM_KEYMAP_DIR/keymap.c" | sed 's/^_//' | sed 's/,$//' | tr '\n' ' ' | sed 's/ $//')

log() {
    echo "$*"
}

die() {
    echo "ERROR: $*" >&2
    exit 1
}

setup_qmk() {
    log "Setting up QMK firmware..."
    cd "$QMK_DIR"
    
    log "Activating venv"
    . /opt/venv/bin/activate
    
    log "Installing pip requirements"
    pip install -r "$QMK_DIR/requirements.txt"
    
    log "Making git submodule"
    make git-submodule
    
    log "QMK Setup"
    qmk setup -y
}

install_keymap() {
    log "Installing keymap..."
    mkdir -p "$KEYMAP_DIR"
    cp "$CUSTOM_KEYMAP_DIR"/* "$KEYMAP_DIR"
    
    # Remove JSON/YAML keymap files to prevent conflicts with C keymap
    rm -f "$KEYMAP_DIR"/keymap.json "$KEYMAP_DIR"/keymap.yaml
}

compile_firmware() {
    log "Compiling firmware..."
    qmk compile -kb "$QMK_KEYBOARD" -km "$QMK_KEYMAP"
    
    log "Moving UF2 file to build-output/"
    mv "$QMK_DIR/${QMK_KEYBOARD//\//_}_${QMK_KEYMAP}.uf2" "$BUILD_OUTPUT_DIR"
}

convert_svg_to_png() {
    local svg_file="$1"
    local png_file="$2"
    
    convert "$svg_file" "$png_file"
}

generate_keymap_visualizations() {
    log "Generating keymap visualizations..."
    mkdir -p "$ASSETS_DIR"

    # Validate layer names were extracted
    if [[ -z "$LAYER_NAMES" ]]; then
        die "Failed to extract layer names from keymap.c"
    fi

    # 1. Generate QMK keymap JSON from C file
    log "Converting QMK C keymap to JSON..."
    qmk c2json -kb "$QMK_KEYBOARD" -km "$QMK_KEYMAP" -o /tmp/keymap.json

    # 2. Parse JSON with explicit layer names for keymap-drawer compatibility
    log "Parsing with layer names: $LAYER_NAMES"
    keymap parse \
        -q /tmp/keymap.json \
        --layer-names $LAYER_NAMES \
        -o /tmp/logical_layers.yaml

    # 3. Construct complete keymap YAML with layout header
    log "Constructing final keymap YAML..."
    local final_keymap_yaml="$BUILD_OUTPUT_DIR/final_keymap.yaml"
    cat > "$final_keymap_yaml" << EOF
layout:
  qmk_keyboard: $QMK_KEYBOARD
  layout_name: $QMK_LAYOUT
EOF
    
    # Extract only the layers section from parsed YAML
    sed -n '/^layers:/,$p' /tmp/logical_layers.yaml >> "$final_keymap_yaml"

    # 4. Draw the complete keymap visualization
    log "Drawing complete keymap visualization..."
    keymap -c "$CUSTOM_KEYMAP_DIR/keymap-drawer-config.yaml" draw \
        -k "$QMK_KEYBOARD" -l "$QMK_LAYOUT" \
        "$final_keymap_yaml" \
        -o "$ASSETS_DIR/keymap.svg"

    # Convert to PNG
    convert_svg_to_png "$ASSETS_DIR/keymap.svg" "$ASSETS_DIR/keymap.png"

    # 5. Generate individual layer images
    log "Drawing individual layer visualizations..."
    for layer_name in $LAYER_NAMES; do
        local layer_svg="$ASSETS_DIR/keymap-${layer_name,,}.svg"
        local layer_png="$ASSETS_DIR/keymap-${layer_name,,}-layer.png"

        keymap -c "$CUSTOM_KEYMAP_DIR/keymap-drawer-config.yaml" draw \
            -k "$QMK_KEYBOARD" -l "$QMK_LAYOUT" -s "$layer_name" \
            -o "$layer_svg" \
            "$final_keymap_yaml"

        convert_svg_to_png "$layer_svg" "$layer_png"
    done

    log "Keymap visualizations generated in $ASSETS_DIR/"
}

main() {
    log "Starting Iris Rev 8 firmware build..."
    
    setup_qmk
    install_keymap
    compile_firmware
    
    # Install keymap-drawer and generate visualizations
    pip install keymap-drawer
    generate_keymap_visualizations
    
    log "Build completed successfully!"
}

main "$@"