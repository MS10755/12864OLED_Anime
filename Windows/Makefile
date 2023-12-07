CC = gcc
CXX = g++
LD = ld

TARGET = Simulator.exe

BUILD_DIR = build

OPTS = -O0 -g


DEFINES = -DPLATFORM_WIN32

# add headers files here
INCLUDE_DIR += SDL2/include	\
			../libraries/u8g2/cppsrc \
			../libraries/u8g2/csrc \
			HAL	\
			../UI/anime \
			../UI/page_manager \
			../UI \
			../UI/widget
			


# add .CPP files here
CPP_SOURCES = main.cpp \
			   $(wildcard ../libraries/u8g2/cppsrc/*.cpp) \
			   $(wildcard ../UI/*.cpp) \
			   $(wildcard ../UI/widget/*.cpp)


# add .C files here
C_SOURCES += $(wildcard ../libraries/u8g2/csrc/*.c) \
			../libraries/u8g2/sys/sdl/common/u8x8_d_sdl_128x64.c \
			../libraries/u8g2/sys/sdl/common/u8x8_sdl_key.c \
			HAL/HAL.c \
			$(wildcard ../UI/anime/*.c) \
			../UI/page_manager/page_manager.c \
			$(wildcard ../UI/icons/*.c) 
			


INCLUDE = $(addprefix -I,$(INCLUDE_DIR))

vpath %.cpp $(dir $(CPP_SOURCES))

vpath %.c $(dir $(C_SOURCES))

OBJS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
OBJS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))

ifneq ($(shell gcc --version | findstr "i686" ),)

LIBS = SDL2/lib/x86/SDL2main.lib SDL2/lib/x86/SDL2.lib 
DLL_FILE = SDL2/lib/x86/SDL2.dll

else ifneq ($(shell gcc --version | findstr "x86_64" ),)

LIBS = SDL2/lib/x64/SDL2main.lib SDL2/lib/x64/SDL2.lib 
DLL_FILE = SDL2/lib/x64/SDL2.dll

else
	$(error "Unable to determine the current compiler version！")

endif


LD_FLAGS =

C_CXX_FLAGS = -MMD -MP -MF"$(@:%.o=%.d)"

C_FLAGS = -std=c99 $(C_CXX_FLAGS)

CXX_FLAGS = -std=c++17 $(C_CXX_FLAGS)

$(BUILD_DIR)/$(TARGET): $(BUILD_DIR) $(OBJS) Makefile
	$(CXX) $(LD_FLAGS) $(OBJS) $(LIBS) -o $@
	-cp $(DLL_FILE) build/


$(BUILD_DIR)/%.o : %.cpp Makefile
	$(CXX) $(DEFINES) $(OPTS) $(CXX_FLAGS) $(INCLUDE) -Wall -c $< -o $@

$(BUILD_DIR)/%.o : %.c Makefile
	$(CC) $(DEFINES) $(OPTS) $(C_FLAGS) $(INCLUDE) -Wall -c $< -o $@

clean:
	-rm build/*


$(BUILD_DIR):
	mkdir $@



# print-VIRABLES, this is useful for debug. reference: https://www.cmcrossroads.com/article/printing-value-makefile-variable
print-%  : ; @echo $* = $($*)


-include $(BUILD_DIR)/*.d