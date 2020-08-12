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

	if(!(temp_map = (char **)malloc(((*i)+1) * sizeof(char *))))
		perror("Error: ");
	j = -1;
	while (++j < *i)
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
	if(!(map[*i] = ft_strdup(line)))
		perror("Error: ");
	(*i)++;
	return (map);
}
