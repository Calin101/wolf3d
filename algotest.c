/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   algotest.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/10 19:27:54 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/16 16:16:40 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolfalgo.h"

void    create_thread(t_input *input)
{
        int i;
		double alpha; 

    	alpha = input->dirplayer - input->fov / 2;
        i = 0;
		clear_im(input);;
        while (i < NB_THREAD)
        {
			while(alpha < (input->dirplayer - input->fov / 2) + ((double)((float)i / (float)NB_THREAD) * input->fov))
			{
				alpha +=  input->step_ray - (alpha +
				input->step_ray > M_PI * 2 ? 2 * M_PI : 0);
            //	printf("i = %d			ALPHA = %lf		Alp = %lf\n", i, alpha, ((input->dirplayer - input->fov / 2) + (double)(((float)i / (float)NB_THREAD) * input->fov)));
			}
            input->thread_tab[i].alpha = alpha;
            input->thread_tab[i].start = (i *  input->win_w) / NB_THREAD;
            //printf("i = %d\n", (i *  input->win_w) / NB_THREAD);
            input->thread_tab[i].end = ((i + 1) * (input->win_w)) / NB_THREAD;
            //printf("i = %d\n", ((i + 1) * (input->win_w)) / NB_THREAD);
            input->thread_tab[i].inputs = input;
            pthread_create(&input->thread_tab[i].thread, NULL, &printscreen, &input->thread_tab[i]);
            i++;
        }
        i = 0;
        while (i <= NB_THREAD)
                pthread_join(input->thread_tab[i++].thread, NULL);
		//print_line(input, (t_dot){.x = input->posplayer.x * 50, .y = input->posplayer.y * 50}, (t_dot){.x = (input->posplayer.x + cos(input->dirplayer)) * 50, .y = (input->posplayer.y + -sin(input->dirplayer)) * 50}, 0xFF0000);
		mlx_put_image_to_window(input->im.tab, input->win_ad, input->im.ad, 0, 0);
}

double	dist(t_fdot p1, t_fdot p2)
{
	return(sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
}

int	colli(t_input *inputs, t_fdot dot, t_thread *thread)
{
	//dprintf(1, "%d\n", (int)dot.y * inputs->xmax + (int)dot.x);
	/* VERIFICATION SI X OU Y EST AU MILIEU D'UN CARRE */
	//dprintf(1, "111111      DOT X %f      DOT Y %f                   I %D\n", dot.x, dot.y, count);
	if (dot.x - (int)dot.x == 0)
		dot.x += (thread->alpha < M_PI_2 || thread->alpha > inputs->_3pi_2) ? 0 : -1;
	if (dot.y - (int)dot.y == 0)
		dot.y += (thread->alpha < M_PI) ? -1 : 0;
	//printf("%d\n", inputs->xmax);
	if (dot.x < 0 || dot.y < 0 || dot.x > inputs->xmax || dot.y > inputs->ymax)
		return(0);

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
	if (inputs->tab[((int)dot.y) * inputs->xmax + (int)dot.x] == 2)
	{
		thread->text = 2;
		return(1);
	}
	if	(inputs->tab[((int)dot.y) * inputs->xmax + (int)dot.x] == 3)
	{
		thread->text = 3;
		return (1);
	}
	else
		return (0);
}

void	printline(t_input *inputs, t_fdot closest, t_thread *thread)
{
	double	height;
	double	wallmin;
	double	wallmax;
	int		color = 0X0FFF00;
	double ret = 0;
	int i = 0;

	height = 0;
	if (closest.x == -1 && closest.y == -1)
	{
		height = 0;
		wallmin = inputs->win_h / 2 - height;
		wallmax = inputs->win_h / 2 + height;
	}
	else 
	{  
		ret = dist(inputs->posplayer, closest);
		if (ret != 0)
		{
			height = (double)inputs->wall_size / (dist(inputs->posplayer, closest) * cos(thread->inputs->dirplayer - thread->alpha));
			wallmin = inputs->win_h / 2 - height;
			wallmax = inputs->win_h / 2 + height;
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
	i = -1;

	while (++i < inputs->win_h)
	{
		if (i <= wallmin)
			inputs->im.tab[i * inputs->win_w + thread->index] = 0x0000FF;
		else if (i <= wallmax)
			inputs->im.tab[i * inputs->win_w + thread->index] = color;
		else
			inputs->im.tab[i * inputs->win_w + thread->index] = 0xFFFFFF;
	}
}

int	ray(t_input *inputs, t_thread *thread)
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
			dx += thread->alpha < M_PI / 2 || thread->alpha > inputs->_3pi_2 ? 1 : -1;
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
			return(0);

		}
	}
	printline(inputs, closest, thread);
	return (1);
}


void *printscreen(void *thread)
{
	raycasting((t_thread*)thread);
	//printf("thread\n");
	return(0);
}
int raycasting(t_thread *thread)
{
	int i;
//	printf("RQYCQSTING\n");
    i = thread->start - 1;
    //thread->alpha = thread->inputs->dirplayer - thread->inputs->fov / 2;
	if (thread->alpha < 0)
		thread->alpha += 2 * M_PI;
	//printf("RAY2\n");
	//printf("NOMBRE DE RAYON %f\n", inputs->fov * inputs->win_w);
	//printf("STEP RAY %f\n", inputs->step_ray);
   
   
	while(thread->end > ++i)
	{

		//printf("RAY3\n");
		thread->index = i;
		thread->ray.a = -tan(thread->alpha);
		thread->ray.b = thread->inputs->posplayer.y - thread->ray.a * thread->inputs->posplayer.x;
		ray(thread->inputs, thread);
		//printf("RAY          A {%lf}                 B {%lf}		alpha = {%lf}\n", thread->ray.a, thread->ray.b, thread->alpha);
		//printf("A %f B %f\n", inputs->ray.a, inputs->ray.b);
        thread->alpha +=  thread->inputs->step_ray - (thread->alpha + thread->inputs->step_ray > M_PI * 2 ? 2 * M_PI : 0);
	}

   
   
   
   
   
   
   
    /*while (inputs->index < inputs->win_w)
    {
        //printf("dir %f fov %f alpha %f, STEP %f\n", inputs->dirplayer, inputs->fov, inputs->alpha, inputs->step_ray);
		
		inputs->ray.a = -tan(inputs->alpha);
		inputs->ray.b = inputs->posplayer.y - inputs->ray.a * inputs->posplayer.x;
		ray(inputs);
		//printf("RAY          A {%f}                 B {%f}\n", inputs->ray.a, inputs->ray.b);
		//printf("A %f B %f\n", inputs->ray.a, inputs->ray.b);
        inputs->alpha +=  inputs->step_ray - (inputs->alpha + inputs->step_ray > M_PI * 2 ? 2 * M_PI : 0);
        inputs->index++;
    }*/
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
    inputs->step_ray = inputs->fov / inputs->win_w;
    inputs->im.ad = mlx_new_image(inputs->mlx_ad, inputs->win_w, inputs->win_h);
    inputs->im.tab = (int *)mlx_get_data_addr(inputs->im.ad, &(inputs->im.bits_per_pixel), &(inputs->im.size_line), &(inputs->im.endian));
    return(1);
}

void	clearall(t_input *inputs)
{
	mlx_destroy_image(inputs->mlx_ad, inputs->im.ad);
	mlx_destroy_window(inputs->mlx_ad, inputs->win_ad);
	free(inputs->tab);
	free(inputs->tab_line);
	exit(EXIT_SUCCESS);
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
	//mlx_clear_window(inputs->mlx_ad, inputs->win_ad);
		//mlx_destroy_image(inputs->im.tab, inputs->win_ad);
		//dprintf(1, "input2\n");
		//free(&inputs->im);
	if (key == KEY_RIGHT)
    {
		//dprintf(1, "KEY LEFT\n");
        inputs->dirplayer += 0.1 + (inputs->dirplayer + 0.1 > 2 * M_PI ? -2 * M_PI : 0);
    }
	if (key == KEY_P)
	{
		printf("POS PLAYER  X %lf		Y %lf\n", inputs->posplayer.x, inputs->posplayer.y);
	}
    if (key == KEY_LEFT)
        inputs->dirplayer +=  (- 0.1 + (inputs->dirplayer + 0.1 < 0 ? 2 * M_PI : 0));
	if (key == KEY_ESCAPE)
		clearall(inputs);
	inputs->index = 0;
	create_thread(inputs);
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
	printf("1\n");
    parse_file(&inputs);
	printf("2\n");
	//dprintf(1, "totalnb {%d}\n", inputs.totalnb);
	/*while(i < inputs.totalnb)
	{
		dprintf(1, "tab [%d]                 i = %d\n", inputs.tab[i], i);
		i++;
	}*/
    //printf("x %f y %f z %f\n", inputs.player_pos.x, inputs.player_pos.y, inputs.player_pos.z);
    init_var(&inputs);
	printf("3\n");
    create_thread(&inputs);
	printf("4\n");
	mlx_put_image_to_window(inputs.im.tab, inputs.win_ad, inputs.im.ad, 0, 0);
    mlx_hook(inputs.win_ad, 2, 0, &ft_keyboard, &inputs);
	printf("5\n");
    mlx_loop(inputs.mlx_ad);
	printf("6\n");
    return (0);
}