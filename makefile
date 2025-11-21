CC = gcc

SRC_DIR = src
BUILD_DIR = build

CFLAGS = -Wall -Wextra -O2
LDFLAGS = 

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

TARGET = $(BUILD_DIR)/ArtOfCinema.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	@echo "Clean complete"

.PHONY: all clean
