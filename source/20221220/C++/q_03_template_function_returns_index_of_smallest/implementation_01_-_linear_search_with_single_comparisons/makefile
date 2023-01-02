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
  

obj_topdir := \
  _ignore_obj/./test_smallest__storing_index_only.cc.o \
  _ignore_obj/./test_smallest__tuple.cc.o \
  _ignore_obj/./test_smallest__tuple_with_lambda_expression.cc.o

exe_topdir := \
  _ignore_obj/./test_smallest__storing_index_only.cc.elf \
  _ignore_obj/./test_smallest__tuple.cc.elf \
  _ignore_obj/./test_smallest__tuple_with_lambda_expression.cc.elf

default : $(exe_topdir)  force_look

fromscratch : mkdirtarget  $(exe_topdir)  force_look

geninfo : mkdirtarget  force_look

mkdirtarget : force_look
	@mkdir -p  _ignore_obj  &&  cd _ignore_obj  &&  rm -rf ./* 

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
 \
$(dep_include) \
-c $< -o $@

-include $(wildcard _ignore_obj/./*.cc.d)

clean : force_look
	@rm -rf ./_ignore_obj

.SECONDARY : $(obj_topdir)  $(obj_subdir)

.NOTPARALLEL :

run__test_smallest__storing_index_only.cc.elf : force_look
	@_ignore_obj/./test_smallest__storing_index_only.cc.elf

ldd__test_smallest__storing_index_only.cc.elf : force_look
	@ldd _ignore_obj/./test_smallest__storing_index_only.cc.elf

run__test_smallest__tuple.cc.elf : force_look
	@_ignore_obj/./test_smallest__tuple.cc.elf

ldd__test_smallest__tuple.cc.elf : force_look
	@ldd _ignore_obj/./test_smallest__tuple.cc.elf

run__test_smallest__tuple_with_lambda_expression.cc.elf : force_look
	@_ignore_obj/./test_smallest__tuple_with_lambda_expression.cc.elf

ldd__test_smallest__tuple_with_lambda_expression.cc.elf : force_look
	@ldd _ignore_obj/./test_smallest__tuple_with_lambda_expression.cc.elf

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
.PHONY : run__test_smallest__storing_index_only.cc.elf
.PHONY : ldd__test_smallest__storing_index_only.cc.elf
.PHONY : run__test_smallest__tuple.cc.elf
.PHONY : ldd__test_smallest__tuple.cc.elf
.PHONY : run__test_smallest__tuple_with_lambda_expression.cc.elf
.PHONY : ldd__test_smallest__tuple_with_lambda_expression.cc.elf