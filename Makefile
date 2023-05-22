#==========================================================#
#===============    Makefile v1.0    ======================#
#==========================================================#

#==========================================================
#  Commands
CC		= gcc
CPP		= g++
AR		= ar
RANLIB	= ranlib

#  Flags
ifeq ($(BUILD),DEBUG)
D = d
C_FLAGS			= -g -O0 -rdynamic -Wall -D_DEBUG -DLINUX -fpic -ldl -std=c++11
CXX_FLAGS 		= -g -O0 -rdynamic -Wall -Woverloaded-virtual -D_DEBUG -DLINUX -fpic -ldl -std=c++11
else
D = 
C_FLAGS			= -g -rdynamic -Wall -DNDEBUG -DLINUX -fpic -ldl -std=c++11
CXX_FLAGS 		= -g -rdynamic -Wall -Woverloaded-virtual -DNDEBUG -DLINUX -fpic -ldl -std=c++11
endif

ARFLAGS			= -rc
#==========================================================

#==========================================================
#  Commands
CODE_DIR = ./ 
INCLUDE_DIR =./ 
LIB_FILE = -L./Debug -Lcrypto -lpthread
OUTPUT_DIR =./Debug
OUTPUT = lock_free_queue

#==========================================================

OBJS = $(foreach i, $(CODE_DIR), $(shell find $(i) -name "*.cpp"))
COBJS = $(foreach i, $(CODE_DIR), $(shell find $(i) -name "*.cc"))
INCLUDE_FLAG = $(foreach i, $(INCLUDE_DIR), -I$(i))

all:$(OUTPUT)

$(OUTPUT):$(COBJS:.cc=.o) $(OBJS:.cpp=.o) $(OUTPUT_DIR)
	@echo Build...$@
	$(CPP) $(CXX_FLAGS) -o $(OUTPUT_DIR)/$(OUTPUT) $(COBJS:.cc=.o) $(OBJS:.cpp=.o) $(LIB_FILE)

%.o: %.cpp
	@echo Compile...$@
	$(CPP) $(CXX_FLAGS) $(INCLUDE_FLAG) -c $< -o $@ -MMD -MP -MF$(@:%.o=%.d) 

%.o: %.cc
	@echo Compile...$@
	$(CC) $(C_FLAGS) $(INCLUDE_FLAG) -c $< -o $@ -MMD -MP -MF$(@:%.o=%.d)

$(OUTPUT_DIR):
	-mkdir -p $(OUTPUT_DIR)
	
-include $(OBJS:.cpp=.d)
-include $(COBJS:.cc=.d)

clean:
	rm -f $(OUTPUT_DIR)/$(OUTPUT)
	rm -f $(OBJS:.cpp=.o)
	rm -f $(OBJS:.cpp=.d)
	rm -f $(COBJS:.cc=.o)
	rm -f $(COBJS:.cc=.d)
	
	@echo Clean ...done!
