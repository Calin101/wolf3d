/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_percent.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/06 05:14:54 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 08:24:29 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

double		ft_get_percent(double start, double current, double end)
{
	double	placement;
	double	distance;

	distance = end - start;
	placement = current - start;
	return (distance == 0 ? 1 : placement / distance);
}
