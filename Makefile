CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -std=c99 `sdl2-config --cflags --libs`

SRCDIR = .
OBJDIR = obj
BUILDDIR = bin

ROMDIR = roms

DISPLAYDIR = display
INPUTDIR = input
MEMORYDIR = memory

SRCS = $(wildcard $(SRCDIR)/*.c) \
	$(wildcard $(DISPLAYDIR)/*.c) \
	$(wildcard $(INPUTDIR)/*.c) \
	$(wildcard $(MEMORYDIR)/*.c)

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET = ./$(BUILDDIR)/chip8_emulator

.PHONY: all clean

all: $(TARGET)

logo: all
	$(TARGET) $(ROMDIR)/IBM_Logo.ch8

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJDIR) $(TARGET)
