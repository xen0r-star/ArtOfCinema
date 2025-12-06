CC = gcc

SRC_DIR = src
BUILD_DIR = build

CFLAGS = -Wall -Wextra -O2

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
RES_OBJ = $(BUILD_DIR)/resource.res

# Other resource files
DAT_SRCS = $(wildcard $(SRC_DIR)/*.dat) $(wildcard $(SRC_DIR)/*/*.dat) $(wildcard $(SRC_DIR)/*/*/*.dat)
DAT_DESTS = $(patsubst $(SRC_DIR)/%.dat, $(BUILD_DIR)/%.dat, $(DAT_SRCS))

CSV_SRCS = $(wildcard $(SRC_DIR)/*.csv) $(wildcard $(SRC_DIR)/*/*.csv) $(wildcard $(SRC_DIR)/*/*/*.csv)
CSV_DESTS = $(patsubst $(SRC_DIR)/%.csv, $(BUILD_DIR)/%.csv, $(CSV_SRCS))

ICO_SRCS = $(wildcard $(SRC_DIR)/*.ico) $(wildcard $(SRC_DIR)/*/*.ico) $(wildcard $(SRC_DIR)/*/*/*.ico)
ICO_DESTS = $(patsubst $(SRC_DIR)/%.ico, $(BUILD_DIR)/%.ico, $(ICO_SRCS))

# Final executable
TARGET = $(BUILD_DIR)/ArtOfCinema.exe


all: $(TARGET) $(DAT_DESTS) $(CSV_DESTS) $(ICO_DESTS)

$(TARGET): $(OBJS) $(RES_OBJ)
	@echo Linking...
	$(CC) -o $@ $(OBJS) $(RES_OBJ)
	@echo Build complete: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@powershell -Command "New-Item -ItemType Directory -Force -Path $(subst /,\,$(dir $@)) | Out-Null"
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/resource.res: $(SRC_DIR)/resources/resource.rc
	@powershell -Command "New-Item -ItemType Directory -Force -Path $(subst /,\,$(dir $@)) | Out-Null"
	@echo Compiling resources $<
	windres -O coff $< -o $@


$(BUILD_DIR)/%.dat: $(SRC_DIR)/%.dat
	@powershell -Command "New-Item -ItemType Directory -Force -Path $(subst /,\,$(dir $@)) | Out-Null"
	@echo Copying $<
	@powershell -Command "Copy-Item -Path '$<' -Destination '$@' -Force"

$(BUILD_DIR)/%.csv: $(SRC_DIR)/%.csv
	@powershell -Command "New-Item -ItemType Directory -Force -Path $(subst /,\,$(dir $@)) | Out-Null"
	@echo Copying $<
	@powershell -Command "Copy-Item -Path '$<' -Destination '$@' -Force"

$(BUILD_DIR)/%.ico: $(SRC_DIR)/%.ico
	@powershell -Command "New-Item -ItemType Directory -Force -Path $(subst /,\,$(dir $@)) | Out-Null"
	@echo Copying $<
	@powershell -Command "Copy-Item -Path '$<' -Destination '$@' -Force"

clean:
	rm -rf $(BUILD_DIR)

debug:
	@echo "Target: $(TARGET)"
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"
	@echo ".dat: $(DAT_DESTS)"
	@echo ".csv: $(CSV_DESTS)"
	@echo ".ico: $(ICO_DESTS)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "Resource Object: $(RES_OBJ)"

help:
	@echo "ArtOfCinema Build System"
	@echo "========================="
	@echo "Usage:"
	@echo "  make                   - Build for current platform (auto-detected)"
	@echo "  make clean             - Clean build directory"
	@echo "  make debug             - Show build configuration"

clean-build:
	rm -f $(OBJS) $(RES_OBJ)
	rm -f $(ICO_DESTS)
	/usr/bin/find build -type d -empty -delete

.PHONY: all clean debug help clean-build