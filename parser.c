/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 17:49:29 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 22:17:18 by calin       ###    #+. /#+    ###.fr     */
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
		printf("%zu\n", ft_strlen(line));
		if (ft_strlen(line) <= 1)
		{
			ft_putendl("Error empty file");
			exit(1);
		}
		data->countline++;
		ft_strdel(&line);
	}
	data->ymax = data->countline;
	return (0);
}

void	fill_tab_line(t_input *data)
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
		{
			ft_putendl("Error size line in map file");
			sleep(5);
			exit(1);
		}
		data->totalnb += count_nb;
		data->xmax = count_nb;
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

	count_y = 0;
	index = (t_index){.i = 0, .j = 0};
	while (get_next_line(data->fd3, &line))
	{
		tmp_tab = ft_strsplit(line, ' ');
		index.i = 0;
		while (tmp_tab[index.i])
		{
			if (ft_atoi(tmp_tab[index.i]) == -1)
			{
				data->posplayer.x = index.i;
				data->posplayer.y = count_y;
			}
			data->tab[index.j++] = ft_atoi(tmp_tab[index.i++]);
		}
		count_y++;
		ft_strdel(&line);
		ft_2dstrdel(&tmp_tab);
	}
}

void	fill_texture_tab(t_input *data)
{
	data->name_text[0] = "texture/titi.xpm";
	data->name_text[1] = "texture/text.xpm";
	data->name_text[2] = "texture/mwaterso.xpm";
	data->name_text[3] = "texture/wall.xpm";
	data->name_text[4] = "texture/wall2.xpm";
}

int		parse_file(t_input *data)
{
	int		i;

	i = 0;
	count_lines(data);
	fill_tab_line(data);
	if (!(data->tab = malloc(sizeof(int) * data->totalnb)))
		return (-1);
	filltab(data);
	return (0);
}
