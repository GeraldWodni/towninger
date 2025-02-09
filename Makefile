PROJECT_NAME = Towninger
CC = $(USERPROFILE)/source/gbdk/bin/lcc
INCLUDE_DIR=$(USERPROFILE)/source/gbdk/include
CFLAGS = -Wa-l -Wl-m -Wl-j
TARGET = $(PROJECT_NAME).gb

# Source files for your project (you can add more .c files here)
SRCS = main.c

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET)
	del $(PROJECT_NAME).map
	del $(PROJECT_NAME).noi