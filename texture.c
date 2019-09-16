/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   texture.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 16:27:15 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/16 21:59:27 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolfalgo.h"

void	print_text(t_dot y, t_texture *texture, double p, t_thread *thread)
{
	double	dy_texture;
	int		x_texture;
	double	y_texture;

	x_texture = p * texture->width;
	y_texture = 0;
	dy_texture = texture->height / (double)(y.x - y.y);
	while (y.y < y.x)
    {
		thread->inputs->im.tab[y.y * thread->inputs->win_w + thread->index] =\
				texture->im.tab[(int)y_texture * texture->width + x_texture];
		y_texture += dy_texture;
		y.y++;
	}
}

void    parse_text(t_input *inputs)
{
	//printf("SI CA EGFAULT ICI ON EST NUL\n");
    int i;
    i = 0;
    while (i < NB_TEXTURE)
    {
        if (!(inputs->tab_text[i].im.ad = mlx_xpm_file_to_image(inputs->mlx_ad, "texture/titi.xpm", &inputs->tab_text[i].width, &inputs->tab_text[i].height)))
		{
			ft_putendl("erreur texture\n");
			return;
		}
		//mlx_put_image_to_window(inputs->mlx_ad, inputs->win_ad, inputs->tab_text[i].im.ad, 0, 0);
        inputs->tab_text[i].im.tab = (int *)mlx_get_data_addr(inputs->tab_text[i].im.ad, &(inputs->tab_text[i].im.bits_per_pixel), &(inputs->tab_text[i].im.size_line), &(inputs->tab_text[i].im.endian));
	//	printf("BTM\n");
        i++;
    }
}