# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/17 17:47:06 by kbagot            #+#    #+#              #
#    Updated: 2017/03/13 11:45:52 by kbagot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAGS = -Wall -Werror -Wextra -g
I_FILES = main.c print_line.c make_dir.c make_all_r.c redirect_arg.c find_error.c set_len.c list_b.c free_land.c
O_FILES = $(I_FILES:.c=.o)
C_FILES = $(addprefix src/, $(I_FILES))
LIBFT = -L libft/ -lft

.PHONY: all clean fclean re

all: $(NAME)
$(NAME): $(C_FILES)
	@echo "\033[0;35mCompile $(NAME)"
	@make -C libft/
	@gcc -o $(NAME) $(FLAGS) $(C_FILES) $(LIBFT) 
clean:
	@echo "\033[0;35mDelete ft_ls object files"
	@rm -rf $(O_FILES)
	@make -C libft/ clean
fclean: clean
	@echo "\033[0;35mDelete $(NAME)"
	@rm -rf $(NAME)
	@make -C libft/ fclean
re: fclean all
