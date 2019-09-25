# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/06/25 16:00:03 by calin        #+#   ##    ##    #+#        #
#    Updated: 2019/09/25 16:03:02 by calin       ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re libftcompil

NAME = wolf3d

SRCS = algo.c\
            parser.c\
			texture.c\
			utils.c\
			raycasting.c\
			key_event.c\
			main.c\
            fct.c

OBJ = $(SRCS:%.c=%.o)

INC = wolf.h

FLAGS =  -Wall -Wextra -Werror

LIBFT = libft/libft.a

LIBMLX = minilibx_macos/libmlx.a

OPENGL = -framework OpenGL -framework AppKit

all: lib $(NAME)

$(NAME): $(LIBMLX) $(OBJ)
		gcc $(FLAGS) $(LIBMLX) $(OBJ) $(OPENGL) -o $(NAME) -g $(LIBFT)

%.o: %.c $(INC)
		gcc $(FLAGS) -c $< -o $@

lib:
		make -C libft/

$(LIBMLX):
		make -C minilibx_macos/

clean:
		make clean -C libft/
		make clean -C minilibx_macos/
		rm -rf $(OBJ)

fclean: clean
		make fclean -C libft/
		rm -rf $(NAME)

re: fclean all
		make re -C minilibx_macos/
