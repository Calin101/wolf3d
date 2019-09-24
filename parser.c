/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 17:49:29 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/24 18:22:04 by calin       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

int		count_lines(t_input *data)
{
	char	*line;
	int		i;

	i = -1;
	data->ymax = 0;
	while (get_next_line(data->fd, &line))
	{
		if (data->ymax == 0)
		{
			while (line[++i])
			{
				if (line[i] != '2' && line[i] != ' ')
					error(data);
			}
		}
		if (line[0] != '2' || line[ft_strlen(line) - 1] != '2')
			error(data);
		data->ymax++;
		ft_strdel(&line);
	}
	return (0);
}

void	count_totalnb(t_input *data)
{
	char	**tmp_tab;
	char	*line;
	int		count_nb;
	t_index	index;

	count_nb = 0;
	data->xmax = 0;
	index = (t_index){.i = 0, .j = 0};
	while (get_next_line(data->fd2, &line))
	{
		tmp_tab = ft_strsplit(line, ' ');
		count_nb = 0;
		index.i = 0;
		while (tmp_tab[index.i++])
			count_nb++;
		if (index.j != 0 && data->xmax != count_nb)
			error(data);
		data->totalnb += count_nb;
		data->xmax = count_nb;
		index.j++;
		ft_2dstrdel(&tmp_tab);
		ft_strdel(&line);
	}
}

void	assign_posplayer(t_input *data, t_index index, int count_y)
{
	data->posplayer.x = index.i + 0.5;
	data->posplayer.y = count_y + 0.5;
	if (data->posplayer.y + 1 >= data->ymax ||
	data->posplayer.y - 1 < 0)
		error(data);
	if (data->posplayer.x + 1 >= data->xmax ||
	data->posplayer.x - 1 < 0)
		error(data);
}

void	filltab(t_input *data, int check_player, double count_y)
{
	char	*line;
	char	**tmp_tab;
	t_index	index;

	index = (t_index){.i = 0, .j = 0};
	while (get_next_line(data->fd3, &line))
	{
		tmp_tab = ft_strsplit(line, ' ');
		index.i = 0;
		while (tmp_tab[index.i])
		{
			if (ft_atoi(tmp_tab[index.i]) == -1)
			{
				assign_posplayer(data, index, count_y);
				check_player += 1;
			}
			data->tab[index.j++] = ft_atoi(tmp_tab[index.i++]);
		}
		count_y++;
		ft_strdel(&line);
		ft_2dstrdel(&tmp_tab);
	}
	if (check_player != 1)
		error(data);
}

int		parse_file(t_input *data)
{
	int		i;
	int		index_last_line;

	i = 0;
	index_last_line = 0;
	count_lines(data);
	count_totalnb(data);
	if (!(data->tab = malloc(sizeof(int) * data->totalnb)))
		return (-1);
	filltab(data, 0, 0);
	index_last_line = data->totalnb - data->xmax;
	while (index_last_line < data->totalnb)
	{
		if (data->tab[index_last_line] != 2)
			error(data);
		index_last_line++;
	}
	return (0);
}
