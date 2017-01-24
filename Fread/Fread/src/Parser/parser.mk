SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

parser.a: $(OBJ)
	@ar rcs $@ $(OBJ)
	@echo "    	generated	parser.a 	File"
	@mv parser.a $(OBJ_DIR)/
	@echo "    	parser.a move to $(OBJ_DIR)"

statesConfig.o: statesConfig.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $^
	@echo "    	CXX        $@"

parser.o: parser.cpp
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