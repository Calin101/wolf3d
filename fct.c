/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fct.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/09 16:10:44 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/09/14 17:57:27 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolfalgo.h"

void clear_im(t_input *data)
{
        int i;

        i = -1;
        while (++i <= data->win_h * data->win_w)
        {
                data->im.tab[i] = 0;
        }
}

int tallnomin(int a, int b)
{
    int e;
    int r;

    e = a;
    r = b;
    if (a < 0)
        a *= -1;
    if (b < 0)
        b *= -1;
    if (a >= b)
        return (a);
    return (b);
}

void print_line(t_input *input, t_dot a, t_dot b, int color)
{
    double dx;
    double dy;
    int tall;
    int i;

    i = 0;
    printf("1\n");
    //printf("-----%d   %d---------%d   %d-----\n", a.x, a.y, b.x, b.y);
    if (b.x == a.x && b.y  == a.y)
        return;
    tall = tallnomin(a.y - b.y, a.x - b.x);
    dx = (double)(a.x - b.x) / tall;
    dy = (double)(a.y - b.y) / tall;

    while (i++ < tall)
	{
		if ((i * dx + b.x) >= 0 && (i * dx + b.x) < input->win_w &&
	(i * dy + b.y) < input->win_h && (i * dy + b.y) >= 0)
			input->im.tab[((int)(i * dx + b.x) +
	(int)(i * dy + b.y) * (input->im.size_line / 4))] = color;
	}
    printf("2\n");
}

double    ft_modulo(double nbr, double mod)
{
   return (nbr - (int)(nbr / mod) * mod -\
            (mod < 0 ? mod : 0));
}