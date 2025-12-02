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

GREEN		= \033[0;32m
GREY		= \033[0;90m
RED			= \033[0;31m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(MLX_LIBS) -o $(NAME)
	@echo "$(GREEN)Executable created: $(NAME)$(RESET)"

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
