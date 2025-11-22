#!/bin/bash

REPOSRC="https://github.com/qmk/qmk_firmware"
LOCALREPO=qmk_firmware
# We do it this way so that we can abstract if from just git later on
LOCALREPO_VC_DIR=$LOCALREPO/.git

echo "Copying files to container volume"

mkdir -p ./build-volume/custom-keymap
cp keymap.c ./build-volume/custom-keymap/
cp rules.mk ./build-volume/custom-keymap/
cp config.h ./build-volume/custom-keymap/
if [ -f keymap-drawer-config.yaml ]; then
    cp keymap-drawer-config.yaml ./build-volume/custom-keymap/
fi
cp entry.sh ./build-volume/
chmod a+x ./build-volume/entry.sh

echo "Creating build-output folder"
mkdir -p ./build-volume/build-output

echo "Download QMK firmware repo"

cd ./build-volume

if [ ! -d $LOCALREPO_VC_DIR ]
then
    git clone $REPOSRC $LOCALREPO
else
    cd $LOCALREPO
    git pull $REPOSRC
fi

cd ../..

echo "Building container"
podman build -t qmkbuild -f Containerfile .

echo "Running container"
podman run -v ./build-volume:/build-volume:z --rm localhost/qmkbuild

echo "Copying generated assets from build-output to repo root assets/"
mkdir -p ./assets
cp ./build-volume/build-output/assets/* ./assets/ 2>/dev/null || echo "No assets found to copy"

echo "Build completed. UF2 file available at ./build-volume/build-output/"
echo "Keymap images available at ./assets/"
