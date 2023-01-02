
########################################
# Intermediary Makefile                #
#                                      #
# Communicates call to subdirectories. #
########################################

include info_local.mk

default : force_look
	@for d in $(dnames_subdir); do \
	  make  --directory=$$d  ||  exit 1; \
	done

geninfo : force_look
	@for d in $(dnames_subdir); do \
	  make  --directory=$$d  geninfo  ||  exit 1; \
	done

clean : force_look
	@for d in $(dnames_subdir); do \
	  make  --directory=$$d  clean  ||  exit 1; \
	done

help : force_look
	@echo ""
	@echo "IMPORTANT NOTE"
	@echo ""
	@echo "  If the projects below have not been tended to yet, and"
	@echo "  if they are all rid of the relevant binaries, please call"
	@echo "  'make geninfo' before calling 'make'."
	@echo ""
	@echo "RECIPES"
	@echo ""
	@echo "  default : builds all projects below"
	@echo "  geninfo : creates folders for binaries in each project below"
	@echo "  clean   : removes folders for binaries in each project below"
	@echo "  help    : prints help information as in this recipe"

force_look :
	@true;

.PHONY : default
.PHONY : geninfo
.PHONY : clean
.PHONY : help
.PHONY : force_look
