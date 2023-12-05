# 编译器设定
PREFIX = arm-none-eabi-
CC	= $(PREFIX)gcc
CXX = $(PREFIX)g++
AS 	= $(PREFIX)as
CP	= $(PREFIX)objcopy
SZ = $(PREFIX)size

TARGET = stm32_anime

# 文件添加
INCLUDES = Core/Inc \
	Drivers/STM32F1xx_HAL_Driver/Inc \
	Drivers/STM32F1xx_HAL_Driver/Inc/Legacy \
	Drivers/CMSIS/Device/ST/STM32F1xx/Include \
	Drivers/CMSIS/Include \
	../../libraries/u8g2/cppsrc \
	../../libraries/u8g2/csrc \
	HAL \
	../../UI/anime \
	../../UI/page_manager \
	../../UI \
	../../UI/widget \
	../../libraries/Juan_EventButton_Library

C_SOURCES = Core/Src/stm32f1xx_it.c \
			Core/Src/stm32f1xx_hal_msp.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c \
			Core/Src/system_stm32f1xx.c \
			stm32_startup.c \
			Core/Src/gpio.c \
			Core/Src/spi.c \
			Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c \
			Core/Src/u8x8_byte_stm32_hw_spi.c \
			Core/Src/u8x8_gpio_and_delay_stm32.c \
			$(wildcard ../../libraries/u8g2/csrc/*.c) \
			HAL/HAL.c \
			$(wildcard ../../UI/anime/*.c) \
			../../UI/page_manager/page_manager.c \
			$(wildcard ../../UI/icons/*.c)  \
			../../libraries/Juan_EventButton_Library/Juan_EventButton.c

CPP_SOURCES = Core/Src/main.cpp \
			$(wildcard ../../libraries/u8g2/cppsrc/*.cpp) \
			$(wildcard ../../UI/*.cpp) \
			$(wildcard ../../UI/widget/*.cpp)


BUILD_DIR = build

OPT = -O2

DEGBU = 0

DEFS = -DUSE_HAL_DRIVER \
-DSTM32F103xE

ifeq ($(DEBUG),1)
FLAGS += g -gdwarf-2
endif



DPENS += -MMD -MP -MF"$(@:%.o=%.d)"

C_DEFS =  -std=c99

CPP_DEFS = -std=c++14 -fno-exceptions -fno-rtti


MCU = -mcpu=cortex-m3 -mthumb 


FLAGS = -Wall -fdata-sections -ffunction-sections -fdiagnostics-color=always

LD_SCRIPT = STM32F103C8Tx_FLASH.ld

LIBS = -lc -lm -lnosys

LD_FLAGS =  -specs=nano.specs -specs=nosys.specs -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

IINCLUDES = $(addprefix -I,$(INCLUDES))


vpath %.c $(dir $(C_SOURCES))

vpath %.cpp $(dir $(CPP_SOURCES))

OBJS = $(foreach OBJ,$(notdir $(C_SOURCES:%.c=%.o)), $(BUILD_DIR)/$(OBJ))
OBJS += $(foreach OBJ,$(notdir $(CPP_SOURCES:%.cpp=%.o)), $(BUILD_DIR)/$(OBJ))


$(BUILD_DIR)/%.o : %.c Makefile
	@echo "gcc compile file:"$<
	$(CC) -c $(MCU) $(DEFS) $(C_DEFS)  $(IINCLUDES) $(OPT) $(FLAGS) $(DPENS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst))   $< -o $@


$(BUILD_DIR)/%.o : %.cpp Makefile
	@echo "g++ compile file:"$<
	$(CXX) -c $(MCU) $(DEFS) $(CPP_DEFS) $(IINCLUDES) $(OPT) $(FLAGS) $(DPENS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst))  $(IINCLUDES) $< -o $@


$(BUILD_DIR)/$(TARGET).elf:  $(BUILD_DIR) $(OBJS) Makefile
	@echo "link all files together"
	@$(CXX) $(MCU) $(LD_FLAGS) -T$(LD_SCRIPT) $(LIBS)  $(OBJS) -o  $@
	@$(SZ) -Ax $@
	@$(SZ) -Bd $@

$(BUILD_DIR):
	@mkdir -p $@


clean:
	@rm -rf $(BUILD_DIR)

# print-VIRABLES, this is useful for debug. reference: https://www.cmcrossroads.com/article/printing-value-makefile-variable
print-%  : ; @echo $* = $($*)

sinclude $(wildcard $(BUILD_DIR)/*.d)