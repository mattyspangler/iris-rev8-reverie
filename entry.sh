#!/bin/bash

set -euo pipefail

readonly QMK_DIR="/build-volume/qmk_firmware"
readonly KEYMAP_DIR="/build-volume/qmk_firmware/keyboards/keebio/iris/keymaps/reverie"
readonly CUSTOM_KEYMAP_DIR="/build-volume/custom-keymap"
readonly BUILD_OUTPUT_DIR="/build-volume/build-output"
readonly ASSETS_DIR="/build-volume/build-output/assets"

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
    qmk compile -kb keebio/iris/rev8 -km reverie
    
    log "Moving UF2 file to build-output/"
    mv "$QMK_DIR/keebio_iris_rev8_reverie.uf2" "$BUILD_OUTPUT_DIR"
}

convert_svg_to_png() {
    local svg_file="$1"
    local png_file="$2"
    
    convert "$svg_file" "$png_file"
}

generate_keymap_visualizations() {
    log "Generating keymap visualizations..."
    mkdir -p "$ASSETS_DIR"
    
    # First, generate JSON keymap from QMK C keymap
    log "Converting QMK C keymap to JSON..."
    qmk c2json -kb keebio/iris/rev8 -km reverie -o /tmp/keymap.json
    
    # Parse the keymap
    keymap parse \
        -q /tmp/keymap.json \
        -o /tmp/parsed_keymap.yaml
    
    # Generate the complete keymap visualization
    keymap draw \
        -c "$CUSTOM_KEYMAP_DIR/keymap-drawer-config.yaml" \
        /tmp/parsed_keymap.yaml \
        -o "$ASSETS_DIR/keymap.svg"
    
    # Convert to PNG
    convert_svg_to_png "$ASSETS_DIR/keymap.svg" "$ASSETS_DIR/keymap.png"
    
    # Generate individual layer images
    local layers="QWERTY NUM SYM_NAV MEDIA_MOUSE GAMING MACRO"
    local layer_index=0
    
    for layer_name in $layers; do
        local layer_svg="$ASSETS_DIR/keymap-${layer_name,,}.svg"
        local layer_png="$ASSETS_DIR/keymap-${layer_name,,}-layer.png"
        
        keymap draw \
            -c "$CUSTOM_KEYMAP_DIR/keymap-drawer-config.yaml" \
            -l "$layer_index" \
            /tmp/parsed_keymap.yaml \
            -o "$layer_svg"
        
        convert_svg_to_png "$layer_svg" "$layer_png"
        layer_index=$((layer_index + 1))
    done
    
    log "Keymap visualizations generated in $ASSETS_DIR/"
}

main() {
    log "Starting Iris Rev 8 firmware build..."
    
    setup_qmk
    install_keymap
    compile_firmware
    
    # Try to install keymap-drawer and generate visualizations
    pip install keymap-drawer
    generate_keymap_visualizations
    
    log "Build completed successfully!"
}

main "$@"