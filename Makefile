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

SRCS    := $(notdir $(wildcard $(SRC_DIR)/*.cpp))
OBJS    += $(SRCS:.cpp=.o)
INCL    += $(notdir $(wildcard $(SRC_DIR)/*.h))

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

$(BUILD_DIR)/shockr.o: $(SRC_DIR)/shockr.cpp $(INCL) $(MAKEFILES)
	$(CPP) $(CFLAGS) -c $< -o $@
