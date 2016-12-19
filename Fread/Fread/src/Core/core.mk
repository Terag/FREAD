SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

core.a: $(OBJ)
	@ar rcs $@ $(OBJ)
	@echo "    	generated	core.a 	File"
	@mv core.a $(OBJ_DIR)/
	@echo "    	core.a move to $(OBJ_DIR)"

## Quand vous rajoutez un fichier, suivre le même format que ci dessous pour chaque fichier :
##Cible: dépendances
##	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
##	@echo "    	CXX        $@"

clean:
	@$(RM) -f $(OBJ)
	@$(RM) -f *.expand
	@echo "    Remove Objects:   $(OBJ)"