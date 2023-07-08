# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 11:44:25 by joonasmykka       #+#    #+#              #
#    Updated: 2023/07/07 14:02:30 by joonasmykka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG = -g -fsanitize=address

NAME = minishell
BIN_DIR = bin
TARGET = $(BIN_DIR)/$(NAME)
BONUS_TARGET = $(BIN_DIR)/$(NAME)_BONUS

LIBFT_DIR = ./src/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = cc

CFLAGS = $(DEBUG) -Wall -Werror -Wextra -I./inc
# LDFLAGS = $(DEBUG) -L$(LIBFT_DIR) -lft -L$(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
LDFLAGS = $(DEBUG) -L$(LIBFT_DIR) -lft -L/opt/homebrew/opt/readline/lib -lreadline

SRC_FILES := \
    src/tokenizer/tokenizer_helpers.c src/tokenizer/expansion_mode_helpers.c \
    src/tokenizer/redirection_helpers.c src/tokenizer/edge_cases.c \
    src/parser/handle_cmds_and_args.c src/parser/parser_helpers.c \
    src/parser/parser_allocate_helper.c src/tokenizer/buffer.c \
    src/tokenizer/store_token.c src/tokenizer/evaluate_char.c \
    src/tokenizer/tokenize.c src/tokenizer/expansion_mode.c \
    src/builtins/unset_helper.c src/execute/child_parent.c \
    src/execute/execute.c src/execute/execute_helpers.c \
    src/execute/execute_builtin.c src/execute/redirs.c \
    src/builtins/builtin_helpers.c src/builtins/env.c \
    src/input/heredoc_helpers.c src/input/multiline.c \
    src/parser/parser.c src/parser/redirections.c \
    src/clean_exit_helper.c src/error_checking.c \
    src/builtins/echo.c src/builtins/export.c \
    src/builtins/exit.c src/builtins/unset.c \
    src/input/heredoc.c src/input/input.c \
    src/builtins/pwd.c src/builtins/cd.c \
    src/clean_cur.c src/clean_exit.c \
    src/init_helpers.c src/debug.c \
    src/builtins/export_helper.c \
    src/globals.c src/init.c \
    src/main.c src/signal.c \
	src/input/prompt.c\
	src/termios.c

OBJ_DIR = obj
OBJ_FILES := $(patsubst src/%,$(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

BONUS_DIR = src/bonus
BONUS_FILES := \
	$(BONUS_DIR)/rl_history_bonus.c \
	$(BONUS_DIR)/rl_helpers_bonus.c \
	$(BONUS_DIR)/clean_exit_bonus.c \
	$(BONUS_DIR)/readline_bonus.c \
	$(BONUS_DIR)/termios_bonus.c \
	$(BONUS_DIR)/heredoc_bonus.c \
	$(BONUS_DIR)/signal_bonus.c \
	$(BONUS_DIR)/cursor_bonus.c \
	$(BONUS_DIR)/prompt_bonus.c \
	$(BONUS_DIR)/main_bonus.c

BONUS_FILTER := $(patsubst src/bonus/%_bonus.c, src/%.c, $(filter src/bonus/%_bonus.c, $(BONUS_FILES)))
BONUS_FILTER += $(patsubst src/bonus/%_bonus.c, src/input/%.c, $(filter src/bonus/%_bonus.c, $(BONUS_FILES)))
BONUS_SRC_FILES := $(filter-out $(BONUS_FILTER), $(SRC_FILES))	
BONUS_SRC_FILES += $(BONUS_FILES)
BONUS_OBJ_FILES := $(patsubst %.o, $(OBJ_DIR)/%.o, $(BONUS_SRC_FILES))

.PHONY: all run bonus clean fclean re leaks 

all: $(TARGET)

bonus: $(BONUS_TARGET)

$(TARGET): $(LIBFT_LIB) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_TARGET): $(LIBFT_LIB) $(BONUS_OBJ_FILES)
	$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) $(LDFLAGS) -o $@

$(OBJ_DIR)/%_bonus.o: src/%_bonus.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)/**/*.o
	rm -rf $(OBJ_DIR)/*.o

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(TARGET) $(BONUS_TARGET)

re: fclean all


leaks: $(TARGET)
	leaks --atExit -- ./$(TARGET)
