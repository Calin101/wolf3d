/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_addline.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aducimet <aducimet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 20:15:35 by aducimet     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/29 18:16:38 by aducimet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_addline(char **tab, char *line, int size)
{
	char	**newtab;
	int		i;

	i = 0;
	if ((newtab = (char **)malloc(sizeof(char *) * (size + 2))) == NULL)
		return (0);
	while (i < size)
	{
		newtab[i] = ft_strdup(tab[i]);
		i++;
	}
	newtab[i] = ft_strdup(line);
	newtab[i + 1] = NULL;
	return (newtab);
}
