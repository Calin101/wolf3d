/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 20:29:39 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 20:31:15 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolfalgo.h"

int		main(int argc, char **argv)
{
	t_input inputs;

	(void)argc;
	inputs.fd = open(argv[1], O_RDONLY);
	inputs.fd2 = open(argv[1], O_RDONLY);
	inputs.fd3 = open(argv[1], O_RDONLY);
	parse_file(&inputs);
	init_var(&inputs);
	parse_text(&inputs);
	mlx_put_image_to_window(inputs.im.tab, inputs.win_ad, inputs.im.ad, 0, 0);
	mlx_hook(inputs.win_ad, 2, 0, &ft_keyboard, &inputs);
	mlx_loop(inputs.mlx_ad);
	return (0);
}
