/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wolfalgo.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/15 15:38:23 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/23 17:51:54 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WOLFALGO_H
# define WOLFALGO_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include "keyboard.h"
# include <pthread.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# define NBRTHREAD		8

typedef struct  s_dot
{
   double		x;
   double		y;
   double		z;
}               t_dot;

typedef struct	s_wall
{
	double		zmin;
	double		zmax;
}				t_wall;

typedef struct		s_image
{
	void	*ad;
	int 	*tab;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	
}					t_image;

typedef struct		s_input
{
	void	*mlx_ad;
	void	*win_ad;
	void	*button_ad;
	int		win_h;
	int		win_w;
	int		totalnb;
	int		fd;
    int		fd2;
    int		fd3;
	int		*tab;
	int		*tab_line;
	int		xmax;
	int		ymax;
	int		zmax;

	t_wall	tab_tex[4];
	t_dot	rotplayer;
	t_wall	rotscreen;

	long render;
	double k;

	t_dot	player_pos;

	t_image im;
}					t_input;

typedef struct    s_index
{
    int            i;
    int            j;
}                t_index;

int		parse_file(t_input *data);


#endif