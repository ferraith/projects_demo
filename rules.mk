########################################################################################################################
#
# Workspace: Android Open Accessory Software for AOAA Kit
#
# Description:
#	Makefile used for the definition of common build and clean rules.
#
#============================== Build Targets ==========================================================================
pre_$(PROJ_NAME):
ifeq ($(BUILD_TYPE),$(filter $(BUILD_TYPE),debug release))
ifeq ($(PLATFORM),$(filter $(PLATFORM),arm x86))
	$(ECHO) "Building $(PROJ_NAME) ($(BUILD_TYPE)/$(PLATFORM))..."
else
	$(error Invalid platform (arm/x86) specified!)
endif
else
	$(error Invalid build type (debug/release) specified!)
endif
	$(MKDIR) -p $(BUILD_DIR)

$(PROJ_NAME).a: $(PROJ_OBJS)
	$(foreach PROJ_OBJ_DIR, $(PROJ_OBJ_DIRS), $(CP) -u $(PROJ_OBJ_DIR)/*.o $(BUILD_DIR))
	$(ECHO) "    AR  $(PROJ_OBJS)"
	$(AR) $(ARFLAGS) $(BUILD_DIR)/$(PROJ_NAME).a $(addprefix $(BUILD_DIR)/, $(PROJ_OBJS))

%.asm: %.c
	$(ECHO) "    CC  $<"
	$(CC) $(CPPFLAGS) $(CFLAGS) $(STD_INCS) $(PLTF_INCS) $(PROJ_INCS) -MD $(BUILD_DIR)/$*.d \
	-MQ $(BUILD_DIR)/$*.o $(CURDIR)/$< -o $(BUILD_DIR)/$@
<<<<<<< HEAD
=======

%.asm: %.cpp
	$(ECHO) "    CPP $<"
	$(CPP) $(CPPFLAGS) $(CXXFLAGS) $(STD_INCS) $(PLTF_INCS) $(PROJ_INCS) -MD $(BUILD_DIR)/$*.d \
	-MQ $(BUILD_DIR)/$*.o $(CURDIR)/$< -o $(BUILD_DIR)/$@
>>>>>>> bbf89bcb444b6701919e623661389eab9898aea4

%.asm: %.s
	$(ECHO) "    CC  $<"
	$(CC) $(CPPFLAGS) $(SFLAGS) -MD $(BUILD_DIR)/$*.d -MQ $(BUILD_DIR)/$*.o $(CURDIR)/$< -o $(BUILD_DIR)/$@

%.o: %.asm
	$(ECHO) "    AS  $(BUILD_DIR)/$<"
	$(AS) $(ASFLAGS) $(BUILD_DIR)/$< -o $(BUILD_DIR)/$@

%.o : %.c

%.o : %.cpp

%.o : %.s

#============================== Clean Targets ==========================================================================
clean:
	$(ECHO) "Cleaning $(PROJ_NAME)...\c"
	$(eval PLATFORM := *)
	$(eval BUILD_TYPE := *)
	$(RM) $(BUILD_DIR)/*.asm
	$(RM) $(BUILD_DIR)/*.o
	$(RM) $(BUILD_DIR)/*.d
	$(RM) $(BUILD_DIR)/*.a
	$(RM) $(BUILD_DIR)/*.elf
	$(RM) $(BUILD_DIR)/*.hex
	$(RM) $(BUILD_DIR)/*.bin
	$(RM) $(BUILD_DIR)/*.srec
	$(RM) $(BUILD_DIR)/*.prepatch
	$(RM) $(BUILD_DIR)/*.ld
	$(RM) $(BUILD_DIR)/*.map
	$(ECHO) " Done"

#============================== Phony Targets ==========================================================================
.PHONY: pre_$(PROJ_NAME) clean
