/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wolf.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/15 15:38:23 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 18:36:03 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include "keyboard.h"
# include <pthread.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>
# define NB_THREAD		1
# define NB_TEXTURE		4
# define SKYCOLOR		0x320000
# define GROUNDCOLOR	0x000000

typedef struct		s_fdot
{
	double			x;
	double			y;
	double			z;
}					t_fdot;

typedef struct		s_dot
{
	int				x;
	int				y;
	int				z;
}					t_dot;

typedef struct		s_wall
{
	int				wallmin;
	int				wallmax;
}					t_wall;

typedef struct		s_image
{
	void			*ad;
	int				*tab;
	int				bits_per_pixel;
	int				size_line;
	int				endian;

}					t_image;

typedef	struct		s_texture
{
	int				height;
	int				width;
	t_image			im;
}					t_texture;

typedef struct		s_affine
{
	double			a;
	double			b;
	int				is_equation;
}					t_affine;

typedef struct		s_thread
{
	pthread_t		thread;
	long			start;
	long			end;
	int				text;
	int				index;
	struct s_input	*inputs;
	double			alpha;
	t_affine		ray;
	t_fdot			p1;
	t_fdot			p2;
	int				wallmax;
	int				wallmin;
}					t_thread;

typedef struct		s_input
{
	void			*mlx_ad;
	void			*win_ad;
	void			*button_ad;
	int				win_h;
	int				win_w;
	int				totalnb;
	int				countline;
	int				wall_size;
	int				fd;
	int				fd2;
	int				fd3;
	int				*tab;
	int				scale;
	int				xmax;
	int				ymax;
	t_fdot			oldposplayer;
	char			*name_text[NB_TEXTURE];
	t_texture		tab_text[NB_TEXTURE];
	t_fdot			rotplayer;
	t_thread		thread_tab[NB_THREAD];
	long			render;
	t_fdot			posplayer;
	double			dirplayer;
	double			fov;
	double			step_ray;
	double			m3pi_2;
	double			vitesse;
	int				running;
	int				intotherunmf;
	int				hit;
	int				index;
	t_image			im;
	t_fdot			x_hitbox;
	t_fdot			y_hitbox;
}					t_input;

typedef struct		s_index
{
	int				i;
	int				j;
}					t_index;

void				fill_texture_tab(t_input *data);
void				print_ground(int min, t_thread *thread, t_input *inputs);
void				print_sky(int max, t_thread *thread, t_input *inputs);
double				dist(t_fdot p1, t_fdot p2);
void				*printscreen(void *thread);
void				clear_im(t_input *data);
void				print_text(t_dot y, t_texture *texture,
					double colonne, t_thread *thread);
int					parse_text(t_input *inputs);
void				create_thread(t_input *input);
int					parse_file(t_input *data);
int					ft_keyboard(int key, t_input *inputs);
int					raycasting(t_thread *thread);
int					colli(t_input *inputs, t_fdot dot, t_thread *thread);
int					init_var(t_input *inputs);
int					ft_keyboard(int key, t_input *inputs);
void				error(t_input *data);
void				printline(t_input *inputs, t_fdot closest,
					t_thread *thread);
void				define_dot(t_input *inputs, t_thread *thread,
					int dx, int dy);
int					ft_close(t_input *inputs);
void				clearall(t_input *inputs);

#endif
