/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_idle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:02:53 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/08 19:45:44 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_hook_idle_aux(t_game *game);
static void	ft_hook_lose(mlx_image_t *player);
static void	ft_hook_move_patrol(t_patrol *list);

void	ft_hook_idle(void *param)
{
	int			i[2];
	mlx_image_t	*collec;
	mlx_image_t	*player;

	i[0] = 0;
	i[1] = 0;
	collec = ft_mlx_obj(COLLEC, NULL);
	player = ((t_player *)ft_mlx_obj(18, NULL))->idle[0];
	ft_hook_idle_player();
	ft_hook_move_patrol(((t_game *)param)->patrols);
	ft_hook_lose(player);
	while (i[0] < ((t_game *)param)->collect->qt)
	{
		if (collec->instances[i[0]].enabled
			&& (player->instances[0].x == collec->instances[i[0]].x
				&& player->instances[0].y == (collec->instances[i[0]].y)))
		{
			collec->instances[i[0]].enabled = false;
			((t_game *)param)->qt_col--;
		}
		i[0]++;
	}
	ft_hook_idle_aux(param);
}

static void	ft_hook_lose(mlx_image_t *player)
{
	int			i;
	t_player	*patrol;
	mlx_t		*mlx;

	patrol = ft_mlx_obj(19, NULL);
	mlx = ft_mlx_obj(17, NULL);
	i = 0;
	while ((size_t)i < patrol->idle[0]->count)
	{
		if (patrol->idle[0]->instances[i].x == player->instances[0].x
			&& patrol->idle[0]->instances[i].y == player->instances[0].y)
		{
			ft_printf("\nYou Die!!");
			mlx_close_window(mlx);
		}
		i++;
	}
}

static void	ft_hook_move_patrol(t_patrol *list)
{
	t_patrol	*aux;
	double		time;
	int			mult;
	int			i;

	i = 0;
	aux = list;
	time = mlx_get_time();
	while ((size_t)i < ((t_player *)ft_mlx_obj(19, NULL))->idle[0]->count)
	{
		if (time - aux->last_anime > 0.2)
		{
			if (aux->direction == 0 || aux->direction == 3)
				mult = -1;
			if (aux->direction == 1 || aux->direction == 2)
				mult = 1;
			if (aux->direction == 0 || aux->direction == 2)
				ft_animation_move_patrol(aux, 'y', WIDTH * mult);
			else if (aux->direction == 1 || aux->direction == 3)
				ft_animation_move_patrol(aux, 'x', WIDTH * mult);
		}
		aux = aux->next;
		i++;
	}
}

static void	ft_hook_idle_aux(t_game *game)
{
	mlx_image_t	*exit[2];
	mlx_t		*mlx;
	mlx_image_t	*player;
	t_pos		end;

	mlx = ft_mlx_obj(17, NULL);
	exit[0] = ft_mlx_obj(EXIT_C, NULL);
	exit[1] = ft_mlx_obj(EXIT_O, NULL);
	end.x = exit[0]->instances[0].x / WIDTH;
	end.y = exit[0]->instances[0].y / WIDTH;
	player = ((t_player *)ft_mlx_obj(18, NULL))->idle[0];
	if (game->qt_col == 0 && !exit[1]->instances[0].enabled)
	{
		exit[0]->instances[0].enabled = false;
		exit[1]->instances[0].enabled = true;
		game->map[end.y][end.x] = '0';
	}
	if (exit[1]->instances[0].enabled
		&& (player->instances[0].x == exit[1]->instances[0].x
			&& player->instances[0].y == (exit[1]->instances[0].y)))
	{
		ft_printf("\nCongratulations! You won!!");
		mlx_close_window(mlx);
	}
}
