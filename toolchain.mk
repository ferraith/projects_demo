########################################################################################################################
#
# Workspace: Android Open Accessory Software for AOAA Kit
#
# Description:
#	Makefile used for the configuration of the toolchain.
#
#============================== Paths ==================================================================================
CW_DIR       := c:/DevTools/CrossWorks_for_ARM_2.3
CWT_DIR      := $(CW_DIR)/bin
CWL_DIR      := $(CW_DIR)/lib
CWI_DIR      := $(CW_DIR)/include
GCC_DIR      := $(CW_DIR)/gcc/arm-unknown-eabi/bin

#============================== GNU Compiler Collection ================================================================
CC          := $(GCC_DIR)/cc1.exe
CPP         := $(GCC_DIR)/cc1plus.exe
AS          := $(GCC_DIR)/as.exe
AR          := $(GCC_DIR)/ar.exe
LD          := $(GCC_DIR)/ld.exe
OBJCOPY     := $(GCC_DIR)/objcopy.exe

#============================== Rowley Crossworks ======================================================================
CCD         := $(CWT_DIR)/cc.exe
CROSSSCRIPT := $(CWT_DIR)/crossscript.exe

#============================== Binutils ===============================================================================
CP          := cp
ECHO        := echo -e
MAKE        := make -s
MKDIR       := mkdir
RM          := rm -f

#============================== Unix Utilities =========================================================================
SED         := sed
