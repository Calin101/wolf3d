/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   algo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/09 16:09:57 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/09/10 18:51:50 by mwaterso    ###    #+. /#+    ###.fr     */
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

void printcol(int i, double dist, t_input *inputs, int color)
{
        double div;

        //printf("==PRINT==\n");
        (void)color;
        div = inputs->scale - dist;
        //printf("%lf                   %lf\n", div, dist);
//      print_line(inputs, (t_dot){.x = (i % inputs->win_w), .y = inputs->win_h * (double)(1 / div)},
//      (t_dot){.x = (i % inputs->win_w), .y = (double)(inputs->win_h * (double)((div - 1) / div))}, 0xFFFF00);

        print_line(inputs, (t_dot){.x = (i % inputs->win_w), .y = inputs->win_h / 2 + (inputs->wall_size / dist)},
        (t_dot){.x = (i % inputs->win_w), .y = inputs->win_h / 2 - (inputs->wall_size / dist)}, 0xFFFF00);
//      printf("----%d          %d                              %d              %d-----\n", (i % inputs->win_w), (int)(inputs->win_h * (double)(1 / div)), (i % inputs->win_w), (int)(inputs->win_h * (double)((div - 1) / div)));
}

int colli(double x, double y, t_input *inputs)
{
        long yesy;

        //printf("---%lf                %lf---\n", x, y);

        if (x >= inputs->xmax || x < (double)(0) || y >= inputs->ymax || y < (double)(0)  /* z >= inputs->zmax*/)
                return (-1);
        if ((yesy = findex((y), inputs->tab_line, inputs->totalnb)) < 0)
                return (-1);
        //printf("_-_-_-|  %d    |-_-_-_\n", (long)(x) + yesy);
//      printf("------%d\n", inputs->tab[(long)(x) + yesy]);
        return (inputs->tab[(long)(x) + yesy]);
}

int raytocol(long index, t_input *inputs, t_fdot rot, t_fdot dot)
{
        int i;
        double k;
        int text;
        //printf("rot = %lf             %lf             %lf\n", rot.x, rot.y, rot.z);
        //sleep(1);
        i = -1;
        k = 0;
        text = 0;

        while ((text = colli(dot.x, dot.y, inputs)) >= 0 && ++i < inputs->render)
        {
                //printf("%d\n", text);
                if (text == 2)
                {
                        printcol(index, k * i + 1, inputs, 0x0000FF);
                        return(0);
                }

                if (dot.x < 0)
                        dot.x = (int)(dot.x) + (cos(rot.x) > 0 ? 0 : -1);
                else
                        dot.x = (int)(dot.x) + (cos(rot.x) > 0 ? 1 : 0);


                if (dot.y < 0)
                        dot.y = (int)(dot.y) + (sin(rot.x) > 0 ? 0 : -1);
                else
                        dot.y = (int)(dot.y) + (sin(rot.x) > 0 ? 1 : 0);
                k = (dot.x - inputs->player_pos.x) / (cos(rot.x) == 0 ? 0.000001 : cos(rot.x));
                if (fabs((dot.y - inputs->player_pos.y) / (sin(rot.x) == 0 ? 0.00001 : sin(rot.x))) < fabs(k))
                        k = (dot.y - inputs->player_pos.y) / (sin(rot.x) == 0 ? 0.00001 : sin(rot.x));
                dot.x = cos(rot.x) * k + inputs->player_pos.x;
                dot.y = sin(rot.x) * k + inputs->player_pos.y;
        }
        /* if (text == 0)
                printcol(index, (k + 1) * 2, inputs, 0xFFFFFF);
        if (text == 2)
                printcol(index, (k + 1) * 2, inputs, 0x0000FF);
        if (text == 1)
                printcol(index, (k + 1) * 2, inputs, 0xFF0000);*/
        return (0);
}


void ray(t_thread *thread)
{
        int i;

        i = thread->start - 1;
        //printf("THREAD START [%ld] END [%ld]       I = [%d]\n", thread->start, thread->end, i);
        //printf("start = %ld end = %ld\n", thread->start, thread->end);
        while (++i < thread->end)
        {
                //printf("%d\n", i);
               //  if (i / thread->inputs->win_w > 385 && i % thread->inputs->win_h > 240 && i % thread->inputs->win_h < 250 && i / thread->inputs->win_w < 389)
              //          thread->inputs->debug = 1;
              //  else
               //         thread->inputs->debug = 0;
                //printf("---------------%d    %d----------------\n", i % thread->inputs->win_h, i / thread->inputs->win_w);
                //thread->inputs->im.tab[i] = raytocol(thread->inputs, (t_dot){.x = (double)(thread->inputs->rotplayer.x + (double)(thread->inputs->rotscreen.zmin * (double)(((double)(i % thread->inputs->win_h)) / thread->inputs->win_h)) - ((double)(thread->inputs->rotscreen.zmin / 2))),
                //.y = (double)(thread->inputs->rotplayer.y + (double)(thread->inputs->rotscreen.zmax * ((double)((double)(i / thread->inputs->win_w) / thread->inputs->win_w)) - ((double)(thread->inputs->rotscreen.zmax / 2)))), .z = 0}, thread->inputs->player_pos);
				//printf("%lf\n", (double)(thread->inputs->rotplayer.x + (double)(thread->inputs->rotscreen.zmin * (double)(((double)(i % thread->inputs->win_w)) / thread->inputs->win_w)) - ((double)(thread->inputs->rotscreen.zmin / 2))));
		printf("%f %f %f\n", thread->inputs->player_pos.x, thread->inputs->player_pos.y, thread->inputs->player_pos.z);
                raytocol(i, thread->inputs, (t_fdot){.x = (double)(thread->inputs->rotplayer.x + (double)(thread->inputs->rotscreen.zmin *
                (double)(((double)(i % thread->inputs->win_w)) / thread->inputs->win_w)) - ((double)(thread->inputs->rotscreen.zmin / 2))),
                .y = 0, .z = 0}, thread->inputs->player_pos);
                //printf("%lf\n", (double)(thread->inputs->rotplayer.x + (double)(thread->inputs->rotscreen.zmin * (double)(((double)(i % thread->inputs->win_w)) / thread->inputs->win_w)) - ((double)(thread->inputs->rotscreen.zmin / 2))));
        }
}

void *raytracing(void *t)
{
        ray((t_thread *)t);
        return(0);
}

void    create_thread(t_input *input)
{
        int i;

        i = 0;
        while (i < NB_THREAD)
        {
                //printf("i = %d\n", i);
                input->thread_tab[i].start = (i *  input->win_w) / NB_THREAD;
                //printf("i = %d\n", (i *  input->win_w) / NB_THREAD);
                input->thread_tab[i].end = ((i + 1) * (input->win_w)) / NB_THREAD;
                //printf("i = %d\n", ((i + 1) * (input->win_w)) / NB_THREAD);
                input->thread_tab[i].inputs = input;
                pthread_create(&input->thread_tab[i].thread, NULL, &raytracing, &input->thread_tab[i]);
                i++;
        }
        i = 0;
        while (i <= NB_THREAD)
                pthread_join(input->thread_tab[i++].thread, NULL);
}

void wolf(t_input *inputs)
{
        //mlx_clear_window(inputs->mlx_ad, inputs->win_ad);
        clear_im(inputs);
        create_thread(inputs);
        //raytracing(inputs);
        mlx_put_image_to_window(inputs->mlx_ad, inputs->win_ad, inputs->im.ad, 0, 0);
}

int var_init(t_input *inputs)
{

        inputs->win_w = 1000;
        inputs->win_h = 1000;
        inputs->render = 1000;
        inputs->scale = 1000;
        inputs->rotscreen.zmax = M_PI_4;        /*              ecart omega y           */
        inputs->rotscreen.zmin = M_PI_4;        /*              ecart omega x           */
        inputs->rotplayer.x = 0;
        //printf("ici?\n");
        inputs->rotplayer.y = M_PI_2;
        inputs->rotplayer.z = 3 * M_PI_2;
        //printf("RSCREEN MAX {%f}          RSCREEN MIN {%f}          ROTPLAYER Y {%f}           ROTPLAYER Z {%f}\n", inputs->rotscreen.zmax, inputs->rotscreen.zmin, inputs->rotplayer.y, inputs->rotplayer.z);
        inputs->zmax = 1.2;
        inputs->k = 0;
        inputs->wall_size = 500;
        //printf("ici2?\n");
        inputs->mlx_ad = mlx_init();
        //printf("ici3?\n");
        inputs->win_ad = mlx_new_window(inputs->mlx_ad, inputs->win_w, inputs->win_h, "Wolf3d");
        //printf("ici4?\n");
        inputs->im.ad = mlx_new_image(inputs->mlx_ad, inputs->win_w, inputs->win_h);
        //printf("ici5?\n");
        inputs->im.tab = (int *)mlx_get_data_addr(inputs->im.ad, &(inputs->im.bits_per_pixel), &(inputs->im.size_line), &(inputs->im.endian));
        //printf("ici6?\n");


        return (1);
}

int keyboard(int key, t_input *inputs)
{
        if (key == KEY_P)
                printf("AFTER = %lf             %lf             %lf\n", inputs->rotplayer.x, inputs->rotplayer.y, inputs->rotplayer.z);
    	/*if (key == KEY_LEFT)
                inputs->rotplayer.x -= M_PI / 100;
        if (key == KEY_RIGHT)
                inputs->rotplayer.x += M_PI / 100;
        if (key == KEY_UP)
                inputs->rotplayer.y -= M_PI / 100;
        if (key == KEY_DOWN)
                inputs->rotplayer.y += M_PI / 100;*/
		//if (key == KEY_LEFT)
                //inputs->direplayer += 0.05;
       // if (key == KEY_RIGHT)
                //inputs->dirplayer -= 0.05;
        if (key == KEY_PAD_5)
        {
                inputs->player_pos.x += 0.05;
        //      inputs->k += 0.01;
        //      inputs->player_pos.x = cos(inputs->rotplayer.x) * inputs->k + inputs->player_pos.x;
        //      inputs->player_pos.y = sin(inputs->rotplayer.x) * inputs->k + inputs->player_pos.y;
        //      inputs->player_pos.z = cos(inputs->rotplayer.y) * inputs->k + inputs->player_pos.z;
         }
        if (key == KEY_PAD_2)
        {
                inputs->player_pos.x -= 0.05;
        //      inputs->k -= 0.01;
        //      inputs->player_pos.x = cos(inputs->rotplayer.x) * inputs->k + inputs->player_pos.x;
        //      inputs->player_pos.y = sin(inputs->rotplayer.x) * inputs->k + inputs->player_pos.y;
        //      inputs->player_pos.z = cos(inputs->rotplayer.y) * inputs->k + inputs->player_pos.z;
        }
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
        //printf("parse\n");
        parse_file(&inputs);
        //printf("varinit\n");
        var_init(&inputs);
        //printf("wolf\n");
        wolf(&inputs);
        //return(1);
        /*int i;

        i = -1;
        while (++i < (inputs.win_h * inputs.win_w))
        {
                printf("%d\n", i);
                printf("x =     %lf\n", (double)(inputs.rotplayer.x + (double)(inputs.rotscreen.zmin * (double)(((double)(i % inputs.win_h)) / inputs.win_h)) - ((double)(inputs.rotscreen.zmin / 2))));
                printf("y =                             %lf\n", (double)(inputs.rotplayer.y + (double)(inputs.rotscreen.zmax * ((double)((double)(i / inputs.win_w) / inputs.win_w)) - ((double)(inputs.rotscreen.zmax / 2)))));
        }*/
        mlx_hook(inputs.win_ad, 2, 0, &keyboard, &inputs);
        mlx_loop(inputs.mlx_ad);
}