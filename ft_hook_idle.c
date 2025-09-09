/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_idle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:28:24 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/09 13:45:50 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_hook_idle_aux(t_game *game);

void	ft_hook_idle(void *param)
{
	int			i[2];
	mlx_image_t	*collec;
	mlx_image_t	*player;

	i[0] = 0;
	i[1] = 0;
	collec = ft_mlx_obj(COLLEC, NULL);
	player = ft_mlx_obj(PLAYER_R, NULL);
	while (i[0] < ((t_game *)param)->collect)
	{
		if (collec->instances[i[0]].enabled
			&& (player->instances[0].x == collec->instances[i[0]].x
				&& player->instances[0].y == (collec->instances[i[0]].y)))
		{
			collec->instances[i[0]].enabled = false;
			((t_game *)param)->qt_col--;
			ft_mlx_obj(16, param);
			ft_gc_collect();
		}
		i[0]++;
	}
	ft_hook_idle_aux(param);
}

static void	ft_hook_idle_aux(t_game *game)
{
	mlx_image_t	*exit[2];
	mlx_t		*mlx;
	mlx_image_t	*player;

	mlx = ft_mlx_obj(17, NULL);
	exit[0] = ft_mlx_obj(EXIT_C, NULL);
	exit[1] = ft_mlx_obj(EXIT_O, NULL);
	player = ft_mlx_obj(PLAYER_R, NULL);
	if (game->qt_col == 0 && !exit[1]->instances[0].enabled)
	{
		exit[0]->instances[0].enabled = false;
		exit[1]->instances[0].enabled = true;
		game->map[game->end.y][game->end.x] = '0';
	}
	if (exit[1]->instances[0].enabled
		&& (player->instances[0].x == exit[1]->instances[0].x
			&& player->instances[0].y == (exit[1]->instances[0].y)))
	{
		ft_printf("\nCongratulations! You won!!");
		mlx_close_window(mlx);
	}
}
