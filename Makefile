
# Project name
PROJECT_NAME := primes

# Compiler
CXX := g++

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin
INT_DIR := int

# Files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
HEADER_FILES := $(wildcard $(INCLUDE_DIR)/*.h)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(INT_DIR)/%.o,$(SRC_FILES))
BIN := $(BIN_DIR)/$(PROJECT_NAME)

# Compilation flags
CXXFLAGS := -std=c++11 -I $(INCLUDE_DIR) -Wall

# Linking flags
LDFLAGS :=

# Targets and rules
all: $(BIN)

$(BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(INT_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER_FILES)
	@mkdir -p $(INT_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf $(BIN_DIR) $(INT_DIR)

.PHONY: all clean
