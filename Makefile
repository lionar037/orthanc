# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = -lcurl
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/app

# Encontrar automáticamente archivos fuente y objetos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Reglas
all: $(TARGET)

# Crear el ejecutable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Compilación completa: $@"

# Crear archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compilado: $< -> $@"

# Limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Archivos limpios."

# Limpieza completa (incluye respaldos)
clean-all: clean
	rm -f *~ */*~

# Phony targets
.PHONY: all clean clean-all
