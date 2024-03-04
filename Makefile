ifdef DIR
EXEC = $(DIR)/run.run
BUILD_DIR = $(DIR)/build
else
EXEC   = run.run
BUILD_DIR = build
endif

SRC_DIR = src

###################
#determine SYSTYPE#
###################

$(info Build configuration:)
$(info EXEC: $(EXEC))
$(info )

##########################
#define available Systems#
##########################

NCC       =  g++ -g -O3 -Wall -std=c++17
CPP       =  g++ -g -O3 -Wall -std=c++17
# GSL_INCL   = -I/opt/local/include
# GSL_LIBS   = -L/opt/local/lib
# HDF5_INCL  = -I/usr/lib/x86_64-linux-gnu/hdf5/serial/include
# HDF5_LIBS  = -L/usr/lib/x86_64-linux-gnu/hdf5/serial/
# FFTW_INCL  = -I/opt/local/include
# FFTW_LIBS  = -L/opt/local/lib

ifndef LINKER
LINKER = $(CPP)
endif


##########################################
#determine the needed object/header files#
##########################################
SUBDIRS += .


OBJS    += minihydro.o Boundary.o BoundaryWind.o BoundaryWindLinearisedEuler.o BoundaryWindPassiveScalar.o BoundaryZeroGradient.o Equations.o EquationsEuler.o EquationsEulerPassiveScalar.o EquationsLinearisedEuler.o Grid.o Grid1D.o GridRadial.o InitialData.o InitialDataHomogeneous.o InitialDataHomogeneousLinearisedEuler.o InitialDataHomogeneousPassiveScalar.o InitialDataPowerLaw.o InitialDataPowerLawPassiveScalar.o InitialDataSodShock.o Output.o OutputEuler.o OutputEulerPassiveScalar.o OutputLinearisedEuler.o RiemannSolver.o RiemannSolverHLLC.o RiemannSolverRusanov.o ShockFinder.o ShockFinderEuler.o SimulationConfig.o
INCL    +=             Boundary.h BoundaryWind.h BoundaryWindLinearisedEuler.h BoundaryWindPassiveScalar.h BoundaryZeroGradient.h Equations.h EquationsEuler.h EquationsEulerPassiveScalar.h EquationsLinearisedEuler.h Grid.h Grid1D.h GridRadial.h InitialData.h InitialDataHomogeneous.h InitialDataHomogeneousLinearisedEuler.h InitialDataHomogeneousPassiveScalar.h InitialDataPowerLaw.h InitialDataPowerLawPassiveScalar.h InitialDataSodShock.h Output.h OutputEuler.h OutputEulerPassiveScalar.h OutputLinearisedEuler.h RiemannSolver.h RiemannSolverHLLC.h RiemannSolverRusanov.h ShockFinder.h ShockFinderEuler.h SimulationConfig.h

################################
#determine the needed libraries#
################################

# GSL_LIBS   += -lgsl -lgslcblas
# HDF5_LIBS  += -lhdf5 -lz
MATH_LIBS  = -lm

##########################
#combine compiler options#
##########################

CFLAGS = $(LANGUAGE) $(OPTIMIZE) $(OPT) $(HDF5_INCL) $(GSL_INCL) $(MPI_INCL) $(FFTW_INCL) -I$(BUILD_DIR) -I$(SRC_DIR)

LIBS = $(MATH_LIBS) $(HDF5_LIBS) $(GSL_LIBS) $(MPI_LIBS) $(FFTW_LIBS)


SUBDIRS := $(addprefix $(BUILD_DIR)/,$(SUBDIRS))
OBJS := $(addprefix $(BUILD_DIR)/,$(OBJS)) 
INCL := $(addprefix $(SRC_DIR)/,$(INCL)) 


################
#create subdirs#
################
RESULT := $(shell mkdir -p $(SUBDIRS)  )

###########################################
#create info file for command line options#
###########################################

#############
#build rules#
#############


all:  build

build: $(EXEC)

$(EXEC): $(OBJS)
	$(LINKER) $(OPTIMIZE)  $(OBJS) $(LIBS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC) core*

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp  $(INCL)  $(MAKEFILES)
	$(CPP) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc  $(INCL)  $(MAKEFILES)
	$(CPP) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cu   $(INCL)  $(MAKEFILES)
	$(NCC) $(CFLAGS) -c  $< -o $@

$(BUILD_DIR)/compile_time_info.o: $(BUILD_DIR)/compile_time_info.cc $(MAKEFILES)
	$(CPP) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/minihydro.o: $(SRC_DIR)/minihydro.cpp $(INCL) $(MAKEFILES)
	$(CPP) $(CFLAGS) -c $< -o $@
