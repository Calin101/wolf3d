/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   algotest.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 15:53:43 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/09/09 20:51:46 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "wolfalgo.h"

double	dist(t_fdot p1, t_fdot p2)
{
	return(sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
}

int	colli(t_input *inputs, t_fdot dot)
{
	//dprintf(1, "%d\n", (int)dot.y * inputs->xmax + (int)dot.x);
	/* VERIFICATION SI X OU Y EST AU MILIEU D'UN CARRE */
	//dprintf(1, "111111      DOT X %f      DOT Y %f                   I %D\n", dot.x, dot.y, count);
	//printf("%d\n", inputs->xmax);
	if (dot.x - (int)dot.x == 0)
		dot.x += (inputs->alpha < M_PI_2 || inputs->alpha > inputs->_3pi_2) ? 0 : -1;
	if (dot.y - (int)dot.y == 0)
		dot.y += (inputs->alpha < M_PI) ? -1 : 0;

	/****************************************************/
	//dprintf(1, "IN TAB [%d]\n", inputs->tab[(int)dot.y * inputs->xmax + (int)dot.x]);
	//dprintf(1, "xmax %d\n", inputs->xmax);
	//dprintf(1, " POS PLAYER X %f Y %f\n", inputs->posplayer.x, inputs->posplayer.y);
	//dprintf(1, " return %d\n", (inputs->tab[(int)dot.y * inputs->xmax + (int)dot.x] == 2 ? 1 : 0));
	//sleep(1);
	/* if (inputs->alpha > 0 && inputs->alpha < M_PI)
		dot.y = (int)inputs->posplayer.y - 1;
	else
		dot.y = (int)inputs->posplayer.y;*/
	if (inputs->tab[((int)dot.y) * inputs->xmax + (int)dot.x] == 2 ||\
		inputs->tab[((int)dot.y) * inputs->xmax + (int)dot.x] == 3)
	{
		return (1);
	}
	else
		return (0);
}

void	printline(t_input *inputs, t_fdot closest)
{
	double	height;
	double	wallmin;
	double	wallmax;
	int		color = 0X0FFF00;
	int ret = 0;
	int i = 0;

	height = 0;
	//dprintf(1, " DOT =                 PLAYER[x %f y %f]                           CLOSEST[x %f y %f]\n", inputs->posplayer.x, inputs->posplayer.y, closest.x, closest.y);
	ret = dist(inputs->posplayer, closest);
	if (ret != 0)
	{
		height = inputs->wall_size / dist(inputs->posplayer, closest);
		wallmin = inputs->win_h / 2 - height;
		wallmax = inputs->win_h / 2 + height;
	}
	else
	{
		//dprintf(1, " POS PLAYER {x %f y %f}              CLOSEST {x %f y %f}\n", inputs->posplayer.x, inputs->posplayer.y, closest.x, closest.y);
		wallmax = inputs->win_h;
		wallmin = 0;
	}
	//dprintf(1, " DIST %f               HEIGHT %f\n", dist(inputs->posplayer, closest), height);
	//dprintf(1, "\nWALLMAX %f                                             %f WALLMIN\n", wallmax, wallmin);
	//sleep(1);
	//dprintf(1, "%d\n", inputs->tab[(int)closest.y * inputs->xmax + (int)closest.x] == 2);
	if (inputs->tab[(int)closest.y * inputs->xmax + (int)closest.x] == 3)
		color = 0xFF0000;
	else if (inputs->tab[(int)closest.y * inputs->xmax + (int)closest.x] == 2)
		color = 0x0FFF00;
	i = wallmax;
		//printf("    wallmax %f      i = %d     wallmin %f\n", wallmax, i, wallmin);
	while (i > wallmin)
	{
		inputs->im.tab[i * inputs->win_w + inputs->index] = color;
		i--;
	}
	i = wallmax;
	while (i <= inputs->win_h)
	{
		inputs->im.tab[i * inputs->win_w + inputs->index] = 0xFFFFFF;
		i++;
	}
	i = wallmin;
	while (i >= 0)
	{
		inputs->im.tab[i * inputs->win_w + inputs->index] = 0x0000FF;
		i--;
	}
	/*else if (inputs->tab[(int)closest.y * inputs->xmax + (int)closest.x] == 0)
	{
		i = wallmax;
		while (i > 0)
		{
			inputs->im.tab[i * inputs->win_w + inputs->index] = 0x00FFFF;
			i--;
		}
	}*/
	//dprintf(1, "HEIGHT %f B %d H %d\n", height, (int)b, (int)h);
}

int	ray(t_input *inputs)
{
	t_fdot	p1;
	t_fdot	p2;
	int		dx;
	int		dy;
	t_fdot	closest;
	//int i = 0;

	dx = 0;
	dy = 0;
	//printf("ALP %f\n", inputs->alpha);
	//inputs->alpha = modulo2pi(inputs->alpha);
	closest = (t_fdot){.x = inputs->posplayer.x, .y = inputs->posplayer.y};
	//dprintf(1, "DIST 1 [%f]                         DIST 2 [%f]\n", dist1, dist2);
	while (colli(inputs, closest) == 0)
	{
		if (inputs->alpha > 0 && inputs->alpha < M_PI)
			p2.y = (int)inputs->posplayer.y + dy;
		else
			p2.y = (int)inputs->posplayer.y + 1 + dy;
		if (inputs->alpha > M_PI_2 && inputs->alpha < inputs->_3pi_2)
			p1.x = (int)inputs->posplayer.x + dx;
		else
			p1.x = (int)inputs->posplayer.x + 1 + dx;
		p1.y = inputs->ray.a * p1.x + inputs->ray.b;
		p2.x = (p2.y - inputs->ray.b) / inputs->ray.a;
		//dprintf(1, "POSPLAYER X %f Y %f\n", inputs->posplayer.x, inputs->posplayer.y);
		//dprintf(1, "       P1 [x %f y %f]             P2 [x %f y %f]\n", p1.x, p1.y, p2.x, p2.y);
		//sleep(1);
		if (dist(inputs->posplayer, p1) < dist(inputs->posplayer, p2))
		{
			dx += inputs->alpha < M_PI / 2 || inputs->alpha > inputs->_3pi_2 ? 1 : -1;
			closest = p1;                       
			dprintf(1, "DX %d	ALPHA %lf\n", dx, inputs->alpha / M_PI);
		}
		else
		{
			dy += inputs->alpha < M_PI ? -1 : 1;
			closest = p2;
			dprintf(1, "DY %d	ALPHA %lf\n", dy, inputs->alpha / M_PI);
		}
	}
	printf("A = %lf		B = %lf\n", inputs->ray.a, inputs->ray.b);
	//dprintf(1, "CLOSEST x %f         y %f\n", closest.x, closest.y);
	dprintf(1, "X %f\tY %f\n", closest.x, closest.y);
	printline(inputs, closest);
	mlx_put_image_to_window(inputs->im.tab, inputs->win_ad, inputs->im.ad, 0, 0);
	//printf("return = %f\n", dist(p1, p2));
//	printf("P1{x %f y %f}                P2{x %f y %f}\n", p1.x, p1.y, p2.x, p2.y);
	return (1);
}
int raycasting(t_input *inputs)
{
    //int i;

    //i = 0;
    inputs->alpha = inputs->dirplayer - inputs->fov / 2;
	if (inputs->alpha < 0)
		inputs->alpha += 2 * M_PI;
    inputs->step_ray = inputs->fov / inputs->win_w;
	//printf("NOMBRE DE RAYON %f\n", inputs->fov * inputs->win_w);
	//printf("STEP RAY %f\n", inputs->step_ray);
	//printf("ALPHA %f               INPUTS->INDEX %d\n", inputs->alpha, inputs->index);
    while (inputs->index < inputs->win_w)
    {
        //printf("dir %f fov %f alpha %f, STEP %f\n", inputs->dirplayer, inputs->fov, inputs->alpha, inputs->step_ray);
		
		inputs->ray.a = -tan(inputs->alpha);
		inputs->ray.b = inputs->posplayer.y - inputs->ray.a * inputs->posplayer.x;
		ray(inputs);
		//printf("RAY          A {%f}                 B {%f}\n", inputs->ray.a, inputs->ray.b);
		//inputs->ray.a = inputs->posplayer.x;
		//inputs->ray.b = inputs->posplayer.y;
		//printf("A %f B %f\n", inputs->ray.a, inputs->ray.b);
        inputs->alpha +=  inputs->step_ray - (inputs->alpha + inputs->step_ray > M_PI * 2 ? 2 * M_PI : 0);
        inputs->index++;
    }
    return (1);
}

int init_var(t_input *inputs)
{
	inputs->index = 0; 
    inputs->fov = M_PI / 2;
    inputs->dirplayer = M_PI / 2;
    inputs->win_w = 700;
    inputs->win_h = 700;
	inputs->_3pi_2 = M_PI_2 * 3;
	inputs->wall_size = 150;
    inputs->mlx_ad = mlx_init();
    inputs->win_ad = mlx_new_window(inputs->mlx_ad, inputs->win_w, inputs->win_h, "Wolf3d");
    inputs->im.ad = mlx_new_image(inputs->mlx_ad, inputs->win_w, inputs->win_h);
    inputs->im.tab = (int *)mlx_get_data_addr(inputs->im.ad, &(inputs->im.bits_per_pixel), &(inputs->im.size_line), &(inputs->im.endian));
    return(1);
}

void	refresh(t_input *inputs)
{
	//mlx_clear_window(inputs->im.tab, inputs->win_ad);
	mlx_destroy_image(inputs->im.tab, inputs->win_ad);
	//inputs->im.ad = mlx_new_image(inputs->mlx_ad, inputs->win_w, inputs->win_h);
    //inputs->im.tab = (int *)mlx_get_data_addr(inputs->im.ad, &(inputs->im.bits_per_pixel), &(inputs->im.size_line), &(inputs->im.endian));
}

int ft_keyboard(int key, t_input *inputs)
{
    if (key == KEY_PAD_8)
        inputs->posplayer.x += 0.25;
    if (key == KEY_PAD_5)
        inputs->posplayer.x -= 0.25;
    if (key == KEY_PAD_4)
        inputs->posplayer.y += 0.25;
    if (key == KEY_PAD_6)
        inputs->posplayer.y -= 0.25;
		//dprintf(1, "input\n");
		//refresh(inputs);
	mlx_clear_window(inputs->mlx_ad, inputs->win_ad);
		//mlx_destroy_image(inputs->im.tab, inputs->win_ad);
		//dprintf(1, "input2\n");
		//free(&inputs->im);
	if (key == KEY_LEFT)
    {
		//dprintf(1, "KEY LEFT\n");
        inputs->dirplayer += 0.1 + (inputs->dirplayer + 0.1 > 2 * M_PI ? -2 * M_PI : 0);
    }
    if (key == KEY_RIGHT)
        inputs->dirplayer +=  (- 0.1 + (inputs->alpha + 0.1 < 0 ? 2 * M_PI : 0));
	inputs->index = 0;
	raycasting(inputs);
    return(1);
}

int main(int argc, char ** argv)
{
    t_input inputs;
	//int i = 0;

	(void)argc;
    inputs.fd = open(argv[1], O_RDONLY);
    inputs.fd2 = open(argv[1], O_RDONLY);
    inputs.fd3 = open(argv[1], O_RDONLY);
    parse_file(&inputs);
	//dprintf(1, "totalnb {%d}\n", inputs.totalnb);
	/*while(i < inputs.totalnb)
	{
		dprintf(1, "tab [%d]                 i = %d\n", inputs.tab[i], i);
		i++;
	}*/
    //printf("x %f y %f z %f\n", inputs.player_pos.x, inputs.player_pos.y, inputs.player_pos.z);
    init_var(&inputs);
    raycasting(&inputs);
    mlx_hook(inputs.win_ad, 2, 0, &ft_keyboard, &inputs);
    mlx_loop(inputs.mlx_ad);
    return (0);
}