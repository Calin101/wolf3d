/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 17:49:29 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 15:18:21 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "wolfalgo.h"

int		count_lines(t_input *data)
{
	char	*line;

	data->countline = 0;
	while (get_next_line(data->fd, &line))
	{
		data->countline++;
		ft_strdel(&line);
	}
	if (!(data->tab_line = malloc(sizeof(int) * data->countline)))
		return (-1);
	//data->tab_line[data->countline] = 0;
	return (0);
}

void	fill_tab_line(t_input *data)
{
	char	**tmp_tab;
	char	*line;
	int		count_nb;
	t_index	index;

	count_nb = 0;
	index = (t_index){.i = 0, .j = 0};
	while (get_next_line(data->fd2, &line))
	{
		tmp_tab = ft_strsplit(line, ' ');
		count_nb = 0;
		index.i = 0;
		while (tmp_tab[index.i++])
			count_nb++;
		data->tab_line[index.j] = count_nb;
		index.j++;
		ft_2dstrdel(&tmp_tab);
		ft_strdel(&line);
	}
}

void	filltab(t_input *data)
{
	char	*line;
	char	**tmp_tab;
	double	count_y;
	t_index	index;

	index = (t_index){.i = 0, .j = 0};
	count_y = 0;
	while (get_next_line(data->fd3, &line))
	{
		tmp_tab = ft_strsplit(line, ' ');
		index.i = 0;
		while (tmp_tab[index.i])
		{
			if (ft_atoi(tmp_tab[index.i]) == 1)
			{
				data->player_pos.x = index.i;
				data->player_pos.y = count_y;
				data->player_pos.z = 0.75;
			}
			data->tab[index.j++] = ft_atoi(tmp_tab[index.i++]);
		}
		count_y++;
		ft_strdel(&line);
		ft_2dstrdel(&tmp_tab);
	}
}

int		parse_file(t_input *data)
{
	char	*line;
	char	**tmp_tab;
	int		i;

	i = 0;
	count_lines(data);
	fill_tab_line(data);
	data->xmax = 0;
	data->ymax = 0;
	while (i < data->countline)
	{
		if (data->xmax < data->tab_line[i])
			data->xmax = data->tab_line[i];
		data->totalnb += data->tab_line[i++];
	}
	data->ymax = i;
	printf(" x max {%d} y max {%d}\n", data->xmax, data->ymax);
	if (!(data->tab = malloc(sizeof(int) * data->totalnb)))
		return (-1);
	data->tab[data->totalnb] = 0;
	filltab(data);
	return (0);
}