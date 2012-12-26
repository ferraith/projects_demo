########################################################################################################################
#
# Workspace: Android Open Accessory Software for AOAA Kit
#
# Description:
#	Makefile used for the definition of standard libraries.
#
#============================== Optimization: None =====================================================================
STD_INC_DIRS  = $(CWI_DIR)
STD_LIBS  = $(CWL_DIR)/libc_v7m_t_le_eabi.a                          # Crossworks Standard C Library
# STD_LIBS += $(CWL_DIR)/libcpp_v7m_t_le_eabi.a                      # Crossworks Standard C++ Library
# STD_LIBS += $(CWL_DIR)/libm_v7m_t_le_eabi.a                        # Crossworks Standard C Math Library
# STD_LIBS += $(CWL_DIR)/libgccxceptrtti_v7m_t_le_eabi.a             # GCC Exception and RTTI Library
STD_LIBS += $(CWL_DIR)/libc_user_libc_v7m_t_le_eabi.a                # Crossworks Multi Threaded Library
# STD_LIBS += $(CWL_DIR)/liblpc1000_v7m_t_le_eabi.a                  # Crossworks NXP LPC1000 ARMv7-M Library

ifeq ($(BUILD_TYPE),debug)
ifeq ($(DEBUGIO_SUPPORT),$(filter $(DEBUGIO_SUPPORT),mempoll breakpoint))
STD_LIBS += $(CWL_DIR)/libdebugio_v7m_t_le_eabi.a                    # Crossworks debugIO Library
# STD_LIBS += $(CWL_DIR)/libc_debugio_impl_v7m_t_le_eabi.a           # Crossworks debugIO Implementation Library
# STD_LIBS += $(CWL_DIR)/libc_targetio_impl_v7m_t_le_eabi.a          # Crossworks debugIO Target Implementation Library
endif
else ifeq ($(BUILD_TYPE),release)
endif

#============================== Optimization: Fast =====================================================================
# STD_INC_DIRS  = $(CWI_DIR)
# STD_LIBS  = $(CWL_DIR)/libc_v7m_t_le_eabi_f.a                      # Crossworks Standard C Library
# STD_LIBS += $(CWL_DIR)/libcpp_v7m_t_le_eabi_f.a                    # Crossworks Standard C++ Library
# STD_LIBS += $(CWL_DIR)/libm_v7m_t_le_eabi_f.a                      # Crossworks Standard C Math Library
# STD_LIBS += $(CWL_DIR)/libgccxceptrtti_v7m_t_le_eabi_f.a           # GCC Exception and RTTI Library
# STD_LIBS += $(CWL_DIR)/libc_user_libc_v7m_t_le_eabi_f.a            # Crossworks Multi Threaded Library
# STD_LIBS += $(CWL_DIR)/liblpc1000_v7m_t_le_eabi_f.a                # Crossworks NXP LPC1000 ARMv7-M Library

ifeq ($(BUILD_TYPE),debug)
ifeq ($(DEBUGIO_SUPPORT),$(filter $(DEBUGIO_SUPPORT),mempoll breakpoint))
# STD_LIBS += $(CWL_DIR)/libdebugio_v7m_t_le_eabi_f.a                # Crossworks debugIO Library
# STD_LIBS += $(CWL_DIR)/libc_debugio_impl_v7m_t_le_eabi_f.a         # Crossworks debugIO Implementation Library
# STD_LIBS += $(CWL_DIR)/libc_targetio_impl_v7m_t_le_eabi_f.a        # Crossworks debugIO Target Implementation Library
endif
else ifeq ($(BUILD_TYPE),release)
endif

#============================== Optimization: Small ====================================================================
# STD_INC_DIRS  = $(CWI_DIR)
# STD_LIBS  = $(CWL_DIR)/libc_v7m_t_le_eabi_small.a                  # Crossworks Standard C Library
# STD_LIBS += $(CWL_DIR)/libcpp_v7m_t_le_eabi_small.a                # Crossworks Standard C++ Library
# STD_LIBS += $(CWL_DIR)/libm_v7m_t_le_eabi_small.a                  # Crossworks Standard C Math Library
# STD_LIBS += $(CWL_DIR)/libgccxceptrtti_v7m_t_le_eabi_small.a       # GCC Exception and RTTI Library
# STD_LIBS += $(CWL_DIR)/libc_user_libc_v7m_t_le_eabi_small.a        # Crossworks Multi Threaded Library
# STD_LIBS += $(CWL_DIR)/liblpc1000_v7m_t_le_eabi_small.a            # Crossworks NXP LPC1000 ARMv7-M Library

ifeq ($(BUILD_TYPE),debug)
ifeq ($(DEBUGIO_SUPPORT),$(filter $(DEBUGIO_SUPPORT),mempoll breakpoint))
# STD_LIBS += $(CWL_DIR)/libdebugio_v7m_t_le_eabi_small.a            # Crossworks debugIO Library
# STD_LIBS += $(CWL_DIR)/libc_debugio_impl_v7m_t_le_eabi_small.a     # Crossworks debugIO Implementation Library
# STD_LIBS += $(CWL_DIR)/libc_targetio_impl_v7m_t_le_eabi_small.a    # Crossworks debugIO Target Implementation Library
endif
else ifeq ($(BUILD_TYPE),release)
endif

#============================== Optimization: Fast & Small =============================================================
# STD_INC_DIRS  = $(CWI_DIR)
# STD_LIBS  = $(CWL_DIR)/libc_v7m_t_le_eabi_f_small.a                # Crossworks Standard C Library
# STD_LIBS += $(CWL_DIR)/libcpp_v7m_t_le_eabi_f_small.a              # Crossworks Standard C++ Library
# STD_LIBS += $(CWL_DIR)/libm_v7m_t_le_eabi_f_small.a                # Crossworks Standard C Math Library
# STD_LIBS += $(CWL_DIR)/libgccxceptrtti_v7m_t_le_eabi_f_small.a     # GCC Exception and RTTI Library
# STD_LIBS += $(CWL_DIR)/libc_user_libc_v7m_t_le_eabi_f_small.a      # Crossworks Multi Threaded Library
# STD_LIBS += $(CWL_DIR)/liblpc1000_v7m_t_le_eabi_small_f.a          # Crossworks NXP LPC1000 ARMv7-M Library

ifeq ($(BUILD_TYPE),debug)
ifeq ($(DEBUGIO_SUPPORT),$(filter $(DEBUGIO_SUPPORT),mempoll breakpoint))
# STD_LIBS += $(CWL_DIR)/libdebugio_v7m_t_le_eabi_f_small.a          # Crossworks debugIO Library
# STD_LIBS += $(CWL_DIR)/libc_debugio_impl_v7m_t_le_eabi_f_small.a   # Crossworks debugIO Implementation Library
# STD_LIBS += $(CWL_DIR)/libc_targetio_impl_v7m_t_le_eabi_f_small.a  # Crossworks debugIO Target Implementation Library
endif
else ifeq ($(BUILD_TYPE),release)
endif
