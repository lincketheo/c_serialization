# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -L$(HOME)/.local/lib -Wl,-rpath=$(HOME)/.local/lib
INCLUDES = -I$(HOME)/.local/include

# Directories
BINDIR = bin
LIBDIR = lib
OBJDIR = obj
SRCDIR = src

# Files
LIBNAME = libbitss.a
LIBSRC = bit_serialize.c
LIBOBJ = $(LIBSRC:.c=.o)
LIB = $(LIBDIR)/$(LIBNAME)

MAIN = main
MAINSRC = main.c
MAINOBJ = $(MAINSRC:.c=.o)
MAINBIN = $(BINDIR)/$(MAIN)

TEST = test_bitss
TESTSRC = test.c
TESTOBJ = $(TESTSRC:.c=.o)
TESTBIN = $(BINDIR)/$(TEST)

# CUnit detection
CUNIT_INC = $(shell find $(HOME)/.local/include -name 'CUnit.h' 2>/dev/null)
CUNIT_LIB = $(shell find $(HOME)/.local/lib -name 'libcunit.so' 2>/dev/null)

ifeq ($(CUNIT_INC),)
  TEST_ENABLED = 0
else
  TEST_ENABLED = 1
  CUNIT_FLAGS = -I$(dir $(CUNIT_INC)) -L$(dir $(CUNIT_LIB)) -lcunit
endif

# Rules
all: $(LIB) $(MAINBIN) $(if $(TEST_ENABLED), $(TESTBIN),)

$(LIB): $(LIBOBJ)
	@mkdir -p $(LIBDIR)
	ar rcs $@ $^

$(MAINBIN): $(MAINOBJ) $(LIB)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TESTBIN): $(TESTOBJ) $(LIB)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(TESTOBJ) -o $@ $(LIB) $(CUNIT_FLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean test format

format:
	find . -name "*.c" -o -name "*.h" | xargs clang-format -i

clean:
	rm -rf $(BINDIR) $(LIBDIR) *.o

test: $(TESTBIN)
	$(TESTBIN)
