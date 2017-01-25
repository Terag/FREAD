SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

FREAD_LIB = $(OBJ_DIR)/render.a $(OBJ_DIR)/core.a $(OBJ_DIR)/parser.a $(OBJ_DIR)/$(PARSER).a
 
$(EXEC): $(OBJ) $(FREAD_LIB)
	@$(CXX) -o $(EXEC) $(OBJ) $(FREAD_LIB) $(LIBS) $(FREAD_LIB)
	@echo "    Generate Program $(notdir $(PROG)) from $^"

main.o: main.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $<
	@echo "   	CXX      $@"

FColor.o: FColor.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $<
	@echo "    	CXX      $@"

.PHONY: clean
clean:
	@$(RM) -f $(OBJ)
	@echo "    Remove Objects:   $(OBJ)"