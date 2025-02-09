PROJECT_NAME = Towninger
CC = $(USERPROFILE)/source/gbdk/bin/lcc
INCLUDE_DIR=$(USERPROFILE)/source/gbdk/include
CFLAGS = -Wa-l -Wl-m -Wl-j -Wm-yc
TARGET = $(PROJECT_NAME).gb

# Source files for your project (you can add more .c files here)
SRCS = main.c graphics.c

all:
	@echo "Compiling..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	@echo "Build completed"

clean:
	del $(TARGET)
	del $(PROJECT_NAME).map
	del $(PROJECT_NAME).noi