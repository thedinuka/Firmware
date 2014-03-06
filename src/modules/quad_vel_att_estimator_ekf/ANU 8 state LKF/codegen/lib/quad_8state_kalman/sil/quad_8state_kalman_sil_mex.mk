MATLAB_ROOT = /usr/local/matlab2013b
MAKEFILE = quad_8state_kalman_sil_mex.mk

include quad_8state_kalman_sil_mex.mki


SRC_FILES =  \
	quad_8state_kalman_sil.c \
	_coder_quad_8state_kalman_info.c

MEX_FILE_NAME_WO_EXT = quad_8state_kalman_sil
MEX_FILE_NAME = $(MEX_FILE_NAME_WO_EXT).mexa64
TARGET = $(MEX_FILE_NAME)

SYS_LIBS = 


#
#====================================================================
# gmake makefile fragment for building MEX functions using Unix
# Copyright 2007-2013 The MathWorks, Inc.
#====================================================================
#
OBJEXT = o
.SUFFIXES: .$(OBJEXT)

OBJLISTC = $(SRC_FILES:.c=.$(OBJEXT))
OBJLISTCPP  = $(OBJLISTC:.cpp=.$(OBJEXT))
OBJLIST  = $(OBJLISTCPP:.cu=.$(OBJEXT))

target: $(TARGET)

ML_INCLUDES = -I "$(MATLAB_ROOT)/simulink/include"
ML_INCLUDES+= -I "$(MATLAB_ROOT)/toolbox/shared/simtargets"
SYS_INCLUDE = $(ML_INCLUDES)

# Additional includes

SYS_INCLUDE += -I "/home/dmabeywa/Dropbox/Quadrotor\ State\ Estimation/ANU\ 8\ state\ EKF/codegen/lib/quad_8state_kalman/interface"
SYS_INCLUDE += -I "../."
SYS_INCLUDE += -I "../interface"
SYS_INCLUDE += -I "$(MATLAB_ROOT)/rtw/c/src/rtiostream/utils"
SYS_INCLUDE += -I "$(MATLAB_ROOT)/extern/include"
SYS_INCLUDE += -I "."

EML_LIBS = -lemlrt -lcovrt -lut -lmwmathutil -lmwblas 
SYS_LIBS += $(CLIBS) $(EML_LIBS)


EXPORTFILE = $(MEX_FILE_NAME_WO_EXT)_mex.map
ifeq ($(Arch),maci)
  EXPORTOPT = -Wl,-exported_symbols_list,$(EXPORTFILE)
  COMP_FLAGS = -c $(CFLAGS) -DMX_COMPAT_32
  CXX_FLAGS = -c $(CXXFLAGS) -DMX_COMPAT_32
  LINK_FLAGS = $(filter-out %mexFunction.map, $(LDFLAGS))
else ifeq ($(Arch),maci64)
  EXPORTOPT = -Wl,-exported_symbols_list,$(EXPORTFILE)
  COMP_FLAGS = -c $(CFLAGS) -DMX_COMPAT_32
  CXX_FLAGS = -c $(CXXFLAGS) -DMX_COMPAT_32
  LINK_FLAGS = $(filter-out %mexFunction.map, $(LDFLAGS))
else
  EXPORTOPT = -Wl,--version-script,$(EXPORTFILE)
  COMP_FLAGS = -c $(CFLAGS) -DMX_COMPAT_32 $(OMPFLAGS)
  CXX_FLAGS = -c $(CXXFLAGS) -DMX_COMPAT_32 $(OMPFLAGS)
  LINK_FLAGS = $(filter-out %mexFunction.map, $(LDFLAGS)) 
endif
LINK_FLAGS += $(OMPLINKFLAGS)
ifeq ($(Arch),maci)
  LINK_FLAGS += -L$(MATLAB_ROOT)/sys/os/maci
endif
ifeq ($(EMC_CONFIG),optim)
  ifeq ($(Arch),mac)
    COMP_FLAGS += $(CDEBUGFLAGS)
    CXX_FLAGS += $(CXXDEBUGFLAGS)
  else
    COMP_FLAGS += $(COPTIMFLAGS)
    CXX_FLAGS += $(CXXOPTIMFLAGS)
  endif
  LINK_FLAGS += $(LDOPTIMFLAGS)
else
  COMP_FLAGS += $(CDEBUGFLAGS)
  CXX_FLAGS += $(CXXDEBUGFLAGS)
  LINK_FLAGS += $(LDDEBUGFLAGS)
endif
LINK_FLAGS += -o $(TARGET)
LINK_FLAGS +=  -lfixedpoint -lmwrtiostreamutils

CCFLAGS =  -DMATLAB_MEX_FILE $(COMP_FLAGS) $(USER_INCLUDE) $(SYS_INCLUDE)
CPPFLAGS =  -DMATLAB_MEX_FILE  $(CXX_FLAGS) $(USER_INCLUDE) $(SYS_INCLUDE)

%.$(OBJEXT) : %.c
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : %.cpp
	$(CXX) $(CPPFLAGS) "$<"

# Additional sources

%.$(OBJEXT) : /home/dmabeywa/Dropbox/Quadrotor\ State\ Estimation/ANU\ 8\ state\ EKF/codegen/lib/quad_8state_kalman/interface/%.c
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : /home/dmabeywa/Dropbox/Quadrotor\ State\ Estimation/ANU\ 8\ state\ EKF/codegen/lib/quad_8state_kalman/sil/%.c
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : /home/dmabeywa/Dropbox/Quadrotor\ State\ Estimation/ANU\ 8\ state\ EKF/%.c
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : .././%.c
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : ../interface/%.c
	$(CC) $(CCFLAGS) "$<"



%.$(OBJEXT) : /home/dmabeywa/Dropbox/Quadrotor\ State\ Estimation/ANU\ 8\ state\ EKF/codegen/lib/quad_8state_kalman/interface/%.cu
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : /home/dmabeywa/Dropbox/Quadrotor\ State\ Estimation/ANU\ 8\ state\ EKF/codegen/lib/quad_8state_kalman/sil/%.cu
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : /home/dmabeywa/Dropbox/Quadrotor\ State\ Estimation/ANU\ 8\ state\ EKF/%.cu
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : .././%.cu
	$(CC) $(CCFLAGS) "$<"

%.$(OBJEXT) : ../interface/%.cu
	$(CC) $(CCFLAGS) "$<"



%.$(OBJEXT) : /home/dmabeywa/Dropbox/Quadrotor\ State\ Estimation/ANU\ 8\ state\ EKF/codegen/lib/quad_8state_kalman/interface/%.cpp
	$(CXX) $(CPPFLAGS) "$<"

%.$(OBJEXT) : /home/dmabeywa/Dropbox/Quadrotor\ State\ Estimation/ANU\ 8\ state\ EKF/codegen/lib/quad_8state_kalman/sil/%.cpp
	$(CXX) $(CPPFLAGS) "$<"

%.$(OBJEXT) : /home/dmabeywa/Dropbox/Quadrotor\ State\ Estimation/ANU\ 8\ state\ EKF/%.cpp
	$(CXX) $(CPPFLAGS) "$<"

%.$(OBJEXT) : .././%.cpp
	$(CXX) $(CPPFLAGS) "$<"

%.$(OBJEXT) : ../interface/%.cpp
	$(CXX) $(CPPFLAGS) "$<"



$(TARGET): $(OBJLIST) $(MAKEFILE)
	$(LD) $(EXPORTOPT) $(LINK_FLAGS) $(OBJLIST) $(SYS_LIBS)

#====================================================================

