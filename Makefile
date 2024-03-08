CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -std=c99 `sdl2-config --cflags --libs`

SRCDIR = .
DISPLAYDIR = display
INPUTDIR = input
OBJDIR = obj
BUILDDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.c) \
	$(wildcard $(DISPLAYDIR)/*.c) \
	$(wildcard $(INPUTDIR)/*.c)

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET = ./$(BUILDDIR)/chip8_emulator

.PHONY: all clean

all: $(TARGET)

run: all
	$(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJDIR) $(TARGET)
