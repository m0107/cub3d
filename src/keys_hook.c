/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 06:19:59 by mgupta            #+#    #+#             */
/*   Updated: 2020/07/16 06:20:03 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int		keys_hook(int keycode, t_game *g)
{
	double mvspd;
	double rtspd;

	mvspd = 0.15;
	rtspd = 0.0872665;
	if (keycode == KEY_W)
		move_up(g, mvspd);
	if (keycode == KEY_S)
		move_down(g, mvspd);
	if (keycode == KEY_D)
		move_right(g, mvspd);
	if (keycode == KEY_A)
		move_left(g, mvspd);
	if (keycode == KEY_RIGHT)
		rotate_right(g, mvspd, rtspd);
	if (keycode == KEY_LEFT)
		rotate_left(g, mvspd, rtspd);
	if (keycode == KEY_ESC)
		exit_game(g);
	return (1);
}
