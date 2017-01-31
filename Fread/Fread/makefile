MAKEFILE_PATH = $(abspath $(lastword $(MAKEFILE_LIST)))
MAKE_DIR = $(MAKEFILE_PATH:/makefile=)

ROOT_DIR    := $(MAKE_DIR) 
RENDER_DIR  := $(MAKE_DIR)/src/Render
CORE_DIR    := $(MAKE_DIR)/src/Core
PARSER_DIR  := $(MAKE_DIR)/src/Parser
OBJ_DIR	    := $(MAKE_DIR)/obj

INCLUDE_DIR := -I$(MAKE_DIR)/include

CXX = g++

EXEC = Fread
DEBUG = yes
PARSER = PAJE
ifeq ($(DEBUG),yes)
    CXXFLAGS = -std=c++11 -W -Wall -pedantic -fPIC -g
else
    CXXFLAGS = -std=c++11 -W -Wall -pedantic -fPIC
endif

LIBS := -lsfml-graphics -lsfml-window -lsfml-system -pthread


export MAKE_DIR CXX CXXFLAGS LIBS INCLUDE_DIR EXEC OBJ_DIR EXEC PARSER

all:
	@$(MAKE) -C $(RENDER_DIR) -f render.mk
##l	@$(MAKE) -C $(CORE_DIR) -f core.mk
	@$(MAKE) -C $(PARSER_DIR) -f parser.mk
	@$(MAKE) -C $(PARSER_DIR)/$(PARSER) -f $(PARSER).mk
	@$(MAKE) -C $(MAKE_DIR)/src -f fread.mk

.PHONY: clean
clean:
	rm -f $(MAKE_DIR)/src/Fread
	@$(MAKE) -C $(RENDER_DIR) -f render.mk clean
	@$(MAKE) -C $(CORE_DIR) -f core.mk clean
	@$(MAKE) -C $(PARSER_DIR) -f parser.mk clean
	@$(MAKE) -C $(PARSER_DIR)/$(PARSER) -f $(PARSER).mk clean
	@$(MAKE) -C $(MAKE_DIR)/src -f fread.mk clean