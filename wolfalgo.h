/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wolfalgo.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/15 15:38:23 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 17:03:36 by mwaterso    ###    #+. /#+    ###.fr     */
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
# include <pthread.h>
# define NB_THREAD		16
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

typedef	struct			s_thread
{
	pthread_t			thread;
	long					start;
	long					end;
	struct s_input		*inputs;
}						t_thread;

typedef struct		s_input
{
	void	*mlx_ad;
	void	*win_ad;
	void	*button_ad;
	int		win_h;
	int		win_w;
	int		totalnb;
	int		countline;
	int		fd;
    int		fd2;
    int		fd3;
	int		*tab;
	int		*tab_line;
	double		xmax;
	double		ymax;
	double		zmax;

	t_wall	tab_tex[4];
	t_dot	rotplayer;
	t_wall	rotscreen;

	t_thread	thread_tab[NB_THREAD];

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