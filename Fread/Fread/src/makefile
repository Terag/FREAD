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
HEADER =
SRC = $(HEADER:.hpp=.cpp) main.cpp
OBJ = $(SRC:.cpp=.o)

##Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all : $(EXEC)
	
main.o : main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
	
$(EXEC) : $(OBJ)
	$(CXX) -o $(EXEC) $(OBJ) $(LIBS)
	rm $(OBJ)

clean :
	rm $(OBJ) $(EXEC)	

install :
	cp $(EXEC) $(INSTALL_DIR)/$(EXEC)
	
uninstall :
	rm -f $(INSTALL_DIR)