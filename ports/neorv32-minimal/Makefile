# Include the core environment definitions; this will set $(TOP).
include ../../py/mkenv.mk

# Include py core make definitions.
include $(TOP)/py/py.mk
include $(TOP)/extmod/extmod.mk

# Do cross-compilation for riscv
CROSS=1
CROSS_COMPILE ?= riscv32-unknown-elf-
MARCH ?= rv32i_zicsr_zifencei
MABI  ?= ilp32
#OBJCOPY = $(RISCV_PREFIX)objcopy

# NeoRV32 folders
NEORV32_HOME ?= /home/daniel/git-dropbox/softcore_micropython/common/neorv32
# Path to NEORV32 linker script and startup file
NEORV32_COM_PATH = $(NEORV32_HOME)/sw/common
# Path to main NEORV32 library include files
NEORV32_INC_PATH = $(NEORV32_HOME)/sw/lib/include
# Path to main NEORV32 library source files
NEORV32_SRC_PATH = $(NEORV32_HOME)/sw/lib/source
# Path to NEORV32 executable generator
NEORV32_EXG_PATH = $(NEORV32_HOME)/sw/image_gen

# Main output files
APP_EXE  = neorv32_exe.bin

# NEORV32 executable image generator
IMAGE_GEN = $(NEORV32_EXG_PATH)/image_gen

# Set CFLAGS and libraries.
CFLAGS_NEORV32  = -march=$(MARCH) -mabi=$(MABI) $(EFFORT) -Wall -ffunction-sections -fdata-sections -nostartfiles -mno-fdiv
CFLAGS_NEORV32 += -mstrict-align -mbranch-cost=10 -Wl,--gc-sections -ffp-contract=off
CFLAGS += $(CFLAGS_NEORV32) -I. -I$(BUILD) -I$(TOP) -I$(NEORV32_INC_PATH)
CFLAGS += -Os # Save some codespace
#CFLAGS += -fdata-sections -ffunction-sections
LIBS += -lm


# Set LDFLAGS (linking)
#LDFLAGS += $(CFLAGS) -T neorv32.ld -Map=$@.map --cref --gc-sections
LDFLAGS += $(CFLAGS) -T neorv32.ld

# Define the required source files.
SRC_C = \
	main.c \
	mphalport.c \
	shared/readline/readline.c \
	shared/runtime/gchelper_generic.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c \

# Include NeoRV32 C files
SRC_C += $(wildcard $(NEORV32_SRC_PATH)/*.c)

SRC_S = \
	crt0.S

# Define source files containung qstrs.
SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c

# Define the required object files.
OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_S:.S=.o))

# Define the top-level target, the main firmware.
#all: $(BUILD)/firmware.elf
exe: $(APP_EXE)
all: $(BUILD)/main.bin


# Compile image generator
$(IMAGE_GEN): $(NEORV32_EXG_PATH)/image_gen.c
	@echo Compiling $(IMAGE_GEN)
	@$(CC_HOST) $< -o $(IMAGE_GEN)

# Define how to build the firmware.
$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(ECHO) "LINKING FILES: $^"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(Q)$(SIZE) $@

# Generate final executable from .text + .rodata + .data (in THIS order!)
$(BUILD)/main.bin: $(BUILD)/firmware.elf
	@$(OBJCOPY) -I elf32-little $< -j .text   -O binary text.bin
	@$(OBJCOPY) -I elf32-little $< -j .rodata -O binary rodata.bin
	@$(OBJCOPY) -I elf32-little $< -j .data   -O binary data.bin
	@cat text.bin rodata.bin data.bin > $@
	@rm -f text.bin rodata.bin data.bin

# Generate NEORV32 executable image for upload via bootloader
$(APP_EXE): $(BUILD)/main.bin $(IMAGE_GEN)
	@set -e
	@$(IMAGE_GEN) -app_bin $< $@ $(shell basename $(CURDIR))
	@echo "Executable ($(APP_EXE)) size in bytes:"
	@wc -c < $(APP_EXE)

# Include remaining core make rules.
include $(TOP)/py/mkrules.mk
