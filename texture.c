/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   texture.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 16:27:15 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 18:33:55 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void	print_text(t_dot y, t_texture *texture, double p, t_thread *thread)
{
	double	dy_texture;
	int		x_texture;
	double	y_texture;

	if (y.x == y.y)
		return ;
	x_texture = p * texture->width;
	y_texture = 0;
	dy_texture = ((texture->height - 1)) / (double)(y.x - y.y);
	while (y.y < y.x)
	{
		if (!(y.y < 0 || y.y >= thread->inputs->win_h))
			thread->inputs->im.tab[y.y * thread->inputs->win_w +
			thread->index] = texture->im.tab[(int)y_texture *
			texture->width + x_texture];
		y_texture += dy_texture;
		y.y++;
	}
}

void	print_sky(int max, t_thread *thread, t_input *inputs)
{
	int i;

	i = -1;
	while (++i < max)
		inputs->im.tab[i * inputs->win_w + thread->index] = SKYCOLOR;
}

void	print_ground(int min, t_thread *thread, t_input *inputs)
{
	int i;

	i = min - 1;
	while (++i < inputs->win_h - 2)
		inputs->im.tab[i * inputs->win_w + thread->index] = GROUNDCOLOR;
}

int		parse_text(t_input *inputs)
{
	int i;

	i = 0;
	while (i < NB_TEXTURE)
	{
		if (!(inputs->tab_text[i].im.ad = mlx_xpm_file_to_image(inputs->mlx_ad,
		inputs->name_text[i], &inputs->tab_text[i].width,
		&inputs->tab_text[i].height)))
		{
			ft_putendl("erreur texture");
			return (0);
		}
		inputs->tab_text[i].im.tab = (int *)mlx_get_data_addr(
		inputs->tab_text[i].im.ad, &(inputs->tab_text[i].im.bits_per_pixel),
		&(inputs->tab_text[i].im.size_line), &(inputs->tab_text[i].im.endian));
		i++;
	}
	return (1);
}
