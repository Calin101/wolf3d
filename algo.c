/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   algo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/15 15:29:15 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/23 19:25:28 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolfalgo.h" 

long findex(double y, int *lenline, int sumax)
{
	int i;
	long sum;

	sum = 0;
	i = -1;
	while(++i < y - 1)
	{
		//printf("%d\n", i);
		sum += lenline[i];
		if (sum == sumax)
			return(-1);
	}
	if (sum >= 0)
		return (sum);
	//printf("woula\n");
	return(-1);
}

int colli(double x, double y, double z, t_input *inputs)
{
	long yesy;

	if (x > inputs->xmax || x <= (double)(0) || y > inputs->ymax || y <= (double)(0) || z > inputs->zmax)
		return (-1);

	if ((yesy = findex((y), inputs->tab_line, inputs->totalnb)) < 0)
		return (-1);
	//printf("end of findex\n");
//	if (y > 3)
//		printf("wesh\n");
	if ((z < inputs->tab_tex[inputs->tab[(long)(x) + yesy]].zmax) &&
	(z > inputs->tab_tex[inputs->tab[(long)(x) + yesy]].zmin))
	{
	//	if (y > 3)
	//		printf("wesh\n");
	//	printf("%lf		%lf		%lf\n", x, y, z);
	//	printf("%lf\n", inputs->tab_tex[0].zmax/*inputs->tab_tex[inputs->tab[(long)(x) % yesy + yesy]].zmax*/);
		//printf("%d\n", inputs->tab[(long)(x) % yesy + yesy]);
		return (inputs->tab[(long)(x) + yesy]);
	}
	return (-1);
}

int raytocol(t_input *inputs, t_dot rot, t_dot dot)
{
	int i;
	double k;
	int text;
	//printf("rot = %lf		%lf		%lf\n", rot.x, rot.y, rot.z);
	//sleep(1);
	i = -1;
	k = 0;
	text = 0;
	
	while ((text = colli(dot.x, dot.y, dot.z, inputs)) < 0 && ++i < inputs->render)
	{
		
		
		/*dot.x += 0.1;
		dot.y = ((double)((double)(cos(rot.x) * ((double)(((double)(dot.x - inputs->player_pos.x)) / sin(rot.x))) + inputs->player_pos.y)));
		dot.z = ((double)((double)(sin(rot.y) * ((double)(((double)(dot.x - inputs->player_pos.x)) / sin(rot.x))) + inputs->player_pos.z)));*/
		//k += (double)(inputs->k * ((double)(i / inputs->render)));
		k += 0.05;
		dot.x = cos(rot.x) * k + inputs->player_pos.x;
		dot.y = sin(rot.x) * k + inputs->player_pos.y;
		dot.z = cos(rot.y) * k + inputs->player_pos.z;
		//printf("AFTER =	%lf		%lf		%lf\n", dot.x, dot.y, dot.z);
		//printf("out of while\n");
	//	if (rot.x > 0.099480 && rot.y > 1.8)
	//	{
	//		printf("BEFORE = %lf	%lf		%lf\n", dot.x, dot.y, dot.z);
	//	}
	}
	if (i < inputs->render)
	{
		if (text == 0)
			return (0xFFFFFF);
		if (text == 2)
			return (0x0000FF);
	}
	return (0x000000);
}

void raytracing(t_input *inputs)
{
	int i;

	i = -1;
	while (++i < (inputs->win_h * inputs->win_w))
	{
	//	printf("%d\n", i);
	//	printf("%d	%d\n", i % inputs->win_h, i / inputs->win_w);
		inputs->im.tab[i] = raytocol(inputs, (t_dot){.x = (double)(inputs->rotplayer.x + (double)(inputs->rotscreen.zmin * (double)(((double)(i % inputs->win_h)) / inputs->win_h)) - ((double)(inputs->rotscreen.zmin / 2))),
		.y = (double)(inputs->rotplayer.y + (double)(inputs->rotscreen.zmax * ((double)((double)(i / inputs->win_w) / inputs->win_w)) - ((double)(inputs->rotscreen.zmax / 2)))), .z = 0}, inputs->player_pos);
	}
}

void wolf(t_input *inputs)
{
	raytracing(inputs);
	mlx_put_image_to_window(inputs->mlx_ad, inputs->win_ad, inputs->im.ad, 0, 0);
}

int var_init(t_input *inputs)
{
	
	inputs->win_h = 750;
	inputs->win_w = 500;
	inputs->render = 300;
	inputs->rotscreen.zmax = M_PI_4;	/*		ecart omega y		*/
	inputs->rotscreen.zmin = M_PI_4;	/*		ecart omega x		*/
	inputs->rotplayer.x = 0;
	printf("ici?\n");
	inputs->rotplayer.y = M_PI_2;
	inputs->rotplayer.z = 3 * M_PI_2;
	inputs->tab_tex[0] = (t_wall){.zmax = 0, .zmin = -0.5};
	inputs->tab_tex[1] = (t_wall){.zmax = 3, .zmin = 2};
	inputs->tab_tex[2] = (t_wall){.zmax = 1, .zmin = -0.5};
	inputs->zmax = 3;
	inputs->k = 0.5;
	printf("ici?\n");
	inputs->mlx_ad = mlx_init();
	inputs->win_ad = mlx_new_window(inputs->mlx_ad, inputs->win_h, inputs->win_w, "Wolf3d");
	inputs->im.ad = mlx_new_image(inputs->mlx_ad, inputs->win_h, inputs->win_w);
	inputs->im.tab = (int *)mlx_get_data_addr(inputs->im.ad, &(inputs->im.bits_per_pixel), &(inputs->im.size_line), &(inputs->im.endian));
	printf("ici?\n");
	
	
	return (1);
}

int keyboard(int key, t_input *inputs)
{
	if (key == KEY_P)
		printf("AFTER =	%lf		%lf		%lf\n", inputs->rotplayer.x, inputs->rotplayer.y, inputs->rotplayer.z);
	if (key == KEY_LEFT)
		inputs->rotplayer.x -= M_PI / 30;
	if (key == KEY_RIGHT)
		inputs->rotplayer.x += M_PI / 30;
	if (key == KEY_UP)
		inputs->rotplayer.y -= M_PI / 30;
	if (key == KEY_DOWN)
		inputs->rotplayer.y += M_PI / 30;
	if (key == KEY_PAD_5)
		inputs->player_pos.x += 0.05;
	if (key == KEY_PAD_2)
		inputs->player_pos.x -= 0.05;
	if (key == KEY_PAD_1)
		inputs->player_pos.y += 0.05;
	if (key == KEY_PAD_3)
		inputs->player_pos.y -= 0.05;
	if (key == KEY_PAD_SUB)
		inputs->player_pos.z += 0.05;
	if (key == KEY_PAD_ADD)
		inputs->player_pos.z -= 0.05;
	if (key == KEY_PAD_MULTIPLY)
	{
		inputs->k += 0.5;
		printf("%lf\n", inputs->k);
	}
	if (key == KEY_PAD_DIVIDE)
	{
		inputs->k -= 0.5;
		printf("%lf\n", inputs->k);
	}
	if (key == KEY_C)
	{
		inputs->render--;
		printf("%ld\n", inputs->render);
	}
	if (key == KEY_V)
	{
		inputs->render++;
		printf("%ld\n", inputs->render);
	}
	wolf(inputs);
	return(1);
}
int main(int arc, char **arv)
{
	t_input inputs;
	//t_wall tabtex[4];

	//if (!(tabtex = (t_wall *)malloc(sizeof(t_wall) * 4)))
	//inputs.tab_tex = tabtex;
	inputs.fd = open(arv[1], O_RDONLY);
	inputs.fd2 = open(arv[1], O_RDONLY);
	inputs.fd3 = open(arv[1], O_RDONLY);
	if (arc != 2)
	{
		ft_putstr("wrong argument number\n");
		return(0);
	}
	printf("parse\n");
	parse_file(&inputs);
	printf("varinit\n");
	var_init(&inputs);
	printf("wolf\n");
	wolf(&inputs);
	/*int i;

	i = -1;
	while (++i < (inputs.win_h * inputs.win_w))
	{
		printf("%d\n", i);
		printf("x = 	%lf\n", (double)(inputs.rotplayer.x + (double)(inputs.rotscreen.zmin * (double)(((double)(i % inputs.win_h)) / inputs.win_h)) - ((double)(inputs.rotscreen.zmin / 2))));
		printf("y = 				%lf\n", (double)(inputs.rotplayer.y + (double)(inputs.rotscreen.zmax * ((double)((double)(i / inputs.win_w) / inputs.win_w)) - ((double)(inputs.rotscreen.zmax / 2)))));
	}*/
	mlx_hook(inputs.win_ad, 2, 0, &keyboard, &inputs);
	mlx_loop(inputs.mlx_ad);
}