SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

PAJE.a: $(OBJ)
	@ar rcs $@ $(OBJ)
	@echo "    	generated	PAJE.a 	File"
	@mv PAJE.a $(OBJ_DIR)/
	@echo "    	PAJE.a move to $(OBJ_DIR)"

paje_typedefs.o: paje_typedefs.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

paje_interface.o: paje_interface.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"
	
Reader_MainTrace.o: Reader_MainTrace.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

Container_Reader.o: Container_Reader.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

## Quand vous rajoutez un fichier, suivre le même format que ci dessous pour chaque fichier :
##Cible: dépendances
##	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
##	@echo "    	CXX        $@"

clean:
	@$(RM) -f $(OBJ)
	@$(RM) -f *.expand
	@echo "    Remove Objects:   $(OBJ)"