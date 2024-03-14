CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -std=c99 
LIBS = `sdl2-config --cflags --libs`

SRCDIR = .
OBJDIR = obj
BUILDDIR = bin

ROMDIR = roms

DISPLAYDIR = display
INPUTDIR = input
MEMORYDIR = memory
INSTRUCTIONDIR = instruction

SRCS = $(wildcard $(SRCDIR)/*.c) \
	$(wildcard $(DISPLAYDIR)/*.c) \
	$(wildcard $(INPUTDIR)/*.c) \
	$(wildcard $(MEMORYDIR)/*.c) \
	$(wildcard $(INSTRUCTIONDIR)/*.c)

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET = ./$(BUILDDIR)/chip8_emulator

.PHONY: all clean

all: $(TARGET)

logo: all
	$(TARGET) $(ROMDIR)/Logo.ch8

test: all
	$(TARGET) $(ROMDIR)/Test.ch8

tetris: all
	$(TARGET) $(ROMDIR)/Tetris.ch8

pong: all
	$(TARGET) $(ROMDIR)/Pong.ch8

clock: all
	$(TARGET) $(ROMDIR)/Clock.ch8

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	$(RM) -r $(OBJDIR) $(TARGET)
