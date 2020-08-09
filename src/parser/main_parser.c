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

int	checkno_cub(long ans, int sign)
{
	if (sign > 0 && ans > 2147483647)
		return (-1);
	else if (sign < 0 && ans > 2147483648)
		return (0);
	return (ans * sign);
}

int	ft_atoi_cub(char **str)
{
	long	sign;
	long	ans;
	ans = 0;
	sign = 1;
	while (**str == '\t' || **str == '\n' || **str == '\v'
			|| **str == '\f' || **str == '\r' || **str == ' ')
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		ans = ans * 10 + (**str - 48);
		if (ans > 21474836470)
			break ;
		(*str)++;
	}
	return (checkno_cub(ans, sign));
}



char *remove_space(char *line)
{
	while (*line == '\t' || *line == '\n' || *line == '\v'
			|| *line == '\f' || *line == '\r' || *line == ' ')
		line++;
	return(line);
}
void	main_parser(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	char	*temp;
	int 	size = 1;
	int 	i = 0;



	char **map = (char **)malloc(size * sizeof(char *));	
	fd = open(filename, O_RDONLY);
	//printf("%d :  test", fd);
	while (get_next_line(fd, &line) == 1){
		temp = line;
		line  = remove_space(line);
		if (*line == 'R')	printf("Testing res: %d\n",res_parser(game,line));
		else if (*line == 'N'|| (*line == 'S' && *(line+1) == 'O') || *line == 'W' || *line == 'E')
			printf("Testing texture : %d\n",tex_parser(game, line));
		else if (*line == 'F' || *line == 'C')
			printf("Testing color: %d\n",color_parser(game,line));
		else if (*line != '\n' && *line !='\0')
		{	
			map_parser(temp, i, size, &map);
			printf("temp::::%d ----- %s\n",(i-1), map[i-1]);
		}
		free(temp);
	}
	map[i] = ft_strdup(line);
	printf("temp:::: %s\n", map[i]);
	game->map = map;
	printf("data width::: %d\n", game->vars.screenWidth);
	printf("data height::: %d\n", game->vars.screenHeight);
	printf("data floor-color::: %d\n", game->vars.floor_color);
	free(line);
	//free(map);
	printf("map [i][j]: %s\n", game->map[1]);
	close(fd);
	printf("moti\n\n\n");
}