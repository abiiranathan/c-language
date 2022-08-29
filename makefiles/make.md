# make - One Makefile to make them all

What is make used for ?

- Purely for automation
- Language and paradigm agnostic
- Built in implicit rules
- Expects one or more input files to produce one or more output files.
- Automatic prerequisite tracking
- Timestamp tracking for dependancy management

## Assignment operators

```make

# Verbatim assignment
SRCS = main.c

# Simple expression
# Really it's unlimited recursion
SRCS := $(wildcard *.c)

# Shell expansion
SRCS != find . -name "*.c"

# Explicit shell expansion
SRCS := $(shell find . -name "*.c")

# Append to
CC_FLAGS += -Wextra

# Conditional Assignment
CFLAGS ?= $(CC_FLAGS)
FOO := $(BAR)

# Avoid inline comments
THIS IS A NO OP: !! 
FOO=$(BAR) # Comment
```

## Built in functions

```make

# Text functions
$(SRCS:.c=.0)

# Filename functions
$(addprefix build/, $(OBJS))

# Conditional functions
$(if ..) $(or ..) $(and ..)

# Value functions
$(foreach var, list,text) 
$(value (VARIABLE)) # Print a variable without expanding it.

# Shell functions
$(shell ..)
$(error ..) # Stop building the project
$(warning ..)
$(info ..) 

```

## Rules

```make

%.o: %.c
  $(CC) -c $(CFLAGS) -o $@ $<
  # $@ - target
  # $< - The first prerequisite

%.o: %.cpp
  $(CXX) -c $(CXXFLAGS) -o $@ $<

```

## Recipes
The first defined target is the one to run if none is specified.

```make
# Define sources
SRCS = main.c
OBJS := $(SRCS:.c=.o)

# Define targets
TARGET := foo

# phony targets
# A phony target is a target in make that produces no output.
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
  $(CC) -o $@ $^

clean:
  rm -f $(OBJS)

```

# Automatic Variables

$@ : Current target

$<: First prerequisite

$^: All preriquisites

$?: Prerequisites that have changed

$|: Order-only prerequisites

*Example usage for automatic variables*

```make

SRCS = main.c
OBJS := $(SRCS:.c=.o)
DIR := build
OBJS := $(addprefix $(DIR), $(OBJS))

TARGET := foo

.PHONY: clean

$(DIR)/%.o: %.c
  $(CC) -c $(CFLAGS) -o $@ $<

#Use of Order only prerequisite on build directory.

$(TARGET): $(OBJS) | $(DIR)
  $(CC) -o $@ $^

$(DIR):
  mkdir -p $@

```

## Automatic dependency.

- make integrates with the compiler.
- Dependency files contain information:
  a) -MT: Name of the target
  b) -MMD: List user header files
  c) -MP: Add phony targets
  d) -MF: Name of the file

- The *DEPFILES* recipe and the include line must be the last lines in the file.
- Make will only rebuild prerequisites which have a newer timestamp than the generated dependancy file.

```make
DEPDIR = .deps
DEPFILES := $(SRCS:.c=$(DEPDIR)/%.d)
DEPFLAGS = -MT $@ -MMD -M -MF $(DEPDIR)$*.d

%.o: %c $(DEPDIR)/%.d | $(DEPDIR)
  $(CC) -c $(CFLAGS) $(DEPFLAGS) -o $@ $<

< The rest of the rules/recipes >


$(DEPDIR):
  @mkdir -p $(DEPDIR)


$(DEPFILES):

include $(wildcard $(DEPFILES))

```

##Template Makefile
 
And now time for one makefile to rule them all.

- Replace the target
- You may not need to change anything else for any of your projects.
- Except for external dependencies


```make

SRCS := $(wildcard *.c)
OBJDIR = .build
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

DEPDIR = .deps
DEPFILES := $(SRCS:.c=$(DEPDIR)/%.d)
DEPFLAGS = -MT $@ -MMD -M -MF $(DEPDIR)$*.d

.PHONY: clean

TARGET = binaryname
# Change ^^^^^^^^^^ to the desired name

$(OBJDIR)/%.o: %.c | $(OBJDIR) $(DEPDIR)
  @echo [CC] $@
  @$(CC) -c $(CFLAGS) $(DEPFLAGS) -o $@ $<

$(TARGET): $(OBJS)
  @echo [LD] $@
  @$(CC) $(LDFLAGS) -o $@ $^

clean:
  @rm -rf $(OBJDIR) $(TARGET)

$(OBJDIR) $(DEPDIR):
  @mkdir -p $@

$(DEPFILES):

include $(wildcard $(DEPFILES))

```