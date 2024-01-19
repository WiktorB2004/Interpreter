# Select base image
FROM ubuntu:20.04

# Set the working directory in the container
WORKDIR /app

# Ubuntu configuration
ARG DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    libssl-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Install Cmake
RUN cd /tmp && \
    wget https://github.com/Kitware/CMake/releases/download/v3.28.1/cmake-3.28.1.tar.gz && \
    tar -zxvf cmake-3.28.1.tar.gz && \
    cd cmake-3.28.1 && \
    ./bootstrap && \
    make && \
    make install

# Copy files/folders needed by image
COPY CMakeLists.txt .
COPY include/ include
COPY src/ src
COPY utils/ utils
COPY scripts/ scripts

# Create a build directory and run CMake to configure the project
RUN mkdir build && \
    cd build && \
    cmake .. -DRELEASE_BUILD=1 && \
    cmake --build .

RUN chmod +x /app/scripts/docker_entrypoint.sh

# Entry point script handles file argument
ENTRYPOINT ["/app/scripts/docker_entrypoint.sh"]