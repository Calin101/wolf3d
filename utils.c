/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 18:27:08 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 20:57:36 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolfalgo.h"

double	dist(t_fdot p1, t_fdot p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x) +
	(p2.y - p1.y) * (p2.y - p1.y)));
}

int		init_var(t_input *inputs)
{
	inputs->index = 0;
	inputs->fov = M_PI / 2;
	inputs->dirplayer = M_PI / 2;
	inputs->win_w = 1500;
	inputs->win_h = 1500;
	inputs->x_hitbox.x = -0.25;
	inputs->x_hitbox.y = 0.25;
	inputs->y_hitbox.x = -0.25;
	inputs->y_hitbox.y = 0.25;
	inputs->_3pi_2 = M_PI_2 * 3;
	inputs->wall_size = 150;
	fill_texture_tab(inputs);
	inputs->oldposplayer = inputs->posplayer;
	inputs->mlx_ad = mlx_init();
	inputs->win_ad = mlx_new_window(inputs->mlx_ad, inputs->win_w,
	inputs->win_h, "Wolf3d");
	inputs->step_ray = inputs->fov / inputs->win_w;
	inputs->im.ad = mlx_new_image(inputs->mlx_ad, inputs->win_w, inputs->win_h);
	inputs->im.tab = (int *)mlx_get_data_addr(inputs->im.ad,
	&(inputs->im.bits_per_pixel), &(inputs->im.size_line),
	&(inputs->im.endian));
	return (1);
}

void	clearall(t_input *inputs)
{
	mlx_destroy_image(inputs->mlx_ad, inputs->im.ad);
	mlx_destroy_window(inputs->mlx_ad, inputs->win_ad);
	free(inputs->tab);
	//free(inputs->tab_line);
	exit(EXIT_SUCCESS);
}

int		ft_keyboard(int key, t_input *inputs)
{
	if (key == KEY_PAD_8)
	{
		inputs->posplayer.x += 0.25;
	/*	inputs->posplayer.x += cos(inputs->dirplayer);
		inputs->posplayer.y += sin(inputs->dirplayer);*/
	}
	if (key == KEY_PAD_5)
		inputs->posplayer.x -= 0.25;
	if (key == KEY_PAD_4)
		inputs->posplayer.y += 0.25;
	if (key == KEY_PAD_6)
		inputs->posplayer.y -= 0.25;
	if (key == KEY_PAD_8 || key == KEY_PAD_5 || key == KEY_PAD_4 || key == KEY_PAD_6)
	{
		if (inputs->tab[(int)(inputs->posplayer.x + inputs->x_hitbox.x) + ((int)(inputs->posplayer.y + inputs->y_hitbox.x)) * inputs->xmax] > 0 || 
		inputs->tab[(int)(inputs->posplayer.y + inputs->x_hitbox.y) + ((int)(inputs->posplayer.y + inputs->y_hitbox.y)) * inputs->xmax] > 0)
			inputs->posplayer = inputs->oldposplayer;
		else
			inputs->oldposplayer = inputs->posplayer;
	}
	if (key == KEY_RIGHT)
	{
		inputs->dirplayer += 0.1 +
		(inputs->dirplayer + 0.1 > 2 * M_PI ? -2 * M_PI : 0);
	}
	if (key == KEY_P)
	{
		printf("x %lf y %lf\n", inputs->posplayer.x, inputs->posplayer.y);
	}
	if (key == KEY_LEFT)
	{
		inputs->dirplayer += (-0.1 +
		(inputs->dirplayer + 0.1 < 0 ? 2 * M_PI : 0));
	}
	if (key == KEY_ESCAPE)
		clearall(inputs);
	inputs->index = 0;
	create_thread(inputs);
	return (1);
}

void	*printscreen(void *thread)
{
	raycasting((t_thread*)thread);
	return (0);
}
