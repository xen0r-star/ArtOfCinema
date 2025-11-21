CC = gcc

SRC_DIR = src
BUILD_DIR = build

CFLAGS = -Wall -Wextra -O2

SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

TARGET = $(BUILD_DIR)/ArtOfCinema.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo Linking...
	$(CC) -o $@ $(OBJS)
	@echo Build complete: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@powershell -Command "New-Item -ItemType Directory -Force -Path $(subst /,\,$(dir $@)) | Out-Null"
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

debug:
	@echo "Target: $(TARGET)"
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"
	@echo "CFLAGS: $(CFLAGS)"

help:
	@echo "ArtOfCinema Build System"
	@echo "========================="
	@echo "Usage:"
	@echo "  make                   - Build for current platform (auto-detected)"
	@echo "  make clean             - Clean build directory"
	@echo "  make debug             - Show build configuration"

.PHONY: all clean debug help