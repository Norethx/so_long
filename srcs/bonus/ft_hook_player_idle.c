/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_player_idle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:03 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/09 13:36:55 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_alter_instance_idle(t_player *player, int cont, int i);

void	ft_hook_idle_player(void)
{
	t_player	*player;
	mlx_t		*mlx;

	mlx = ft_mlx_obj(15, NULL);
	player = ft_mlx_obj(18, NULL);
	player->last_anime += mlx->delta_time;
	while (player->last_anime >= 0.25)
	{
		player->actual = 3;
		player->actual_i = (player->actual_i + 1) % 4;
		ft_alter_instance_idle(player, player->direction, 0);
		player->last_anime -= 0.25;
	}
}

static void	ft_alter_instance_idle(t_player *player, int cont, int i)
{
	if (cont < 0)
	{
		while (i < 8)
		{
			if (player->actual_i + 4 == i)
				player->idle[i]->instances[0].enabled = true;
			else
				player->idle[i]->instances[0].enabled = false;
			player->run[i++]->instances[0].enabled = false;
		}
	}
	else
	{
		while (i < 8)
		{
			if (player->actual_i == i)
				player->idle[i]->instances[0].enabled = true;
			else
				player->idle[i]->instances[0].enabled = false;
			player->run[i++]->instances[0].enabled = false;
		}
	}
}
