#
# Copyright (c) 2022, NovaInTechs. All rights reserved.
#
# This application used C++ version 11
#

# app name
PROGRAM = json-c-app

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
JSON_C_LIB_DIR = json-c

# compile flags
COMPILE_FLAGS = -O2 -std=c++11 -Wall -Wextra -Werror

# link flags
LDFLAGS = -L./json-c/build -ljson-c-test

# include -I
CPPFLAGS = -I$(JSON_C_LIB_DIR)

.PHONY: $(PROGRAM) lib clean

all: lib $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o $(PROGRAM) $(LDFLAGS)

lib:
	rm -rf ./json-c/build 
	mkdir ./json-c/build
	cd ./json-c/build && cmake .. && make && cd -
	cp ./json-c/build/json.h ./json-c
	cp ./json-c/build/json_config.h ./json-c
	mv ./json-c/build/libjson-c.so ./json-c/build/libjson-c-test.so 

clean:
	@- $(RM) $(PROGRAM)
	@- $(RM) $(OBJECT_FILES)
	@- $(RM) $(MAC_TEMP_FILES)
