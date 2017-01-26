SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
LIB_NAME = render

render.so: $(OBJ)
	@g++ -o $@ -shared -fPIC $(OBJ)
	@echo "    	generated	render.so 	File"
	@mv $@ $(OBJ_DIR)/
	@echo "    	render.so move to $(OBJ_DIR)"
	
FBezierCurve.o: FBezierCurve.cpp
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