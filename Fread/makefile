## -*- Makefile -*-
##
## User: Victor Rouquette
## Time: Nov 30, 2016 12:39:11 PM
##
##Not an essential makefile for the moment

SUBDIRS = $(dir $(wildcard */makefile) $(wildcard */*/makefile) $(wildcard */*/*/makefile))
EXEC = Fread.out
EXEC_DIR = ./Fread/src

all : $(EXEC)

$(EXEC):$(EXEC_DIR)/$(EXEC)
	@(cd $(SUBDIRS) && $(MAKE) install)

$(EXEC_DIR)/$(EXEC):
	@(cd $(SUBDIRS) && $(MAKE))

clean : 
	@(cd $(SUBDIRS) && $(MAKE) $@)
	rm $(EXEC)