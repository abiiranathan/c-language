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
