/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 18:27:08 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/09/23 19:11:13 by mwaterso    ###    #+. /#+    ###.fr     */
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
	inputs->fov = M_PI / 4;
	inputs->dirplayer = M_PI;
	inputs->win_w = 1000;
	inputs->win_h = 1000;
	inputs->vitesse = 0.1;
	inputs->running = 0;
	inputs->x_hitbox.x = -0.01;
	inputs->x_hitbox.y = 0.01;
	inputs->y_hitbox.x = -0.01;
	inputs->y_hitbox.y = 0.01;
	inputs->m3pi_2 = M_PI_2 * 3;
	inputs->wall_size = 400;
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
	if (key == KEY_UP)
	{
		inputs->posplayer.x += inputs->vitesse * cos(inputs->dirplayer);
		inputs->posplayer.y -= inputs->vitesse * sin(inputs->dirplayer);
	}
	if (key == KEY_DOWN)
	{
		inputs->posplayer.x -= inputs->vitesse * cos(inputs->dirplayer);
		inputs->posplayer.y += inputs->vitesse * sin(inputs->dirplayer);
	}
	if (key == KEY_RIGHT)
	{
		inputs->posplayer.x += inputs->vitesse * cos(inputs->dirplayer + M_PI_2);
		inputs->posplayer.y -= inputs->vitesse * sin(inputs->dirplayer + M_PI_2);
	}
	if (key == KEY_LEFT)
	{
		inputs->posplayer.x += inputs->vitesse * cos(inputs->dirplayer - M_PI_2);
		inputs->posplayer.y -= inputs->vitesse * sin(inputs->dirplayer - M_PI_2);
	}
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
	{
		if (inputs->tab[(int)(inputs->posplayer.x + inputs->x_hitbox.x) + (int)inputs->posplayer.y * inputs->xmax] > 0 || 
		inputs->tab[(int)inputs->posplayer.y + ((int)(inputs->posplayer.y + inputs->y_hitbox.y)) * inputs->xmax] > 0 ||
		inputs->tab[(int)inputs->posplayer.x + ((int)(inputs->posplayer.y + inputs->y_hitbox.x)) * inputs->xmax] > 0 ||
		inputs->tab[(int)(inputs->posplayer.y + inputs->x_hitbox.y) + (int)inputs->posplayer.y * inputs->xmax] > 0)
			inputs->posplayer = inputs->oldposplayer;
		else
			inputs->oldposplayer = inputs->posplayer;
	}
	if (key == KEY_SHIFT_RIGHT)
	{
		if (inputs->running != 0)
		{
			inputs->running = 0;
			inputs->vitesse -= 0.1;
		}
		else
		{
			inputs->running = 1;
			inputs->vitesse += 0.1;
		}
	}
	if (inputs->running)
		inputs->intotherunmf = (inputs->intotherunmf == -1 ? 1 : -1);
	if (key == KEY_D)
	{
		inputs->dirplayer += 0.03 +
		(inputs->dirplayer + 0.1 > 2 * M_PI ? -2 * M_PI : 0);
	}
	if (key == KEY_A)
	{
		inputs->dirplayer += (-0.03 +
		(inputs->dirplayer + 0.1 < 0.00001 ? 2 * M_PI : 0));
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
