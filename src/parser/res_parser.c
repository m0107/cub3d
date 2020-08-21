/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 05:51:57 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 05:51:58 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_n_set_res(t_game *g, int scn_w, int scn_h)
{
	if (scn_w > 2560 || scn_w == -942514)
		scn_w = 1600;
	if (scn_h > 1440 || scn_h == -942514)
		scn_h = 900;
	if (scn_w <= 0 || scn_h <= -1)
		printf_error("Invalid Resolution\n", g);
	g->vars.scn_h = scn_h;
	g->vars.scn_w = scn_w;
	if (!(g->r.zbuffer = (int *)malloc((g->vars.scn_w) * sizeof(int))))
		printf_error("malloc map failed.\n", g);
}

void	remove_extra(char **line)
{
	while (**line >= '0' && **line <= '9')
		(*line)++;
}

void	res_parser(t_game *g, char *line)
{
	int	scn_w;
	int	scn_h;
	int	loop_len;

	if (g->map.size > 0)
		printf_error("Input order incorrect:res_parser.\n", g);
	line = line + 2;
	scn_w = ft_atoi_cub(&line);
	remove_extra(&line);
	scn_h = ft_atoi_cub(&line);
	remove_extra(&line);
	while (*line != '\0')
	{
		if (*line != ' ')
			printf_error("Extra input in resolution\n", g);
		line++;
	}
	check_n_set_res(g, scn_w, scn_h);
	g->pars_check[0]++;
}
