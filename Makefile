# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/06/25 16:00:03 by calin        #+#   ##    ##    #+#        #
#    Updated: 2019/09/17 20:12:24 by calin       ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = wolf3d

SRCS = algotest.c\
            parser.c\
			texture.c\
			utils.c\
            fct.c

OBJ = $(SRCS:%.c=%.o)

INC = wolfalgo.h

FLAGS =  -Wall -Wextra -Werror -fsanitize=address

LIBFT = libft/libft.a

LIBMLX = minilibx_macos/libmlx.a

OPENGL = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ)
		gcc $(FLAGS) $^ $(OPENGL) -o $@ -g

%.o: %.c $(INC)
		gcc $(FLAGS) -c $< -o $@    

$(LIBFT):
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

.PHONY: all clean fclean re