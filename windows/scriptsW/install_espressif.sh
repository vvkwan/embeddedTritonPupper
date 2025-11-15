# install_espressif.sh

#!/bin/bash

# Check if the 'esp' folder exists
if [ ! -d ~/esp ]; then

    # Update package lists and install required dependencies
    sudo apt-get update -y
    sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0 -y
    
    # Create directory for ESP development and clone ESP-IDF repository
    mkdir -p ~/esp
    cd ~/esp
    git clone -b v5.2 --recursive https://github.com/espressif/esp-idf.git

    # Navigate to ESP-IDF directory and install ESP32 toolchain
    cd ~/esp/esp-idf
    ./install.sh esp32

    # Set IDF_PATH environment variable and make it persistent
    export IDF_PATH=$HOME/esp/esp-idf
    echo "export IDF_PATH=$HOME/esp/esp-idf" >> "$HOME/.bashrc"
    source "$HOME/.bashrc"
else
    echo "'esp' folder already exists."
fi