SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

FREAD_LIB = $(OBJ_DIR)/render.so $(OBJ_DIR)/parser.so $(OBJ_DIR)/$(PARSER).so
 
$(EXEC): $(OBJ) $(FREAD_LIB)
	$(CXX) -o $(EXEC) $(OBJ) $(FREAD_LIB) $(LIBS)
	@echo "    Generate Program $(notdir $(PROG)) from $^"

main.o: main.cpp FQueue.hpp FQueue.tpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $<
	@echo "   	CXX      $@"

FColor.o: FColor.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $<
	@echo "    	CXX      $@"

FPattern.o: FPattern.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $<
	@echo "    	CXX      $@"

FOccurrence.o: FOccurrence.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $<
	@echo "    	CXX      $@"

FContainer.o: FContainer.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $<
	@echo "    	CXX      $@"

FThread_Guard.o: FThread_Guard.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $<
	@echo "    	CXX      $@"

.PHONY: clean
clean:
	@$(RM) -f $(OBJ)
	@echo "    Remove Objects:   $(OBJ)"