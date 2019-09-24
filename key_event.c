/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_event.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/24 17:23:16 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 18:25:02 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void	check_colli(int key, t_input *inputs)
{
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
	{
		if (inputs->tab[(int)(inputs->posplayer.x + inputs->x_hitbox.x) +
		(int)inputs->posplayer.y * inputs->xmax] > 0 ||
		inputs->tab[(int)inputs->posplayer.y + ((int)(inputs->posplayer.y +
		inputs->y_hitbox.y)) * inputs->xmax] > 0 ||
		inputs->tab[(int)inputs->posplayer.x + ((int)(inputs->posplayer.y +
		inputs->y_hitbox.x)) * inputs->xmax] > 0 ||
		inputs->tab[(int)(inputs->posplayer.y + inputs->x_hitbox.y) +
		(int)inputs->posplayer.y * inputs->xmax] > 0)
			inputs->posplayer = inputs->oldposplayer;
		else
			inputs->oldposplayer = inputs->posplayer;
	}
}

void	keyboard_move(int key, t_input *inputs)
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
		inputs->posplayer.x += inputs->vitesse *
		cos(inputs->dirplayer + M_PI_2);
		inputs->posplayer.y -= inputs->vitesse *
		sin(inputs->dirplayer + M_PI_2);
	}
	if (key == KEY_LEFT)
	{
		inputs->posplayer.x += inputs->vitesse *
		cos(inputs->dirplayer - M_PI_2);
		inputs->posplayer.y -= inputs->vitesse *
		sin(inputs->dirplayer - M_PI_2);
	}
	check_colli(key, inputs);
}

void	rotate_left_right(int key, t_input *inputs)
{
	if (key == KEY_D)
		inputs->dirplayer += 0.03 +
		(inputs->dirplayer + 0.1 > 2 * M_PI ? -2 * M_PI : 0);
	if (key == KEY_A)
		inputs->dirplayer += (-0.03 +
		(inputs->dirplayer + 0.1 < 0.00001 ? 2 * M_PI : 0));
}

int		ft_keyboard(int key, t_input *inputs)
{
	keyboard_move(key, inputs);
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
	rotate_left_right(key, inputs);
	if (key == KEY_ESCAPE)
		clearall(inputs);
	inputs->index = 0;
	create_thread(inputs);
	return (1);
}
