SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

core.so: $(OBJ)
	@g++ -o $@ -shared -fPIC $(OBJ)
	@echo "    	generated	core.so	File"
	@mv core.so $(OBJ_DIR)/
	@echo "    	core.so move to $(OBJ_DIR)"

FCore.o: FCore.cpp FMap.hpp FMap.tpp FQueue.hpp FQueue.tpp FMessages.hpp FMessages.tpp
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