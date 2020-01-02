# Makefile for test with Unity
# reference: "Building with Unity with Make"
# https://www.throwtheswitch.org/build/make

#SRCDIR := src
INCDIR   := include
TESTDIR  := test
UNITYDIR := unity/src

BUILDDIR  := build
DEPDIR    := build/depends
OBJDIR    := build/objs
RESDIR    := build/results
BUILDDIRS := $(BUILDDIR) $(DEPDIR) $(OBJDIR) $(RESDIR)

TESTSRCS := $(wildcard $(TESTDIR)/*.c)
RESULTS  := $(patsubst $(TESTDIR)/test_%.c, $(RESDIR)/test_%.txt, $(TESTSRCS))

.PRECIOUS: $(BUILDDIR)/test_%.out
.PRECIOUS: $(DEPDIR)/%.d
.PRECIOUS: $(OBJDIR)/%.o
.PRECIOUS: $(RESDIR)/%.txt

CC     := gcc
CFLAGS := -Wall -Wextra -Wpedantic -Werror -std=c11 -I$(INCDIR) -I$(UNITYDIR) -DTEST

COMPILE := $(CC) -c
LINK    := $(CC)
DEPEND  := $(CC) -MM -MG -MF

RM    := rm -f
MKDIR := mkdir -p

.PHONY: test clean

test: $(BUILDDIRS) $(RESULTS)
	@echo "$(RESULTS)"
	@echo "----------\nIGNORES:\n----------"
	@echo `grep -s IGNORE ${RESDIR}/*.txt`
	@echo "----------\nFAILURES:\n----------"
	@echo `grep -s FAIL ${RESDIR}/*.txt`
	@echo "\nDONE"

$(RESDIR)/%.txt: $(BUILDDIR)/%.out
	./$< > $@ 2>&1

$(BUILDDIR)/test_%.out: $(OBJDIR)/test_%.o $(OBJDIR)/unity.o
	$(LINK) -o $@ $^

$(OBJDIR)/%.o:: $(TESTDIR)/%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o:: $(UNITYDIR)/%.c $(UNITYDIR)/%.h
	$(COMPILE) $(CFLAGS) $< -o $@

$(DEPDIR)/%.d:: $(TESTDIR)/%.c
	$(DEPEND) $@ $<

$(BUILDDIR):
	$(MKDIR) $(BUILDDIR)

$(DEPDIR):
	$(MKDIR) $(DEPDIR)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(RESDIR):
	$(MKDIR) $(RESDIR)

clean:
	$(RM) $(OBJDIR)/*.o
	$(RM) $(BUILDDIR)/*.out
	$(RM) $(RESDIR)/*.txt

