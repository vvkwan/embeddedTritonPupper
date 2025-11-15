#!/usr/bin/env bash
set -e
apt-get update -y
apt-get install -y ros-humble-ros-base ros-dev-tools
echo 'source /opt/ros/humble/setup.bash' >> /root/.bashrc
echo 'source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash' >> /root/.bashrc || true