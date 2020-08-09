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

int	map_parser(char *line, int i, int size, char ***map) 
{
	char **temp_map;

	if(i == size) {
		size++;
		temp_map = (char **)malloc(size * sizeof(char *));
		int j;
		for(j = 0;j < (size -1); j++)
		{
			temp_map[j] = map[j];
		}
		free(map);
		map = temp_map;
	}
	map[i++] = ft_strdup(line);
	while (*line != '\0') {
		if(*line == ' ') *line = '$';
		printf("%c", *line++);
	}
	return (map);
}