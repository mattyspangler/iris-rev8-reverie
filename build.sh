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
