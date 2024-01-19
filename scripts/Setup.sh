#!/bin/bash

set -e  # Exit immediately if a command exits with a non-zero status

# Define variables
repository_url="https://github.com/WiktorB2004/WLang_interpreter-C"
repository_dir="$HOME/WLang"
binary_name="WLang"
install_path="$HOME/bin"

# Function to install CMake
install_cmake() {
    echo "Installing CMake..."
    sudo apt-get update
    sudo apt-get install -y build-essential libssl-dev wget

    cd /tmp
    wget https://github.com/Kitware/CMake/releases/download/v3.28.1/cmake-3.28.1.tar.gz
    tar -zxvf cmake-3.28.1.tar.gz
    cd cmake-3.28.1
    ./bootstrap
    make
    sudo make install

    cd /tmp
    rm -rf cmake-3.28.1.tar.gz cmake-3.28.1

    echo "CMake successfully installed - version 3.28.1"
}

# Check if Git is installed
if ! command -v git &> /dev/null; then
    echo "Error: Git is required for the installation. Please install Git and try again."
    exit 1
fi

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    read -p "CMake is not installed. Do you want to install it? (Y/N): " install_cmake_choice
    if [[ "$install_cmake_choice" =~ ^[Yy]$ ]]; then
        install_cmake
    else
        echo "Error: CMake is required for the installation. Please install CMake and try again."
        exit 1
    fi
fi

# Create necessary directories if they don't exist
mkdir -p "$install_path" "$repository_dir"

# Change to the repository directory
cd "$repository_dir"

# Check if the repository directory exists
if [ -d "$repository_dir/.git" ]; then
    echo "Repository directory exists. Pulling the latest changes..."
    git pull
else
    echo "Cloning repository..."
    git clone "$repository_url" "$repository_dir"
fi

# Configure and build the WLang interpreter
mkdir -p build && cd build
cmake .. -DRELEASE_BUILD=1 && cmake --build .
cd ..

# Copy the binary to the user's local bin directory
cp "$repository_dir/bin/$binary_name" "$install_path"

# Inform the user about the successful installation and usage
echo "WLang interpreter has been installed successfully for the current user."
echo "You can now interpret your WLang files using 'wlang path_to_file'."
