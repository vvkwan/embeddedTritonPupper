FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    curl gnupg lsb-release locales \
    && locale-gen en_US en_US.UTF-8 \
    && update-locale LC-ALL=en_US.UTF-8 LANG=en_US.UTF-8

ENV ROS_VERSION=2
ENV ROS_DISTRO=humble
ENV ROS_PYTHON_VERSION=3
ENV TZ=America/Los_Angeles
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && apt install -y software-properties-common
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key \
    -o /usr/share/keyrings/ros-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] \
    http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" \
    | tee /etc/apt/sources.list.d/ros2.list > /dev/null

RUN apt update && apt install -y \
    ros-humble-desktop \
    python3-argcomplete \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /embeddedTritonPupper/src
COPY scriptsW/*.sh /embeddedTritonPupper/src/

RUN chmod +x ./*.sh
RUN ./install_ros2.sh

CMD ["/bin/bash"]