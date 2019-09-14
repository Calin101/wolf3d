/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wolfalgo.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/15 15:38:23 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/13 19:00:50 by mwaterso    ###    #+. /#+    ###.fr     */
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
# define NB_THREAD              1
typedef struct  s_fdot
{
   double               x;
   double               y;
   double               z;
}               t_fdot;

typedef struct  s_dot
{
   int          x;
   int          y;
   int          z;
}               t_dot;

typedef struct  s_wall
{
        double          zmin;
        double          zmax;
}                               t_wall;

typedef struct          s_image
{
        void    *ad;
        int     *tab;
        int             bits_per_pixel;
        int             size_line;
        int             endian;

}                                       t_image;

typedef struct			s_affine
{
	double				a;
	double				b;
	int				is_equation;
}				t_affine;

typedef struct                  s_thread
{
        pthread_t                       thread;
        long                            start;
        long                            end;
        int								text;
		int								index;
        struct s_input					*inputs;
		double          				alpha;
		t_affine						ray;
}                                               t_thread;

typedef struct          s_input
{
        void    *mlx_ad;
        void    *win_ad;
        void    *button_ad;
        int             win_h;
        int				win_w;
        int             totalnb;
        int             countline;
        int             fd;
        int         fd2;
        int         fd3;
        int             *tab;
        int             *tab_line;
        int             scale;
        int             wall_size;
        int          xmax;
        int         ymax;
        double          zmax;

        t_wall  tab_tex[4];
        t_fdot  rotplayer;
        t_wall  rotscreen;
        int debug;

        t_thread        thread_tab[NB_THREAD];

        long render;
        double k;
        t_fdot          posplayer;
        double          dirplayer;
        double          fov;
        //double          alpha;
        double          step_ray;
	double		_3pi_2;
	int 	        hit;
	int		index;
        /******************/

        t_image im;
}                                       t_input;

typedef struct    s_index
{
    int            i;
    int            j;
}                t_index;

double			ft_modulo(double nbr, double mod);
void			print_line(t_input *input, t_dot a, t_dot b, int color);
void			*printscreen(void *thread);
void			clear_im(t_input *data);
int             parse_file(t_input *data);
int 			ft_keyboard(int key, t_input *inputs);
int				raycasting(t_thread *thread);
int				colli(t_input *inputs, t_fdot dot, t_thread *thread);

#endif