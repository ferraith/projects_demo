########################################################################################################################
#
# Workspace: Android Open Accessory Software for AOAA Kit
#
# Description:
#    Makefile used for the definition of common GCC & Binutils flags.
#
#============================== Preprocessor Flags =====================================================================
CPPFLAGS  = -nostdinc
CPPFLAGS += -quiet
CPPFLAGS += -D__ARM_ARCH_7M__
CPPFLAGS += -D__THUMB
CPPFLAGS += -D__CROSSWORKS_ARM
CPPFLAGS += -D__CROSSWORKS_MAJOR_VERSION=2
CPPFLAGS += -D__CROSSWORKS_MINOR_VERSION=2
CPPFLAGS += -D__CROSSWORKS_REVISION=0
# CPPFLAGS += -D__SHORT_DOUBLES

ifeq ($(BUILD_PLACEMENT),flash)
CPPFLAGS += -D__FLASH_BUILD
else ifeq ($(BUILD_PLACEMENT),ram)
CPPFLAGS += -D__RAM_BUILD
else ifeq ($(BUILD_PLACEMENT),none)

endif
ifeq ($(BUILD_TYPE),debug)
CPPFLAGS += -DDEBUG
else ifeq ($(BUILD_TYPE),release)
CPPFLAGS += -DNDEBUG
endif

#============================== S Compile Flags ========================================================================
SFLAGS  = -E

ifeq ($(BUILD_TYPE),debug)
SFLAGS += -g2
else ifeq ($(BUILD_TYPE),release)
SFLAGS += -g1
endif

#============================== C Compile Flags ========================================================================
CFLAGS  = -fmessage-length=0
CFLAGS += -mcpu=cortex-m3
CFLAGS += -mthumb
CFLAGS += -mlittle-endian
CFLAGS += -mfpu=vfp
CFLAGS += -mfloat-abi=soft
CFLAGS += -std=c99
CFLAGS += -fno-dwarf2-cfi-asm
CFLAGS += -fno-builtin
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -fno-common
CFLAGS += -Wall
CFLAGS += -mapcs-frame
CFLAGS += -mno-sched-prolog
# CFLAGS += -fomit-frame-pointer
# CFLAGS += -mlong-calls
# CFLAGS += -fshort-double

ifeq ($(BUILD_TYPE),debug)
CFLAGS += -g2
else ifeq ($(BUILD_TYPE),release)
CFLAGS += -O1
endif

#============================== C++ Compile Flags ======================================================================
CXXFLAGS  =

#============================== Assembler Flags ========================================================================
ASFLAGS  = --traditional-format
ASFLAGS += -mcpu=cortex-m3
ASFLAGS += -mthumb
ASFLAGS += -EL
ASFLAGS += -mfpu=vfp
ASFLAGS += -mfloat-abi=soft
ASFLAGS += -gdwarf-2

ifeq ($(BUILD_TYPE),debug)
else ifeq ($(BUILD_TYPE),release)
endif

#============================== Archiver Flags =========================================================================
ARFLAGS  = -r
ARFLAGS += -c
ARFLAGS += -s
