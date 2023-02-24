######################################
# target
######################################
TARGET = swm181cbt6

USER_SOURCES = main.c
USER_INCLUDES = 

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization for size
OPT = -Os


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES = \
SWM181_StdPeriph_Driver/CSL/CMSIS/DeviceSupport/system_SWM181.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_uart.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_port.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_adc.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_div.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_can.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_dma.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_slcd.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_sleep.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_cordic.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_cmp.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_flash.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_cache.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_wdt.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_i2c.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_timr.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_pwm.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_sdadc.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_spi.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_irqmux.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_gpio.c \
SWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver/SWM181_exti.c \
$(USER_SOURCES)

# ASM sources
ASM_SOURCES =  SWM181_StdPeriph_Driver/CSL/CMSIS/DeviceSupport/startup/gcc/startup_SWM181.S


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-

CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m0

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

AS_DEFS =

# C defines
C_DEFS = 

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-ISWM181_StdPeriph_Driver/CSL/CMSIS/DeviceSupport \
-ISWM181_StdPeriph_Driver/CSL/CMSIS/CoreSupport \
-ISWM181_StdPeriph_Driver/CSL/SWM181_StdPeriph_Driver \
$(USER_INCLUDES)

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = SWM181_StdPeriph_Driver/swm181.ld 

# libraries
LIBS = -lc -lm -lnosys
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
#$(LUAOBJECTS) $(OBJECTS)
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		
#######################################
# program
#######################################
program:
	pyocd erase -c -t swm181xb --config pyocd.yaml
	pyocd load build/$(TARGET).hex -t swm181xb --config pyocd.yaml

#######################################
# debug
#######################################
debug_pyocd:
	pyocd-gdbserver -t swm181xb --config pyocd.yaml


#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
