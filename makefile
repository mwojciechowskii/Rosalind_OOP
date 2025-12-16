workdir :=$(shell pwd)
CXX        := g++
INCLUDES   :=
SRCS       := $(workdir)/src/main.cpp \
			  $(workdir)/src/Sequence.cpp \
			  $(workdir)/src/NtSequence.cpp \
			  $(workdir)/src/DNA.cpp \
			  $(workdir)/src/RNA.cpp \
			  $(workdir)/src/fileReader.cpp \
			  $(workdir)/src/Solution.cpp \
			  $(workdir)/src/AaSequence.cpp \
			  $(workdir)/src/Request.cpp
OBJS       := $(patsubst $(workdir)/src/%.cpp,$(workdir)/build/%.o,$(SRCS))
TARGET     ?= myapp

CXXFLAGS_DEBUG   := -g -fsanitize=address,undefined -O0 -std=c++20 -Wall
CXXFLAGS_RELEASE := -O2 -std=c++20 -Wall

CXXFLAGS := $(CXXFLAGS_RELEASE)

.PHONY: all debug release clean run

CURL_CFLAGS := $(shell pkg-config --cflags libcurl 2>/dev/null || echo $(shell curl-config --cflags 2>/dev/null))
CURL_LIBS   := $(shell pkg-config --libs libcurl 2>/dev/null || echo $(shell curl-config --libs 2>/dev/null))

OTHER_LIBS  := -lboost_regex

INCLUDES += $(CURL_CFLAGS)

LDFLAGS := $(CURL_LIBS)
LIBS    := $(OTHER_LIBS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

$(workdir)/build/%.o: $(workdir)/src/%.cpp
	@mkdir -p $(workdir)/build
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

debug: CXXFLAGS := $(CXXFLAGS_DEBUG)
debug: clean all

release: CXXFLAGS := $(CXXFLAGS_RELEASE)
release: clean all

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
