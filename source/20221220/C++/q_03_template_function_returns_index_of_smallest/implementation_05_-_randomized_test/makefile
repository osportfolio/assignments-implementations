#################################################
# THIS IS AN AUTOMATICALLY GENERATED MAKEFILE.  #
# IT HAS BEEN CRAFTED BASED ON THE SOURCE CODE  #
# FILES AND DIRECTORY STRUCTURE PRESENT IN THE  #
# CURRENT PROJECT FAMILY FOLDER. IT IS BEST NOT #
# TO TAMPER WITH THIS MAKEFILE.                 #
#                                               #
# TARGETS : MULTIPLE STAND-ALONE EXECUTABLES    #
#################################################

include config.mk

obj_subdir := \
  _ignore_obj/randomization/prng_utilities.cc.o \
  _ignore_obj/testing_equipment/rng_engine_static.cc.o

obj_topdir := \
  _ignore_obj/./demo_calling_all_implementations.cc.o \
  _ignore_obj/./randomized_test.cc.o \
  _ignore_obj/./randomized_test__with_ccc.cc.o

exe_topdir := \
  _ignore_obj/./demo_calling_all_implementations.cc.elf \
  _ignore_obj/./randomized_test.cc.elf \
  _ignore_obj/./randomized_test__with_ccc.cc.elf

default : $(exe_topdir)  force_look

fromscratch : mkdirtarget  $(exe_topdir)  force_look

geninfo : mkdirtarget  force_look

mkdirtarget : force_look
	@mkdir -p  _ignore_obj  &&  cd _ignore_obj  &&  rm -rf ./*  && \
mkdir -p  implementations  && \
mkdir -p  randomization  && \
mkdir -p  testing_equipment

_ignore_obj/./%.elf : _ignore_obj/./%.o $(obj_subdir)
	@echo ""
	@echo "Object       : $<"
	@echo "Dependencies : $^"
	@echo "Target       : $@"
	@echo ""
	@echo "Linking    $*.elf"
	@echo ""
	@$(CXX) $(LDCXXFLAGS) -o $@ $< $(obj_subdir) $(dep_link)
	@if [[ $(flag_use_patchelf) -gt 0 ]]; then \
	   echo "patchelf   $*.elf" && \
	   patchelf --set-rpath "$(path_link)" $@ && \
	   echo ""; \
	fi

_ignore_obj/./%.cc.o : ././%.cc
	@echo ""
	@echo "Source : $<"
	@echo "Target : $@"
	@echo ""
	@echo "$(CXX)    $*.cc"
	@echo ""
	@$(CXX)  $(CXXFLAGS) \
-MP -MMD \
-MT '$@' \
-MF _ignore_obj/./$*.cc.d \
-I. \
-I./implementations  -I./randomization  -I./testing_equipment \
$(dep_include) \
-c $< -o $@

_ignore_obj/implementations/%.cc.o : ./implementations/%.cc
	@echo ""
	@echo "Source : $<"
	@echo "Target : $@"
	@echo ""
	@echo "$(CXX)    $*.cc"
	@echo ""
	@$(CXX)  $(CXXFLAGS) \
-MP -MMD \
-MT '$@' \
-MF _ignore_obj/implementations/$*.cc.d \
-I. \
-I./implementations \
$(dep_include) \
-c $< -o $@

_ignore_obj/randomization/%.cc.o : ./randomization/%.cc
	@echo ""
	@echo "Source : $<"
	@echo "Target : $@"
	@echo ""
	@echo "$(CXX)    $*.cc"
	@echo ""
	@$(CXX)  $(CXXFLAGS) \
-MP -MMD \
-MT '$@' \
-MF _ignore_obj/randomization/$*.cc.d \
-I. \
-I./randomization \
$(dep_include) \
-c $< -o $@

_ignore_obj/testing_equipment/%.cc.o : ./testing_equipment/%.cc
	@echo ""
	@echo "Source : $<"
	@echo "Target : $@"
	@echo ""
	@echo "$(CXX)    $*.cc"
	@echo ""
	@$(CXX)  $(CXXFLAGS) \
-MP -MMD \
-MT '$@' \
-MF _ignore_obj/testing_equipment/$*.cc.d \
-I. \
-I./testing_equipment \
$(dep_include) \
-c $< -o $@

-include $(wildcard _ignore_obj/./*.cc.d)
-include $(wildcard _ignore_obj/implementations/*.cc.d)
-include $(wildcard _ignore_obj/randomization/*.cc.d)
-include $(wildcard _ignore_obj/testing_equipment/*.cc.d)

clean : force_look
	@rm -rf ./_ignore_obj

.SECONDARY : $(obj_topdir)  $(obj_subdir)

.NOTPARALLEL :

run__demo_calling_all_implementations.cc.elf : force_look
	@_ignore_obj/./demo_calling_all_implementations.cc.elf

ldd__demo_calling_all_implementations.cc.elf : force_look
	@ldd _ignore_obj/./demo_calling_all_implementations.cc.elf

run__randomized_test.cc.elf : force_look
	@_ignore_obj/./randomized_test.cc.elf

ldd__randomized_test.cc.elf : force_look
	@ldd _ignore_obj/./randomized_test.cc.elf

run__randomized_test__with_ccc.cc.elf : force_look
	@_ignore_obj/./randomized_test__with_ccc.cc.elf

ldd__randomized_test__with_ccc.cc.elf : force_look
	@ldd _ignore_obj/./randomized_test__with_ccc.cc.elf

help : force_look
	@echo ""
	@echo "IMPORTANT NOTE"
	@echo ""
	@echo "  With a clean project family folder with only source"
	@echo "  codes and subdirectories with source codes, "geninfo""
	@echo "  should be called first. "fromscratch" is an alternative"
	@echo "  first call that also tries to build after creation of"
	@echo "  folders for binaries."
	@echo ""
	@echo "RECIPES"
	@echo ""
	@echo "  default     :  tries to build executables"
	@echo "  fromscratch :  creates folders for binaries and builds"
	@echo "  geninfo     :  creates folders for binaries only"
	@echo "  mkdirtarget :  equivalent to geninfo"
	@echo "  run__...    :  run executable, allows cycle through with tab"
	@echo "  ldd__...    :  ldd executable, allows cycle through with tab"
	@echo "  clean       :  removes folders with binaries"
	@echo "  help        :  prints this help information"

force_look :
	@true;

.PHONY : default
.PHONY : fromscratch
.PHONY : geninfo
.PHONY : mkdirtarget
.PHONY : clean
.PHONY : help
.PHONY : force_look
.PHONY : run__demo_calling_all_implementations.cc.elf
.PHONY : ldd__demo_calling_all_implementations.cc.elf
.PHONY : run__randomized_test.cc.elf
.PHONY : ldd__randomized_test.cc.elf
.PHONY : run__randomized_test__with_ccc.cc.elf
.PHONY : ldd__randomized_test__with_ccc.cc.elf