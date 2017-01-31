SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

PAJE.so: $(OBJ)
	@g++ -o $@ -shared -fPIC $(OBJ)
	@echo "    	generated	PAJE.so	File"
	@mv PAJE.so $(OBJ_DIR)/
	@echo "    	PAJE.so move to $(OBJ_DIR)"

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
	
Pattern_Reader.o: Pattern_Reader.cpp
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