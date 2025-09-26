CC = clang

CFLAGS = -g -Wall -Werror -Wextra
LIBS = `sdl2-config --cflags --libs`

SRC_DIR = src
BUILD_DIR = .build
ROMS_DIR = roms

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.d)

TARGET = ./$(BUILD_DIR)/chip8_emulator

.PHONY: all clean

all: $(TARGET)

logo: all
	$(TARGET) $(ROMS_DIR)/Logo.ch8

test: all
	$(TARGET) $(ROMS_DIR)/Test.ch8

tetris: all
	$(TARGET) $(ROMS_DIR)/Tetris.ch8

pong: all
	$(TARGET) $(ROMS_DIR)/Pong.ch8

clock: all
	$(TARGET) $(ROMS_DIR)/Clock.ch8

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	$(RM) -r $(OBJS) $(DEPS) $(TARGET)
