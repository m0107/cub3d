/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 05:51:57 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 05:51:58 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



char *remove_space(char *line)
{
	while (*line == '\t' || *line == '\n' || *line == '\v'
			|| *line == '\f' || *line == '\r' || *line == ' ')
		line++;
	return(line);
}

void mp_helpr(char * line, t_game *game, int *i)
{

		char	*temp;
		temp = line;
		line  = remove_space(line);
		if (*line == 'R')	printf("Testing res: %d\n",res_parser(game,line));
		else if (*line == 'N'|| (*line == 'S' && *(line+1) == 'O') || *line == 'W' || *line == 'E')
			printf("Testing texture : %d\n",tex_parser(game, line));
		else if (*line == 'F' || *line == 'C')
			printf("Testing color: %d\n",color_parser(game,line));
		else if (*line != '\n' && *line !='\0'){
			// printf("line--- %s\n", line);
			game->map = map_parser(temp, i, game->map);
		}
		free(temp);
	
}

void	main_parser(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int 	i;
	char	**map;

	i = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		mp_helpr(line, game, &i);
	}
	mp_helpr(line, game, &i);
	close(fd);
}