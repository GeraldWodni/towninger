PROJECT_NAME = Towninger
GBDK_DIR = gbdk
CC = $(abspath $(GBDK_DIR))/bin/lcc
INCLUDE_DIR = $(abspath $(GBDK_DIR))/include
CFLAGS = -Wa-l -Wl-m -Wl-j -Wm-yc
TARGET = $(PROJECT_NAME).gb

# Source files for your project (you can add more .c files here)
SRCS = main.c graphics.c

# Default target
all: build

# Target to build the project
build:
	@echo "Compiling..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	@echo "Build completed"

# Target to clean up build files
clean:
	del $(TARGET)
	del $(PROJECT_NAME).map
	del $(PROJECT_NAME).noi