################################################
# FILE TO ENTER CUSTOM SETTINGS ON THE CHOICES #
# OF EXTERNAL LIBRARY UTILIZATION.             #
#                                              #
# TARGETS : MULTIPLE STAND-ALONE EXECUTABLES   #
################################################

CC     := gcc
CXX    := g++

MAKE    := make

CFLAGS     := -fPIC -fopenmp -Wall -Wwrite-strings -Wno-strict-aliasing -Wno-unknown-pragmas -g3 -O0
CXXFLAGS   := $(CFLAGS) -std=c++11

LDFLAGS    := -fPIC -fopenmp -Wall -Wwrite-strings -Wno-strict-aliasing -Wno-unknown-pragmas -g3 -O0
LDCXXFLAGS := $(LDFLAGS) -std=c++11

temp_lib := \
	-lgomp  \
	-lgfortran  \
	-lX11  \
	-lpthread  \
	-lquadmath  \
	-lstdc++  \
	-lgcc_s  \
	-ldl  \
	-lrt  \
	-lm

dep_include :=
dep_link := $(temp_lib)
path_link :=

flag_use_patchelf := 0
