# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsilance <jsilance@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 02:54:08 by jsilance          #+#    #+#              #
#    Updated: 2020/10/25 20:44:22 by jsilance         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

SRC = main.c treat/keyboard_treat.c treat/window_treat.c map_filler/map_read.c \
	map_filler/struct_init.c map_filler/ft_realloc_d_malloc.c \
	map_filler/ft_map_checker.c map_filler/ft_map_filler_utils.c \
	rays/rays.c treat/light_utils.c rays/rays_utils.c \
	bmp/bmp_save.c rays/sprite_casting.c rays/rays_dist_calc.c \
	map_filler/ft_map_checker_utils.c treat/ft_error.c \
	map_filler/ft_map_checker_utils2.c \

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

COMPFLAGS = -Lminilibx_opengl -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compilation..."
	@make -C libft all
	@make -C minilibx_opengl
	@gcc $(FLAGS) $(COMPFLAGS) $(OBJ) -fsanitize=address libft.a libmlx.a -o $(NAME)
	@echo "Compilation complete!"

%.o: %.c
	@gcc -c -o $@ $? 

clean:
	@echo "Cleaning..."
	@make -C libft clean
	@make -C minilibx_opengl clean
	@/bin/rm -f ${OBJ}
	@/bin/rm -f libft.a
	@/bin/rm -f $(NAME)
	@echo "Cleaning complete!"

fclean:	clean
	@make -C libft fclean
	@/bin/rm -f $(NAME)

re:	fclean all

bonus: all

.PHONY: re all clean fclean test testre
