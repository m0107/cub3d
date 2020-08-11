/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 23:17:28 by mgupta            #+#    #+#             */
/*   Updated: 2020/08/09 23:17:30 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**map_parser(char *line, int *i, char **map)
{
	char	**temp_map;
	int		j;

	(*i)++;
	temp_map = (char **)malloc(*i * sizeof(char *));
	j = -1;
	while (++j < (*i - 1))
		temp_map[j] = map[j];
	free(map);
	map = temp_map;
	j = 0;
	while (line[j] != '\0')
	{
		if (line[j] == ' ')
			line[j] = '$';
		else if (line[j] == 'N')
			line[j] = '0';
		j++;
	}
	map[(*i) - 1] = ft_strdup(line);
	return (map);
}
