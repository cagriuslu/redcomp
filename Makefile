# redmake-0.2 Individual Project Makefile

# Build Options
override LIBRARY_NAME          = redcomp
override COMMON_COMPILER_FLAGS = -g -Wall -Wextra
override C_COMPILER_FLAGS      = -std=c11
override CPP_COMPILER_FLAGS    = -std=c++11
override INCLUDE_DIRECTORIES   =
override LINKER_FLAGS          =
override REDMAKE_DEPENDENCIES  =
override LINK_TYPE             = dynamic

##################
## Call redmake ##
##################

MAKE = make
REDMAKE_DIRECTORY = ../redmake/Makefile
COMMAND = $(MAKE) -f $(REDMAKE_DIRECTORY) -C . $@ LIBRARY_NAME="$(LIBRARY_NAME)" COMMON_COMPILER_FLAGS="$(COMMON_COMPILER_FLAGS)" C_COMPILER_FLAGS="$(C_COMPILER_FLAGS)" CPP_COMPILER_FLAGS="$(CPP_COMPILER_FLAGS)" INCLUDE_DIRECTORIES="$(INCLUDE_DIRECTORIES)" LINKER_FLAGS="$(LINKER_FLAGS)" REDMAKE_DEPENDENCIES="$(REDMAKE_DEPENDENCIES)" LINK_TYPE="$(LINK_TYPE)"

all:
	$(COMMAND)
%:
	$(COMMAND)
