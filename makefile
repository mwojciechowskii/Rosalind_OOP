workdir :=$(shell pwd)
CXX        := g++
INCLUDES   :=
SRCS       := $(workdir)/src/main.cpp \
			  $(workdir)/src/sequence.cpp
OBJS       := $(patsubst $(workdir)/src/%.cpp,$(workdir)/build/%.o,$(SRCS))
TARGET     ?= myapp

CXXFLAGS_DEBUG   := -g -O0 -std=c++14 -Wall
CXXFLAGS_RELEASE := -O2 -std=c++14 -Wall

CXXFLAGS := $(CXXFLAGS_RELEASE)

.PHONY: all debug release clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(workdir)/build/%.o: $(workdir)/src/%.cpp
	@mkdir -p $(workdir)/build
	$(CXX) $(CXXFLAGS) -c $< -o $@

debug: CXXFLAGS := $(CXXFLAGS_DEBUG)
debug: clean all

release: CXXFLAGS := $(CXXFLAGS_RELEASE)
release: clean all

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS)
