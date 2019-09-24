/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 20:29:39 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 18:38:03 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void	clearall(t_input *inputs)
{
	mlx_destroy_image(inputs->mlx_ad, inputs->im.ad);
	mlx_destroy_window(inputs->mlx_ad, inputs->win_ad);
	free(inputs->tab);
	exit(EXIT_SUCCESS);
}

int		ft_close(t_input *inputs)
{
	mlx_destroy_image(inputs->mlx_ad, inputs->im.ad);
	mlx_destroy_window(inputs->mlx_ad, inputs->win_ad);
	free(inputs->tab);
	exit(EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	t_input inputs;

	(void)argc;
	inputs.fd = open(argv[1], O_RDONLY);
	inputs.fd2 = open(argv[1], O_RDONLY);
	inputs.fd3 = open(argv[1], O_RDONLY);
	parse_file(&inputs);
	init_var(&inputs);
	if (!parse_text(&inputs))
	{
		free(inputs.tab);
		exit(EXIT_SUCCESS);
	}
	create_thread(&inputs);
	mlx_put_image_to_window(inputs.im.tab, inputs.win_ad, inputs.im.ad, 0, 0);
	mlx_hook(inputs.win_ad, 2, 0, &ft_keyboard, &inputs);
	mlx_hook(inputs.win_ad, 17, 0, &ft_close, &inputs);
	mlx_loop(inputs.mlx_ad);
	return (0);
}
