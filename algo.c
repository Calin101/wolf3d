/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   algo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/10 19:27:54 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/25 16:29:17 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

int		colli(t_input *inputs, t_fdot dot, t_thread *thread)
{
	if (dot.x - (int)dot.x == 0)
		dot.x += (thread->alpha < M_PI_2 ||
		thread->alpha > inputs->m3pi_2) ? 0 : -1;
	if (dot.y - (int)dot.y == 0)
		dot.y += (thread->alpha < M_PI) ? -1 : 0;
	if (dot.x < 0 || dot.y < 0 || dot.x > inputs->xmax || dot.y > inputs->ymax)
		return (0);
	if (inputs->tab[((int)dot.y) * inputs->xmax + (int)dot.x] == 2)
		return (1);
	else
		return (0);
}

void	define_text(t_input *inputs, t_thread *thread, t_fdot closest)
{
	if (fmod(closest.x, 1))
	{
		if (thread->alpha > M_PI)
			thread->text = 0;
		else
			thread->text = 1;
	}
	else
	{
		if (!(thread->alpha < M_PI_2 || thread->alpha > inputs->m3pi_2))
			thread->text = 2;
		else
			thread->text = 3;
	}
}

void	redefine_wall(t_input *inputs, t_thread *thread,
int height, t_fdot closest)
{
	if (dist(inputs->posplayer, closest) * 100 > 0.0001)
	{
		height = (double)inputs->wall_size / (dist(inputs->posplayer,
		closest) * cos(thread->inputs->dirplayer - thread->alpha));
		thread->wallmin = inputs->win_h / 2 - height + inputs->intotherun *
		((double)inputs->win_h / 1000);
		thread->wallmax = inputs->win_h / 2 + height + inputs->intotherun *
		((double)inputs->win_h / 1000);
	}
	else
	{
		thread->wallmax = inputs->win_h;
		thread->wallmin = 0;
	}
}

void	printline(t_input *inputs, t_fdot closest, t_thread *thread)
{
	double	height;
	float	column;

	column = (fmod(closest.x, 1) ? fmod(closest.x, 1) : fmod(closest.y, 1));
	height = 0;
	if (closest.x == -1 && closest.y == -1)
	{
		height = 0;
		thread->wallmin = (inputs->win_h / 2 - height) + inputs->intotherun *
		((double)inputs->win_h / 1000);
		thread->wallmax = (inputs->win_h / 2 + height) + inputs->intotherun *
		((double)inputs->win_h / 1000);
	}
	else
	{
		redefine_wall(inputs, thread, height, closest);
		define_text(inputs, thread, closest);
		print_text((t_dot){.x = thread->wallmax, .y = thread->wallmin},
		&thread->inputs->tab_text[thread->text], column, thread);
	}
	thread->wallmax > inputs->win_h ? thread->wallmax = inputs->win_h - 1 :
	print_ground(thread->wallmax, thread, inputs);
	thread->wallmin == 0 ? thread->wallmin = 0 :
	print_sky(thread->wallmin, thread, inputs);
}

void	define_dot(t_input *inputs, t_thread *thread, int dx, int dy)
{
	if (thread->alpha > 0 && thread->alpha < M_PI)
		thread->p2.y = (int)inputs->posplayer.y + dy;
	else
		thread->p2.y = (int)inputs->posplayer.y + 1 + dy;
	if (thread->alpha > M_PI_2 && thread->alpha < inputs->m3pi_2)
		thread->p1.x = (int)inputs->posplayer.x + dx;
	else
		thread->p1.x = (int)inputs->posplayer.x + 1 + dx;
	thread->p1.y = thread->ray.a * thread->p1.x + thread->ray.b;
	thread->p2.x = (thread->p2.y - thread->ray.b) / thread->ray.a;
}
