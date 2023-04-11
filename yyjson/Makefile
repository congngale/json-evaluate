#
# Copyright (c) 2022, NovaInTechs. All rights reserved.
#
# This application used C++ version 11
#

# app name
PROGRAM = yyjson-app

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

# yyjson lib dir
YYJSON_LIB_DIR = yyjson/src

# compile flags
COMPILE_FLAGS = -O2 -std=c++11 -Wall -Wextra -Werror

# link flags
LDFLAGS = -L./yyjson/build -lyyjson

# include -I
CPPFLAGS = -I$(YYJSON_LIB_DIR)

.PHONY: $(PROGRAM) lib clean

all: lib $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o $(PROGRAM) $(LDFLAGS) $(COMPILE_FLAGS)

lib:
	rm -rf ./yyjson/build 
	mkdir ./yyjson/build
	cd ./yyjson/build && cmake .. && make && cd -

clean:
	@- $(RM) $(PROGRAM)
	@- $(RM) $(OBJECT_FILES)
	@- $(RM) $(MAC_TEMP_FILES)
