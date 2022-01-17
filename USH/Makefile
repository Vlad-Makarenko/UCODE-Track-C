CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

NAME = ush

SRC_DIR	= src
INC_DIR	= inc
OBJ_DIR	= obj

INC_FILES = $(wildcard $(INC_DIR)/*.h)
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))

LIBMX_DIR = libmx
LIBMX_A:= $(LIBMX_DIR)/libmx.a
LIBMX_INC:= $(LIBMX_DIR)/inc

all: install

install: $(LIBMX_A) $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) -L$(LIBMX_DIR) -lmx -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIBMX_INC)

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBMX_A):
	@make -sC $(LIBMX_DIR)

clean:
	@rm -rf $(OBJ_DIR)

uninstall:
	@make -sC $(LIBMX_DIR) uninstall
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)

reinstall: uninstall all
