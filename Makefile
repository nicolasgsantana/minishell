GREEN  = \033[1;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
CYAN   = \033[1;36m
RESET  = \033[0m
ERASE  = \033[K

NAME = minishell
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

LIBFT_DIR= lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
### REMOVE -g flag before sending project
### -g flag for DEBUG ONLY
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)/inc
LIBS = $(LIBFT) -lreadline

SRC = $(addprefix src/, main.c \
						executor/exec_utils.c \
						executor/execute_cmd.c \
						executor/executor.c \
						executor/pipes.c \
						executor/redir.c \
						executor/heredoc.c \
						builtins/dup_env.c \
						builtins/env_utils.c \
						builtins/ft_cd.c \
						builtins/ft_echo.c \
						builtins/ft_env.c \
						builtins/ft_exit.c \
						builtins/ft_export.c \
						builtins/ft_pwd.c \
						builtins/ft_unset.c \
						lexer/lexer.c \
						lexer/token.c \
						lexer/ft_isspace.c \
						lexer/handle_quote.c \
						lexer/handle_operator.c \
						lexer/handle_word.c \
						parser/parser.c \
						parser/check_quotes.c \
						parser/append.c \
						parser/check_redir.c \
						parser/check_misc.c \
						parser/tk_handlers.c \
						expansion/expansion.c \
						expansion/get_var.c \
						expansion/validation.c \
						)
HEADER = inc/minishell.h

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@printf "\n$(GREEN)$(NAME) created$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "\r$(ERASE)$(BLUE) compiled $(notdir $@)$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@printf "$(GREEN)dir $(OBJ_DIR)/ created $(RESET)\n"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(YELLOW)removed $(OBJ_DIR)/ dir$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(YELLOW)removed $(NAME)$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
