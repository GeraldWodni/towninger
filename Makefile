PROJECT_NAME = Towninger
GBDK_URL = https://github.com/gbdk-2020/gbdk-2020/releases/download/4.3.0/gbdk-win64.zip
GBDK_DIR = gbdk
BGB_URL = https://bgb.bircd.org/bgbw64.zip
BGB_DIR = bgb
CC = $(abspath $(GBDK_DIR))/bin/lcc
INCLUDE_DIR = $(abspath $(GBDK_DIR))/include
CFLAGS = -Wa-l -Wl-m -Wl-j -Wm-yc
TARGET = $(PROJECT_NAME).gb

# Source files for your project (you can add more .c files here)
SRCS = main.c graphics.c

# Default target
all: download_gbdk build

# Target to download and set up GBDK & BGB
download_gbdk:
	@if not exist "$(GBDK_DIR)" ( \
		echo "Downloading GBDK..." && \
		powershell -Command "Invoke-WebRequest -Uri '$(GBDK_URL)' -OutFile 'gbdk.zip'" && \
		echo "Extracting GBDK..." && \
		powershell -Command "Expand-Archive -Path 'gbdk.zip' -DestinationPath '.'" && \
		del gbdk.zip && \
		echo "GBDK setup complete." \
	) else ( \
		echo "GBDK already exists." \
	)

download_bgb:
	@if not exist "$(BGB_DIR)" ( \
		echo "Downloading BGB..." && \
		powershell -Command "Invoke-WebRequest -Uri '$(BGB_URL)' -OutFile '$(BGB_DIR).zip'" && \
		echo "Extracting BGB..." && \
		powershell -Command "Expand-Archive -Path '$(BGB_DIR).zip' -DestinationPath '$(BGB_DIR)'" && \
		del $(BGB_DIR).zip && \
		echo "BGB setup complete." \
	) else ( \
		echo "BGB already exists." \
	)

# Target to build the project
build: download_bgb
	@echo "Compiling..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	@echo "Build completed"

# Target to clean up build files
clean:
	del $(TARGET)
	del $(PROJECT_NAME).map
	del $(PROJECT_NAME).noi