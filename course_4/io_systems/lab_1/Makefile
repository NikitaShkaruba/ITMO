SYSTEMC_HOME    = systemc-2.3.1a
TARGET_ARCH     = linux64

SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-$(TARGET_ARCH)

FLAGS           = -g -Wall -pedantic -Wno-long-long \
                 -DSC_INCLUDE_DYNAMIC_PROCESSES -fpermissive \
                 -I$(SYSTEMC_INC_DIR)
LDFLAGS         = -L$(SYSTEMC_LIB_DIR) -lsystemc -lm

SRCS = src/mips32.cpp src/mem.cpp src/main.cpp
OBJS = $(SRCS:.cpp=.o)

main:
	g++ -std=c++11 -Wall -pedantic -o model $(LDFLAGS) $(FLAGS) $(SRCS)
