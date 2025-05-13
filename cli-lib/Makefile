# Nome do projeto
PROJ_NAME = CyberTerminalHacker

# Compilador e flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
LDFLAGS = 

# Diretórios
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin


SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))


all: setup $(BIN_DIR)/$(PROJ_NAME)


setup:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)


$(BIN_DIR)/$(PROJ_NAME): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR)


run: all
	$(BIN_DIR)/$(PROJ_NAME)

.PHONY: all clean run setup
