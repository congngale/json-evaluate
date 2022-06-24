#
# Copyright (c) 2022, Cong Nga Le. All rights reserved.
#
# This is main Makefile to call other modules
#

.PHONY: all json-c rapidjson

all: json-c rapidjson

json-c:
	$(MAKE) -C json-c

rapidjson:
	$(MAKE) -C rapidjson

clean:
	$(MAKE) clean -C json-c
	$(MAKE) clean -C rapidjson
