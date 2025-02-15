#!/bin/bash

# Set directories and URLs
GBDK_URL="https://github.com/gbdk-2020/gbdk-2020/releases/download/4.3.0/gbdk-linux64.tar.gz"
BGB_URL="https://bgb.bircd.org/bgbw64.zip"

# Check for GBDK directory
if [ ! -d "gbdk" ]; then
    echo "Downloading GBDK..."
    curl -L -o gbdk.tar.gz "$GBDK_URL"
    echo "Extracting GBDK..."
    tar -xvzf gbdk.tar.gz -C ./
    rm gbdk.tar.gz
    echo "GBDK setup complete."
else
    echo "GBDK already exists."
fi

# Check for BGB directory
if ! type "bgb" && [ ! -d "bgb" ]; then
    echo "Downloading BGB..."
    curl -L -o bgb.zip "$BGB_URL"
    echo "Extracting BGB..."
    unzip bgb.zip -d ./bgb/
    rm bgb.zip
    echo "BGB setup complete."
else
    echo "BGB already exists."
fi