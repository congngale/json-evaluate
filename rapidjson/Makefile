#
# Copyright (c) 2022, NovaInTechs. All rights reserved.
#
# This application used C++ version 11
#

# app name
PROGRAM = rapidjson-app

# MAC OS temp files
MAC_TEMP_FILES = $(shell find ./ -type f -name '._*')

# object files
OBJECT_FILES = $(shell find ./ -type f -name '*.o')

# collect all .cc source files
SOURCES = main.cc

# object files
OBJECTS = $(patsubst %.cc,%.o,$(SOURCES))

# include inc folders
INCLUDE_DIR = inc

# json-c lib dir
RAPID_JSON_LIB_DIR = rapidjson/include

# compile flags
COMPILE_FLAGS = -O2 -std=c++11 -Wall -Wextra -Werror

# include -I
CPPFLAGS = -I$(RAPID_JSON_LIB_DIR)

.PHONY: $(PROGRAM) lib clean

all: lib $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o $(PROGRAM)

clean:
	@- $(RM) $(PROGRAM)
	@- $(RM) $(OBJECT_FILES)
	@- $(RM) $(MAC_TEMP_FILES)
