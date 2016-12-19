SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

PAJE.a: $(OBJ)
	@ar rcs $@ $(OBJ)
	@echo "    	generated	PAJE.a 	File"
	@mv PAJE.a $(OBJ_DIR)/
	@echo "    	PAJE.a move to $(OBJ_DIR)"

Reader_MainTrace.o: Reader_MainTrace.cpp
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