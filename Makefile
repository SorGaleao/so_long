NAME		= so_long
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
INCLUDE 	= -Iinclude
MLX_LIBS	= -lmlx -lX11 -lXext -lm

SRCS = 	src/so_long.c \
		src/so_long_utils.c \
		src/so_long_fts_map.c \
		src/so_long_fts_clean.c\
		src/get_next_line.c \
		src/get_next_line_utils.c \
		src/ft_printf.c \
		src/ft_is_int.c \
		src/ft_is_char.c\
		src/ft_is_str.c \
		src/ft_is_unsigned_int.c \
		src/ft_is_percent.c \
		src/ft_is_hex.c

OBJS = $(SRCS:src/%.c=obj/%.o)

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m
CHECK = \033[0;34m✔\033[0m
BOLD = \033[1m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(MLX_LIBS) -o $(NAME)
	@echo "$(CHECK) $(BOLD)Executable built successfully!$(RESET)\n"
	@echo "$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(BLUE)$(BOLD)  🎮 How to run the game:$(RESET)"
	@echo "$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(GREEN)  • Game maps:$(RESET)"
	@echo "    $(BOLD)./$(NAME) maps/valid_map.cub$(RESET)"
	@echo "    $(BOLD)./$(NAME) maps/labyrinth.cub$(RESET)\n"
	@echo "$(BOLD)$(BLUE)$(BOLD)  🎮 How to play:$(RESET)"
	@echo "$(GREEN)  • Movement:$(RESET) $(BOLD)W$(RESET) (up), $(BOLD)A$(RESET) (left), $(BOLD)S$(RESET) (down), $(BOLD)D$(RESET) (right)"
	@echo "$(GREEN)  • Goal:$(RESET) Collect all $(BOLD)strawberries $(RESET)to access the exit"
	@echo "$(GREEN)  • Exit:$(RESET) $(BOLD)ESC$(RESET) or click the close button (X) in the top-right corner"
	@echo "$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)\n"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

valgrind: $(NAME)
	valgrind --leak-check=full ./$(NAME)

clean:
	@$(RM) $(OBJS)
	@$(RM) -r obj
	@echo "$(RED)Cleaned object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Fully cleaned everything.$(RESET)"
re: fclean all

.PHONY: all clean fclean re run valgrind
