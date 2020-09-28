# Commands
CC=g++ #icpc
CPY = cp -v
REM = rm -rfv
MKDIR = mkdir -pv

# Directories
GEN_DIR = gen
EXEC_DIR = exec

# Compiler options
CFLAGS := $(CFLAGS) -DDEBUG # -g
#CFLAGS := $(CFLAGS) -static-libgcc -static-libstdc++ # -static-intel
CFLAGS := $(CFLAGS) -fstrict-aliasing
CFLAGS := $(CFLAGS) -std=c++11
CFLAGS := $(CFLAGS) -fPIC
CFLAGS := $(CFLAGS) -O2
CFLAGS := $(CFLAGS) -Wall
CFLAGS := $(CFLAGS) -I./include -I./$(GEN_DIR)

LDFLAGS := $(LDFLAGS) -lrt
LDFLAGS := $(LDFLAGS) -lthrift
LDFLAGS := $(LDFLAGS) -lpthread

# Object file collections
GEN_SHARED = $(GEN_DIR)/shared_types.o \
	$(GEN_DIR)/shared_constants.o

GEN_SERVICE = $(GEN_SHARED) \
	$(GEN_DIR)/Service.o \
	$(GEN_DIR)/service_types.o \
	$(GEN_DIR)/service_constants.o

# NOTE: Indent using Tabs, otherwise build will fail!
all: server

run: server
	./$(EXEC_DIR)/server

server: $(GEN_SERVICE) server.o
	$(MKDIR) $(EXEC_DIR)
	$(CC) $(CFLAGS) $^ -o $(EXEC_DIR)/$@ $(LDFLAGS)

clean:
	$(REM) $(EXEC_DIR)
	$(REM) *.o $(GEN_DIR)/*.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)
