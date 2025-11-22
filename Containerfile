FROM debian:stable-slim

# Install QMK prerequisites
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    clang-format \
    diffutils \
    gcc \
    unzip \
    wget \
    zip \
    avr-libc \
    binutils-arm-none-eabi \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    avrdude \
    teensy-loader-cli \
    libhidapi-hidraw0 \
    libusb-dev \
    ca-certificates \
    gcc-avr \
    binutils-avr \
    dfu-programmer \
    dfu-util \
    make \
    python3 \
    python3-pip \
    python3-venv \
    git-core \
    librsvg2-bin \
    imagemagick && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

COPY entry.sh .
RUN python3 -m venv /opt/venv
RUN . /opt/venv/bin/activate && pip install qmk

CMD /entry.sh
