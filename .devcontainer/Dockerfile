# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.140.1/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version: bionic, focal
ARG VARIANT="focal"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

RUN apt-get update -y && apt-get upgrade -y

RUN cd ~/

# Install misc tools
RUN apt-get install -y make
RUN apt-get install -y gdb
RUN apt-get install -y fish
RUN apt-get install -y gcc-arm-none-eabi
RUN apt-get install -y zip unzip

# Download and unzip the SDK
RUN wget https://www.nordicsemi.com/-/media/Software-and-other-downloads/SDKs/nRF5/Binaries/nRF5SDK160098a08e2.zip
RUN unzip nRF5SDK160098a08e2.zip -d nRF5SDK16

# Download and unzip S140 softDevice
RUN wget https://www.nordicsemi.com/-/media/Software-and-other-downloads/SoftDevices/S140/s140nrf52701.zip
RUN unzip s140nrf52701.zip -d s140

# Download and unzip S113 softDevice
RUN wget https://www.nordicsemi.com/-/media/Software-and-other-downloads/SoftDevices/S113/s113nrf52701.zip
RUN unzip s113nrf52701.zip -d s113

# Set GCC ARM cross compiler path for the NRF5 SDK
ENV GNU_INSTALL_ROOT /usr/bin/

# We must mount our project into the following directory:
# /nRF5SDK16/examples/ble_peripheral/
# This is done in devcontainer.json
