/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 18:27:08 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 18:16:52 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

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
	inputs->intotherunmf = 0;
	inputs->wall_size = 300;
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

void	*printscreen(void *thread)
{
	raycasting((t_thread*)thread);
	return (0);
}
