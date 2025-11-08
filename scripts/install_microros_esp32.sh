# install_microros_esp32.sh

#!/bin/bash
# Run the ESP32 setup script
./install_espressif.sh

# Create a workspace and download the micro-ROS tools
git clone -b $ROS_DISTRO https://github.com/micro-ROS/micro_ros_espidf_component.git

# Install dependecies
export IDF_PATH=$HOME/esp/esp-idf
source $IDF_PATH/export.sh && pip3 install catkin_pkg lark-parser colcon-common-extensions