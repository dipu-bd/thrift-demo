CC := g++ #icpc
CPY := cp -v
REM := rm -rfv
MKDIR := mkdir -pv
NPROCS ?= 1
OS := $(shell uname -s)

ifeq ($(OS),Windows_NT)
  $(error Unsupported platform)
endif
ifeq ($(OS),Linux)
  NPROCS:=$(shell grep -c ^processor /proc/cpuinfo)
endif
ifeq ($(OS),Darwin) # Assume Mac OS X
  NPROCS:=$(shell system_profiler | awk '/Number Of CPUs/{print $4}{next;}')
endif

# Directories
GEN_DIR := gen
BUILD_DIR := build
HEADER_DIR := include
BIN_DIR := bin

# Compiler options
CFLAGS += -DDEBUG # -g
#CFLAGS += -static-libgcc -static-libstdc++ # -static-intel
CFLAGS += -fstrict-aliasing
CFLAGS += -std=c++11
CFLAGS += -fPIC
CFLAGS += -O2
CFLAGS += -Wall

# Includes
IFLAGS += -I./$(GEN_DIR)
IFLAGS += -I./$(HEADER_DIR)

# Library flags
LDFLAGS += -lrt
LDFLAGS += -lpthread
LDFLAGS += -lthrift

# Object file collections
GEN_SOURCES := $(shell find $(GEN_DIR) -name '*.cpp')
GEN_OBJECTS := $(addprefix $(BUILD_DIR)/,$(GEN_SOURCES:%.cpp=%.o))

# Define Targets
all :: $(BIN_DIR)/server

clean ::
	@$(REM) $(BIN_DIR) $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ $(LDFLAGS)

$(BIN_DIR)/%:
	@$(MAKE) -j$(NPROCS) $(GEN_OBJECTS) $(BUILD_DIR)/$*.o
	@$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $(GEN_OBJECTS) $(BUILD_DIR)/$*.o -o $@ $(LDFLAGS)
