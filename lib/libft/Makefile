GREEN  = \033[1;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
CYAN   = \033[1;36m
RESET  = \033[0m
ERASE  = \033[K

NAME = libft.a
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
INCLUDES = -I$(INC_DIR)

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADER = $(wildcard $(INC_DIR)/*.h)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@echo "\n$(GREEN)$(NAME) created$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@printf "\r$(ERASE)$(BLUE) Compiled $(notdir $<)$(RESET)"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN) obj directory created$(RESET)"

clean:
	@echo "$(YELLOW) obj directory removed$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)$(NAME) removed$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re