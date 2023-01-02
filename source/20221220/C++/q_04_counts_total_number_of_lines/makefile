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
  _ignore_obj/dir_info_extraction/dir_info.cc.o \
  _ignore_obj/line_counter/line_counter.cc.o \
  _ignore_obj/line_counter/line_counter__with_OpenMP.cc.o \
  _ignore_obj/line_counter/line_counter__with_threads.cc.o \
  _ignore_obj/tree_builder/tree_builder.cc.o

obj_topdir := \
  _ignore_obj/./line_count_report__with_OpenMP.cc.o \
  _ignore_obj/./line_count_report__with_threads.cc.o \
  _ignore_obj/./list_directory_contents.cc.o

exe_topdir := \
  _ignore_obj/./line_count_report__with_OpenMP.cc.elf \
  _ignore_obj/./line_count_report__with_threads.cc.elf \
  _ignore_obj/./list_directory_contents.cc.elf

default : $(exe_topdir)  force_look

fromscratch : mkdirtarget  $(exe_topdir)  force_look

geninfo : mkdirtarget  force_look

mkdirtarget : force_look
	@mkdir -p  _ignore_obj  &&  cd _ignore_obj  &&  rm -rf ./*  && \
mkdir -p  dir_info_extraction  && \
mkdir -p  line_counter  && \
mkdir -p  tree_builder

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
-I./dir_info_extraction  -I./line_counter  -I./tree_builder \
$(dep_include) \
-c $< -o $@

_ignore_obj/dir_info_extraction/%.cc.o : ./dir_info_extraction/%.cc
	@echo ""
	@echo "Source : $<"
	@echo "Target : $@"
	@echo ""
	@echo "$(CXX)    $*.cc"
	@echo ""
	@$(CXX)  $(CXXFLAGS) \
-MP -MMD \
-MT '$@' \
-MF _ignore_obj/dir_info_extraction/$*.cc.d \
-I. \
-I./dir_info_extraction \
$(dep_include) \
-c $< -o $@

_ignore_obj/line_counter/%.cc.o : ./line_counter/%.cc
	@echo ""
	@echo "Source : $<"
	@echo "Target : $@"
	@echo ""
	@echo "$(CXX)    $*.cc"
	@echo ""
	@$(CXX)  $(CXXFLAGS) \
-MP -MMD \
-MT '$@' \
-MF _ignore_obj/line_counter/$*.cc.d \
-I. \
-I./line_counter \
$(dep_include) \
-c $< -o $@

_ignore_obj/tree_builder/%.cc.o : ./tree_builder/%.cc
	@echo ""
	@echo "Source : $<"
	@echo "Target : $@"
	@echo ""
	@echo "$(CXX)    $*.cc"
	@echo ""
	@$(CXX)  $(CXXFLAGS) \
-MP -MMD \
-MT '$@' \
-MF _ignore_obj/tree_builder/$*.cc.d \
-I. \
-I./tree_builder \
$(dep_include) \
-c $< -o $@

-include $(wildcard _ignore_obj/./*.cc.d)
-include $(wildcard _ignore_obj/dir_info_extraction/*.cc.d)
-include $(wildcard _ignore_obj/line_counter/*.cc.d)
-include $(wildcard _ignore_obj/tree_builder/*.cc.d)

clean : force_look
	@rm -rf ./_ignore_obj

.SECONDARY : $(obj_topdir)  $(obj_subdir)

.NOTPARALLEL :

run__line_count_report__with_OpenMP.cc.elf : force_look
	@_ignore_obj/./line_count_report__with_OpenMP.cc.elf

ldd__line_count_report__with_OpenMP.cc.elf : force_look
	@ldd _ignore_obj/./line_count_report__with_OpenMP.cc.elf

run__line_count_report__with_threads.cc.elf : force_look
	@_ignore_obj/./line_count_report__with_threads.cc.elf

ldd__line_count_report__with_threads.cc.elf : force_look
	@ldd _ignore_obj/./line_count_report__with_threads.cc.elf

run__list_directory_contents.cc.elf : force_look
	@_ignore_obj/./list_directory_contents.cc.elf

ldd__list_directory_contents.cc.elf : force_look
	@ldd _ignore_obj/./list_directory_contents.cc.elf

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
.PHONY : run__line_count_report__with_OpenMP.cc.elf
.PHONY : ldd__line_count_report__with_OpenMP.cc.elf
.PHONY : run__line_count_report__with_threads.cc.elf
.PHONY : ldd__line_count_report__with_threads.cc.elf
.PHONY : run__list_directory_contents.cc.elf
.PHONY : ldd__list_directory_contents.cc.elf