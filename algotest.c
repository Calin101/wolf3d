/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   algotest.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/10 19:27:54 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 21:05:46 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolfalgo.h"

void	create_thread(t_input *input)
{
	int		i;
	double	alpha;

	alpha = input->dirplayer - input->fov / 2;
	i = 0;
	clear_im(input);
	while (i < NB_THREAD)
	{
		while (alpha < (input->dirplayer - input->fov / 2) +
		((double)((float)i / (float)NB_THREAD) * input->fov))
			alpha += input->step_ray - (alpha +
			input->step_ray > M_PI * 2 ? 2 * M_PI : 0);
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

int		colli(t_input *inputs, t_fdot dot, t_thread *thread)
{
//	printf("colli\n");
	if (dot.x - (int)dot.x == 0)
	{
		dot.x += (thread->alpha < M_PI_2 ||
		thread->alpha > inputs->_3pi_2) ? 0 : -1;
	}
	//	printf("colli2\n");
	if (dot.y - (int)dot.y == 0)
		dot.y += (thread->alpha < M_PI) ? -1 : 0;
	//	printf("colli3\n");
	if (dot.x < 0 || dot.y < 0 || dot.x > inputs->xmax || dot.y > inputs->ymax)
		return (0);
	//	printf("index = %d\n", ((int)dot.y) * inputs->xmax + (int)dot.x);
	if (inputs->tab[((int)dot.y) * inputs->xmax + (int)dot.x] == 2)
	{
		thread->text = 0;
		return (1);
	}
	//	printf("colli4\n");
	if (inputs->tab[((int)dot.y) * inputs->xmax + (int)dot.x] == 3)
	{
		thread->text = 0;
		return (1);
	}
	else
		return (0);
}

void	printline(t_input *inputs, t_fdot closest, t_thread *thread)
{
	double	height;
	int	wallmin;
	int	wallmax;
	float	colonne;
	int		color;

	height = 0;
	color = 0X0FFF00;
	colonne = (fmod(closest.x, 1) ? fmod(closest.x, 1) : fmod(closest.y, 1));
	if (closest.x == -1 && closest.y == -1)
	{
		height = 0;
		wallmin = inputs->win_h / 2 - height;
		wallmax = inputs->win_h / 2 + height;
	}
	else
	{
		printf("dist = %lf\n", dist(inputs->posplayer, closest));
		if (dist(inputs->posplayer, closest) * 100 > 0.0001)
		{
			height = (double)inputs->wall_size / (dist(inputs->posplayer,
			closest) * cos(thread->inputs->dirplayer - thread->alpha));
			wallmin = inputs->win_h / 2 - height;
			wallmax = inputs->win_h / 2 + height;
			printf("%d			%lf		%lf\n", wallmax, dist(inputs->posplayer, closest) * 100, dist(inputs->posplayer, closest));
		}
		else
		{
			wallmax = inputs->win_h;
			wallmin = 0;
		}
	}
	if (thread->text == 3)
		color = 0xFF0000;
	else if (thread->text == 2)
		color = 0x0FFF00;
	if (wallmax > inputs->win_h)
		wallmax = 699;
	else
		print_ground(wallmax, thread, inputs);
	if (wallmin < 0)
		wallmin  = 0;
	else
		print_sky(wallmin, thread, inputs);
	if (closest.x != -1 || closest.y != -1)
		print_text((t_dot){.x = (wallmax), .y = wallmin},
		&thread->inputs->tab_text[thread->text], colonne, thread);
}

int		ray(t_input *inputs, t_thread *thread)
{
	t_fdot	p1;
	t_fdot	p2;
	int		dx;
	int		dy;
	t_fdot	closest;

	dx = 0;
	dy = 0;
	closest = (t_fdot){.x = inputs->posplayer.x, .y = inputs->posplayer.y};
	while (colli(inputs, closest, thread) == 0)
	{
		if (thread->alpha > 0 && thread->alpha < M_PI)
			p2.y = (int)inputs->posplayer.y + dy;
		else
			p2.y = (int)inputs->posplayer.y + 1 + dy;
		if (thread->alpha > M_PI_2 && thread->alpha < inputs->_3pi_2)
			p1.x = (int)inputs->posplayer.x + dx;
		else
			p1.x = (int)inputs->posplayer.x + 1 + dx;
		p1.y = thread->ray.a * p1.x + thread->ray.b;
		p2.x = (p2.y - thread->ray.b) / thread->ray.a;
		if (dist(inputs->posplayer, p1) < dist(inputs->posplayer, p2))
		{
			dx += thread->alpha < M_PI / 2 ||
			thread->alpha > inputs->_3pi_2 ? 1 : -1;
			closest = p1;
		}
		else
		{
			dy += thread->alpha < M_PI ? -1 : 1;
			closest = p2;
		}
		if (dist(inputs->posplayer, closest) > 75)
		{
			printline(inputs, (t_fdot){.x = -1, .y = -1}, thread);
			return (0);
		}
	}
	printline(inputs, closest, thread);
	return (1);
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
		ray(thread->inputs, thread);
		thread->alpha += thread->inputs->step_ray -
		(thread->alpha + thread->inputs->step_ray > M_PI * 2 ? 2 * M_PI : 0);
	}
	return (1);
}
