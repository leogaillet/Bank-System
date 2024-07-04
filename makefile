# Variables
CC = gcc
CFLAGS = -Wall -Werror -Iinclude
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
TARGET = $(BIN_DIR)/mon_projet

# Trouver tous les fichiers .c dans SRC_DIR
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Remplacer .c par .o pour créer une liste de fichiers objet
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Règle pour créer les fichiers objet
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Nettoyer les fichiers compilés
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Nettoyer plus profondément en incluant les fichiers générés
distclean: clean
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Règle pour exécuter les tests
test: $(TARGET)
	@./tests/run_tests.sh

# Règle pour afficher de l'aide
help:
	@echo "Les cibles disponibles sont :"
	@echo "  all       : Compile le projet"
	@echo "  clean     : Supprime les fichiers objets et binaires"
	@echo "  distclean : Supprime les fichiers objets, binaires, et autres fichiers générés"
	@echo "  test      : Exécute les tests"
	@echo "  help      : Affiche cette aide"

# Indiquer à make que ces règles ne sont pas des fichiers
.PHONY: all clean distclean test help
