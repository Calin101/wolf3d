/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/24 16:43:18 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 17:32:45 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void	ray(t_input *inputs, t_thread *thread, t_fdot closest)
{
	int		dx;
	int		dy;

	dx = 0;
	dy = 0;
	while (colli(inputs, closest, thread) == 0)
	{
		define_dot(inputs, thread, dx, dy);
		if (dist(inputs->posplayer, thread->p1) < dist(inputs->posplayer,
		thread->p2))
		{
			dx += thread->alpha < M_PI / 2 ||
			thread->alpha > inputs->m3pi_2 ? 1 : -1;
			closest = thread->p1;
		}
		else
		{
			dy += thread->alpha < M_PI ? -1 : 1;
			closest = thread->p2;
		}
	}
	printline(inputs, closest, thread);
}

int		raycasting(t_thread *thread)
{
	int i;

	i = thread->start - 1;
	if (thread->alpha < 0)
		thread->alpha += 2 * M_PI;
	while (thread->end > ++i)
	{
		thread->index = i;
		thread->ray.a = -tan(thread->alpha);
		thread->ray.b = thread->inputs->posplayer.y -
		thread->ray.a * thread->inputs->posplayer.x;
		ray(thread->inputs, thread, (t_fdot){.x = thread->inputs->posplayer.x,
		.y = thread->inputs->posplayer.y});
		thread->alpha += thread->inputs->step_ray -
		(thread->alpha + thread->inputs->step_ray > M_PI * 2 ? 2 * M_PI : 0);
	}
	return (1);
}

void	create_thread(t_input *input)
{
	int		i;
	double	alpha;

	i = 0;
	clear_im(input);
	while (i < NB_THREAD)
	{
		alpha = (input->dirplayer - input->fov / 2) +
		((double)((float)i / (float)NB_THREAD) * input->fov);
		if (alpha < 0)
			alpha += M_PI * 2;
		if (alpha > 2 * M_PI)
			alpha -= M_PI * 2;
		input->thread_tab[i].alpha = alpha;
		input->thread_tab[i].start = (i * input->win_w) / NB_THREAD;
		input->thread_tab[i].end = ((i + 1) * (input->win_w)) / NB_THREAD;
		input->thread_tab[i].inputs = input;
		pthread_create(&input->thread_tab[i].thread, NULL,
		&printscreen, &input->thread_tab[i]);
		i++;
	}
	i = 0;
	while (i <= NB_THREAD)
		pthread_join(input->thread_tab[i++].thread, NULL);
	mlx_put_image_to_window(input->im.tab, input->win_ad, input->im.ad, 0, 0);
}
