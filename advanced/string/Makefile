CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g -O2

SRCDIR = src
INCDIR = include
OBJDIR = obj
TESTDIR = test
BUILDDIR= build

SOURCES = $(wildcard $(SRCDIR)/*.c)
HEADERS = $(wildcard $(INCDIR)/*.h)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

TEST_SOURCES = $(wildcard $(TESTDIR)/*.c)

.PHONY: all clean

all: $(OBJECTS) test

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@


test: $(TEST_SOURCES) $(SOURCES)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $(BUILDDIR)/test $^
	$(BUILDDIR)/test

clean:
	rm -f $(OBJECTS)  $(BUILDDIR)/test
