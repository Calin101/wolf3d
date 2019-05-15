/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_tabint.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 15:10:30 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 14:53:30 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tabint(int ***tab_int)
{
	int i;

	i = 0;
	if (*tab_int)
	{
		while ((*tab_int)[i])
			free((*tab_int)[i++]);
		free(*tab_int);
		(*tab_int) = NULL;
	}
}
