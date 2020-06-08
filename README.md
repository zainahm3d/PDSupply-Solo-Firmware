# PDSupply Solo
A small, open source, USB Power Delivery enabled switching power supply. This power supply is controlled by an NRF52840 Bluetooth 5.0 SOC which handles communication with an iOS application.

## Features (HW Version 1.0)
- 1.0V to 12V output (depending on input capabilities).
    - Adjustment step size from 1V to 9V: 0.06V
    - Adjustment step size from 9V to 12V: 0.25V
- 1.0 amp output across all voltages.
- Live current monitoring, voltage monitoring and graphing with companion iOS application.
- Companion iOS application for control and live graph view.
- Power Delivery profiles: 9V @ 2A (or greater) or 20V @ 2A (or greater)
- Configurable overcurrent shutdown (adjustable in 10mA increments) within 2ms.

## Tested USB PD Bricks
- Apple 96W USB C power brick (MacBook Pro 16 inch)
- Apple 18W USB C power brick (iPad Pro or iPhone fast charger)
- Any PD compatible power supply supporting either 9V @ 2A (or greater) or 20V @ 2A (or greater) should work.

## How to Compile/Run/Debug NRF52 Firmware (MacOS)
- This project includes a VSCode workspace (`PDSupply Solo.code-workspace`) and build/debug/flash tasks to automate flashing the PDSupply.

- Prerequisites/Toolchain Setup:
    - Visual Studio Code
    - Cortex Debug extension
    - [Useful guide](https://gist.github.com/cheburashka/c74840823cde609a5ec379c9440fc0fe) for handling all of the below (make sure to use SDK 16!)
    - JLink drivers installed and added to $PATH. (test by running `jlinkexe` in terminal)
    - NRFJprog
    - Nordic SDK 16 for NRF52840
        - __IMPORTANT:__ For this project to work, you must download the SDK and place the `PDSupply_Solo_FIRMWARE` in the SDK_DIR/examples/ble_peripheral folder
    - GCC_ARM
        - run `brew install gcc-arm-none-eabi` and ensure that your NRF SDK is pointed to the correct binary.

- Predefined tasks in tasks.json (use <kbd>⌘</kbd><kbd>Shift</kbd><kbd>p</kbd> then type "run task" or "run build task")
    - build
        - Builds application
    - build+flash
        - Builds application and flashes over JLink
    - Build + Full Wipe + Flash __(use this for first flash!)__
        - Builds application, wipes NRF52, flashes S140 softdevice, then flashes application.
    - sdk_config
        - Brings up visual (java) tool for setting up NRF SDK params.

- Debugging (preset in "launch.json)
    - For first run, use Build + Full Wipe + Flash build task to make sure the softdevice is flashed.
    - Use the play button in VSCode to begin a debug session. The `build` task will automatically run and invoke the compiler before launch.
    - The correct SVD file is included in this project and should be automatically set up for Cortex Debug

## How to Compile/Run/Debug iOS Application
- Open PDSupply.xcodeproj with Xcode
- Set your developer team to yourself to begin testing on a real device. CoreBluetooth does not function in a simulator.

_Designed by @CaptioLabs_
