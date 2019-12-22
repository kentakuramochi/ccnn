CC     := gcc
CFLAGS := -Wall -Wextra -Wpedantic -Werror -std=c11

# for GoogleTest
CXX      := g++
CXXFLAGS := -Wall -Wextra -Wpedantic -Werror -std=c++11
LDFLAGS  := -L/usr/local/lib
LIBS     := -lgtest -lgtest_main -lpthread

INCLUDE := -I./include

BUILD ?= release

ifeq ($(BUILD), release)
	CFLAGS   += -O0 -g
else
	CFLAGS   += -O2
endif

TESTDIR  := test
BUILDDIR := build

TESTSRCS := $(wildcard $(TESTDIR)/*.cpp)
TESTOBJS := $(addprefix $(BUILDDIR)/,$(TESTSRCS:.cpp=.o))
TESTMAIN := $(BUILDDIR)/$(TESTDIR)/test_main

RM := rm -rf

.PHONY: test clean

test: $(TESTMAIN)
	@./$(TESTMAIN)

$(TESTMAIN): $(TESTOBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) $? $(LIBS) -o $@

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p ./$(BUILDDIR)/$(TESTDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -c $< $(LIBS) -o $@

clean:
	$(RM) $(BUILDDIR)
