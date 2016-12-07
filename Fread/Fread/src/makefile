## -*- Makefile -*-
##
## User: Victor Rouquette
## Time: Nov 30, 2016 12:39:11 PM

##Compilation informations
CXX = g++
DEBUG = yes
ifeq ($(DEBUG),yes)
    CXXFLAGS = -W -Wall -pedantic -g
else
    CXXFLAGS = -W -Wall -pedantic
endif
EXEC = Fread
INSTALL_DIR = ../..

##Files
INCLUDEDIRS = -I../include
HEADER = Reader_MainTrace.hpp
SRC = $(HEADER:.hpp=.cpp) main.cpp
OBJ = $(SRC:.cpp=.o)

##Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all : $(EXEC)
	
main.o : main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -o $@ -c $<
	
Reader_MainTrace.o : Reader_MainTrace.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -o $@ -c $<
	
$(EXEC) : $(OBJ)
	$(CXX) -o $(EXEC) $(OBJ) $(LIBS)
	rm $(OBJ)

clean :
	rm $(EXEC)
	rm $(OBJ)

install :
	cp $(EXEC) $(INSTALL_DIR)/$(EXEC)
	
uninstall :
	rm -f $(INSTALL_DIR)