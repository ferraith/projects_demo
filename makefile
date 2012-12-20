########################################################################################################################
#
# Project: Demo Application
#
# Description:
#	Makefile used to build the startup code and main function of the demo application including all libraries.
#
########################################################################################################################
#
# Configuration
#
#============================== Common =================================================================================
PROJ_NAME = demo

#============================== Build ==================================================================================
# Placement Type (flash|ram)
PLACEMENT_TYPE := flash

BUILD_DIR   = build/$(PLATFORM)/$(BUILD_TYPE)
ifeq ($(PLACEMENT_TYPE),flash)
PLACEMENT  := $(CURDIR)/misc/flash_placement.xml
else
PLACEMENT  := $(CURDIR)/misc/ram_placement.xml
endif
MEMORY_MAP := $(CURDIR)/misc/LPC1769_MemoryMap.xml
LINK_PATCH := $(CURDIR)/misc/LPC1000_LinkPatch.js

#============================== Libraries ==============================================================================
# debugIO Support (mempoll|breakpoint|none)
DEBUGIO_SUPPORT := mempoll
# Data Type Support of printf (int|long|long_long|double|none)
PRINTF_SUPPORT  := int
# Data Type Support of scanf (int|long|long_long|double|none)
SCANF_SUPPORT   := int

#============================== Toolchain ==============================================================================
include toolchain/make/toolchain.mk


########################################################################################################################
#
# Libraries
#
#============================== Standard Libraries =====================================================================
include toolchain/make/libs.mk

#============================== Platform Libraries =====================================================================
# CMSIS-CORE LPC17xx
PLTF_LIB_DIRS  = platform/cmsis_core_lpc17xx
PLTF_INC_DIRS  = platform/cmsis_core_lpc17xx/src/core/include
PLTF_INC_DIRS += platform/cmsis_core_lpc17xx/src/device/include
PLTF_LIBS      = platform/cmsis_core_lpc17xx/build/$(PLATFORM)/$(BUILD_TYPE)/cmsis_core_lpc17xx.a

# CMSIS-DSP
# PLTF_LIB_DIRS += platform/cmsis_dsp
# PLTF_INC_DIRS += platform/cmsis_dsp/src/include
# PLTF_LIBS     += platform/cmsis_dsp/build/$(PLATFORM)/$(BUILD_TYPE)/cmsis_dsp.a

# LPC17xx
PLTF_LIB_DIRS += platform/lpc17xx
PLTF_INC_DIRS += platform/lpc17xx/src/include
PLTF_LIBS     += platform/lpc17xx/build/$(PLATFORM)/$(BUILD_TYPE)/lpc17xx.a

# AOAA Kit
PLTF_LIB_DIRS += platform/aoaa
PLTF_INC_DIRS += platform/aoaa/src/include
PLTF_LIBS     += platform/aoaa/build/$(PLATFORM)/$(BUILD_TYPE)/aoaa.a

# FreeRTOS
PLTF_LIB_DIRS += platform/freertos
PLTF_INC_DIRS += platform/freertos/src/include
PLTF_LIBS     += platform/freertos/build/$(PLATFORM)/$(BUILD_TYPE)/freertos.a

# LPC17xx
PLTF_LIB_DIRS += platform/lwip
PLTF_INC_DIRS += platform/lwip/src/include/ipv4/lwip
PLTF_INC_DIRS += platform/lwip/src/include/lwip
PLTF_INC_DIRS += platform/lwip/src/include/netif
PLTF_INC_DIRS += platform/lwip/src/include/posix
PLTF_INC_DIRS += platform/lwip/src/include/posix/sys
PLTF_LIBS     += platform/lwip/build/$(PLATFORM)/$(BUILD_TYPE)/lwip.a

########################################################################################################################
#
# Project Files
#
#============================== Source Directories =====================================================================
PROJ_SRC_DIRS  = src

#============================== Header Directories =====================================================================
PROJ_INC_DIRS  = src/include

#============================== Object Directories =====================================================================
PROJ_OBJ_DIRS  =


########################################################################################################################
#
# GCC & Binutils Flags
#
#============================== Common Flags ===========================================================================
include toolchain/make/flags.mk

#============================== Project Preprocessor Flags =============================================================
CPPFLAGS += -D__TARGET_PROCESSOR=LPC1769
CPPFLAGS += -DOSCILLATOR_CLOCK_FREQUENCY=12000000
CPPFLAGS += -DUSE_PROCESS_STACK

ifeq ($(BUILD_TYPE),debug)
else ifeq ($(BUILD_TYPE),release)
endif

#============================== Project S Compile Flags ================================================================
SFLAGS +=

ifeq ($(BUILD_TYPE),debug)
else ifeq ($(BUILD_TYPE),release)
endif

#============================== Project C Compile Flags ================================================================
CFLAGS +=

ifeq ($(BUILD_TYPE),debug)
else ifeq ($(BUILD_TYPE),release)
endif

#============================== Project Assembler Flags ================================================================
ASFLAGS +=

ifeq ($(BUILD_TYPE),debug)
else ifeq ($(BUILD_TYPE),release)
endif

#============================== Project Linker Flags ===================================================================
LDFLAGS  = -X
LDFLAGS += -ereset_handler
LDFLAGS += --omagic
LDFLAGS += -u_vectors
LDFLAGS += --fatal-warnings
LDFLAGS += -EL
# LDFLAGS += --allow-multiple-definition
# LDFLAGS += --no-warn-mismatch
ifeq ($(PLACEMENT_TYPE),$(filter $(PLACEMENT_TYPE),ram))
LDFLAGS += -s
endif

LDFLAGS += -defsym __STACKSIZE__=256                                    # Main Stack Size
LDFLAGS += -defsym __STACKSIZE_PROCESS__=0                              # Process Stack Size
LDFLAGS += -defsym __HEAPSIZE__=0                                       # Heap Size

ifeq ($(PRINTF_SUPPORT),int)
LDFLAGS += -defsym=__vfprintf=__vfprintf_int                            # Printf Fixed Point Support: int
LDFLAGS += -u__vfprintf_int                                             # Printf Fixed Point Support: int
else ifeq ($(PRINTF_SUPPORT),long)
LDFLAGS += -defsym=__vfprintf=__vfprintf_long                           # Printf Fixed Point Support: long
LDFLAGS += -u__vfprintf_long                                            # Printf Fixed Point Support: long
else ifeq ($(PRINTF_SUPPORT),long_long)
LDFLAGS += -defsym=__vfprintf=__vfprintf_long_long                      # Printf Fixed Point Support: long_long
LDFLAGS += -u__vfprintf_long_long                                       # Printf Fixed Point Support: long_long
else ifeq ($(PRINTF_SUPPORT),double)
LDFLAGS += -defsym=__vfprintf=__vfprintf_double_long_long               # Printf Floating Point Support
LDFLAGS += -u__vfprintf_double_long_long                                # Printf Floating Point Support
else ifeq ($(PRINTF_SUPPORT),nwp)
LDFLAGS += -defsym=__vfprintf=__vfprintf_int_nwp                        # Printf No Width/Precision Support
LDFLAGS += -u__vfprintf_int_nwp                                         # Printf No Width/Precision Support
else ifeq ($(PRINTF_SUPPORT),none)
endif

ifeq ($(SCANF_SUPPORT),int)
LDFLAGS += -defsym=__vfscanf=__vfscanf_int                              # Scanf Fixed Point Support: int
LDFLAGS += -u__vfscanf_int                                              # Scanf Fixed Point Support: int
else ifeq ($(SCANF_SUPPORT),long)
LDFLAGS += -defsym=__vfscanf=__vfscanf_long                             # Scanf Fixed Point Support: long
LDFLAGS += -u__vfscanf_long                                             # Scanf Fixed Point Support: long
else ifeq ($(SCANF_SUPPORT),long_long)
LDFLAGS += -defsym=__vfscanf=__vfscanf_long_long                        # Scanf Fixed Point Support: long_long
LDFLAGS += -u__vfscanf_long_long                                        # Scanf Fixed Point Support: long_long
else ifeq ($(SCANF_SUPPORT),double)
LDFLAGS += -defsym=__vfscanf=__vfscanf_double_long_long                 # Scanf Floating Point Support
LDFLAGS += -u__vfscanf_double_long_long                                 # Scanf Floating Point Support
else ifeq ($(SCANF_SUPPORT),int_cc)
LDFLAGS += -defsym=__vfscanf=__vfscanf_int_cc                           # Scanf Classes Support
LDFLAGS += -u__vfscanf_int_cc                                           # Scanf Classes Support
else ifeq ($(SCANF_SUPPORT),none)
endif

ifeq ($(BUILD_TYPE),debug)
ifeq ($(DEBUGIO_SUPPORT),mempoll)
LDFLAGS += -defsym=__do_debug_operation=__do_debug_operation_mempoll    # DebugIO Memory Pool
LDFLAGS += -u__do_debug_operation_mempoll                               # DebugIO Memory Pool
else ifeq ($(DEBUGIO_SUPPORT),breakpoint)
LDFLAGS += -defsym=__do_debug_operation=__do_debug_operation_bkpt       # DebugIO Breakpoint
LDFLAGS += -u__do_debug_operation_bkpt                                  # DebugIO Breakpoint
else ifeq ($(DEBUGIO_SUPPORT),none)
endif
else ifeq ($(BUILD_TYPE),release)
endif


########################################################################################################################
#
# Build Environment
#
#============================== Strip Variables ========================================================================
STD_INC_DIRS  := $(strip $(STD_INC_DIRS))
STD_LIBS      := $(strip $(STD_LIBS))
PLTF_INC_DIRS := $(strip $(PLTF_INC_DIRS))
PLTF_LIBS     := $(strip $(PLTF_LIBS))
PROJ_SRC_DIRS := $(strip $(PROJ_SRC_DIRS))
PROJ_INC_DIRS := $(strip $(PROJ_INC_DIRS))
PROJ_OBJ_DIRS := $(strip $(PROJ_OBJ_DIRS))
CPPFLAGS      := $(strip $(CPPFLAGS))
SFLAGS        := $(strip $(SFLAGS))
CFLAGS        := $(strip $(CFLAGS))
ASFLAGS       := $(strip $(ASFLAGS))
LDFLAGS       := $(strip $(LDFLAGS))

#============================== vpath Directories ======================================================================
vpath %.s $(PROJ_SRC_DIRS)
vpath %.c $(PROJ_SRC_DIRS)
vpath %.o $(PROJ_OBJ_DIRS) $(BUILD_DIR)
vpath %.elf $(BUILD_DIR)

#============================== Build Variables ========================================================================
find_s_files = $(wildcard $(PROJ_SRC_DIR)/*.s)
find_c_files = $(wildcard $(PROJ_SRC_DIR)/*.c)
find_o_files = $(wildcard $(PROJ_OBJ_DIR)/*.o)

PROJ_S_SRCS := $(notdir $(foreach PROJ_SRC_DIR,$(PROJ_SRC_DIRS),$(find_s_files)))
PROJ_C_SRCS := $(notdir $(foreach PROJ_SRC_DIR,$(PROJ_SRC_DIRS),$(find_c_files)))
PROJ_O_SRCS := $(notdir $(foreach PROJ_OBJ_DIR,$(PROJ_OBJ_DIRS),$(find_o_files)))

PROJ_OBJS    = $(strip $(PROJ_S_SRCS:.s=.o) $(PROJ_C_SRCS:.c=.o) $(PROJ_O_SRCS))

STD_INCS     = $(addprefix -isystem, $(STD_INC_DIRS))
PLTF_INCS    = $(addprefix -I, $(PLTF_INC_DIRS))
PROJ_INCS    = $(addprefix -I, $(PROJ_INC_DIRS))


########################################################################################################################
#
# Targets
#
#============================== Common Rules ===========================================================================
include toolchain/make/rules.mk

#============================== Project Build Targets ==================================================================
all: $(PROJ_NAME).elf

$(PROJ_NAME).elf: pltf_libs pre_$(PROJ_NAME) $(PROJ_OBJS) $(STD_LIBS) $(PLTF_LIBS) $(PROJ_NAME).ld
	$(foreach PROJ_OBJ_DIR, $(PROJ_OBJ_DIRS), $(CP) -u $(PROJ_OBJ_DIR)/*.o $(BUILD_DIR))
	$(ECHO) "    LD $(PROJ_OBJS)"
	$(ECHO) "       $(notdir $(PLTF_LIBS))"
	$(ECHO) "       $(notdir $(STD_LIBS))"
	$(LD) $(LDFLAGS) --gc-sections "-T$(BUILD_DIR)/$(PROJ_NAME).ld" -Map $(BUILD_DIR)/$(PROJ_NAME).map \
		-o $(BUILD_DIR)/$(PROJ_NAME).elf --start-group $(addprefix $(BUILD_DIR)/, $(PROJ_OBJS)) $(STD_LIBS) \
		$(PLTF_LIBS) --end-group
ifeq ($(PLACEMENT_TYPE),flash)
	$(ECHO) "    CROSSSCRIPT $(PROJ_NAME).elf"
	$(CROSSSCRIPT) -load $(LINK_PATCH) "patch('$(BUILD_DIR)/$(PROJ_NAME).elf');"
endif

$(PROJ_NAME).ld:
	$(ECHO) "    CCD $(BUILD_DIR)/$(PROJ_NAME).ld"
	$(shell cd $(BUILD_DIR); $(CCD) $(PLACEMENT) $(MEMORY_MAP) -o $(PROJ_NAME).tmp &> /dev/null)
	$(SED) -i '/__STACKSIZE__ = \|__STACKSIZE_IRQ__ = \|__STACKSIZE_FIQ__ = \|__STACKSIZE_SVC__ = '\
	'\|__STACKSIZE_ABT__ = \|__STACKSIZE_UND__ = \|__HEAPSIZE__ = /d' $(BUILD_DIR)/$(PROJ_NAME).ld
	$(RM) $(BUILD_DIR)/$(PROJ_NAME).map

$(PROJ_NAME).hex: $(PROJ_NAME).elf
	$(ECHO) "    OBJCOPY		$(PROJ_NAME).hex"
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(PROJ_NAME).elf $(BUILD_DIR)/$(PROJ_NAME).hex

$(PROJ_NAME).bin: $(PROJ_NAME).elf
	$(ECHO) "    OBJCOPY		$(PROJ_NAME).bin"
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(PROJ_NAME).elf $(BUILD_DIR)/$(PROJ_NAME).bin
	
$(PROJ_NAME).srec: $(PROJ_NAME).elf
	$(ECHO) "    OBJCOPY		$(PROJ_NAME).srec"
	$(OBJCOPY) -O srec $(BUILD_DIR)/$(PROJ_NAME).elf $(BUILD_DIR)/$(PROJ_NAME).srec

pltf_libs: $(PLTF_LIB_DIRS)

$(PLTF_LIB_DIRS):
	$(MAKE) -C $@ all BUILD_TYPE=$(BUILD_TYPE) PLATFORM=$(PLATFORM)

clean_all: clean
	$(foreach PLTF_LIB_DIR, $(PLTF_LIB_DIRS), $(MAKE) -C $(PLTF_LIB_DIR) clean;)

#============================== Phony Targets ==========================================================================
.PHONY: pltf_libs $(PLTF_LIB_DIRS) clean_all
