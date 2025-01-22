# Variáveis de compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =

# Diretórios
SRC_DIR = src
CMD_DIR = $(SRC_DIR)/commands
UTIL_DIR = $(CMD_DIR)/util
NETWORK_DIR = $(SRC_DIR)/network
PARSER_DIR = $(SRC_DIR)/parser
BUILD_DIR = build

# Arquivos
SRCS = $(wildcard $(NETWORK_DIR)/*.c) $(wildcard $(UTIL_DIR)/*.c) $(wildcard $(PARSER_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
MAIN = main.c
MAIN_OBJ = $(MAIN:.c=.o)
TARGET = app

# Regras principais
all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): $(MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(MAIN_OBJ) $(TARGET)

.PHONY: all clean
