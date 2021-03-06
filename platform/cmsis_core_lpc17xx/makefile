########################################################################################################################
#
# Project: CMSIS-CORE LPC17xx Library
#
# Description:
# Makefile used to build the CMSIS-CORE LPC17xx Library.
#
########################################################################################################################
#
# Configuration
#
#============================== Common =================================================================================
PROJ_NAME = cmsis_core_lpc17xx

#============================== Build ==================================================================================
BUILD_DIR = build/$(PLATFORM)/$(BUILD_TYPE)

#============================== Toolchain ==============================================================================
include ../../toolchain/make/toolchain.mk


########################################################################################################################
#
# Libraries
#
#============================== Standard Libraries =====================================================================
include ../../toolchain/make/libs.mk


########################################################################################################################
#
# Project Files
#
#============================== Source Directories =====================================================================
PROJ_SRC_DIRS  = src

#============================== Header Directories =====================================================================
PROJ_INC_DIRS  = include/cmsis_core_lpc17xx

#============================== Object Directories =====================================================================
PROJ_OBJ_DIRS  =


########################################################################################################################
#
# GCC & Binutils Flags
#
#============================== Common Flags ===========================================================================
include ../../toolchain/make/flags.mk

#============================== Project Preprocessor Flags =============================================================
CPPFLAGS +=

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

#============================== Project C++ Compile Flags ==============================================================
CXXFLAGS +=

ifeq ($(BUILD_TYPE),debug)
else ifeq ($(BUILD_TYPE),release)
endif

#============================== Project Assembler Flags ================================================================
ASFLAGS +=

ifeq ($(BUILD_TYPE),debug)
else ifeq ($(BUILD_TYPE),release)
endif

#============================== Project Archiver Flags =================================================================
ARFLAGS +=


########################################################################################################################
#
# Build Environment
#
#============================== Strip Variables ========================================================================
PLTF_INC_DIRS  := $(strip $(PLTF_INC_DIRS))
PROJ_SRC_DIRS := $(strip $(PROJ_SRC_DIRS))
PROJ_INC_DIRS := $(strip $(PROJ_INC_DIRS))
PROJ_OBJ_DIRS := $(strip $(PROJ_OBJ_DIRS))
CPPFLAGS      := $(strip $(CPPFLAGS))
SFLAGS        := $(strip $(SFLAGS))
CFLAGS        := $(strip $(CFLAGS))
CXXFLAGS      := $(strip $(CXXFLAGS))
ASFLAGS       := $(strip $(ASFLAGS))
ARFLAGS       := $(strip $(ARFLAGS))

#============================== vpath Directories ======================================================================
vpath %.s $(PROJ_SRC_DIRS)
vpath %.c $(PROJ_SRC_DIRS)
vpath %.cc $(PROJ_SRC_DIRS)
vpath %.o $(PROJ_OBJ_DIRS) $(BUILD_DIR)
vpath %.a $(BUILD_DIR)

#============================== Build Variables ========================================================================
find_s_files = $(wildcard $(PROJ_SRC_DIR)/*.s)
find_c_files = $(wildcard $(PROJ_SRC_DIR)/*.c)
find_cc_files = $(wildcard $(PROJ_SRC_DIR)/*.cc)
find_o_files = $(wildcard $(PROJ_OBJ_DIR)/*.o)

PROJ_S_SRCS := $(notdir $(foreach PROJ_SRC_DIR,$(PROJ_SRC_DIRS),$(find_s_files)))
PROJ_C_SRCS := $(notdir $(foreach PROJ_SRC_DIR,$(PROJ_SRC_DIRS),$(find_c_files)))
PROJ_CC_SRCS := $(notdir $(foreach PROJ_SRC_DIR,$(PROJ_SRC_DIRS),$(find_cc_files)))
PROJ_O_SRCS := $(notdir $(foreach PROJ_OBJ_DIR,$(PROJ_OBJ_DIRS),$(find_o_files)))

PROJ_OBJS = $(strip $(PROJ_S_SRCS:.s=.o) $(PROJ_C_SRCS:.c=.o) $(PROJ_CC_SRCS:.cc=.o) $(PROJ_O_SRCS))

STD_INCS     = $(addprefix -isystem, $(STD_INC_DIRS))
PROJ_INCS    = $(addprefix -I, $(PROJ_INC_DIRS))


########################################################################################################################
#
# Targets
#
#============================== Common Rules ===========================================================================
include ../../toolchain/make/rules.mk

#============================== Project Build Targets ==================================================================
all: pre_$(PROJ_NAME) $(PROJ_NAME).a

