SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
LIB_NAME = render

render.a: $(OBJ)
	@ar rcs $@ $(OBJ)
	@echo "    	generated	render.a 	File"
	@mv render.a $(OBJ_DIR)/
	@echo "    	render.a move to $(OBJ_DIR)"

## Quand vous rajoutez un fichier, suivre le même format que ci dessous pour chaque fichier :
##Cible: dépendances
##	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
##	@echo "    	CXX        $@"

clean:
	@$(RM) -f $(OBJ)
	@$(RM) -f *.expand
	@echo "    Remove Objects:   $(OBJ)"