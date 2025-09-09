/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_idle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:02:53 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/09 14:24:19 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_hook_idle_aux(t_game *game);
static void	ft_hook_lose(mlx_image_t *player);
static void	ft_hook_move_patrol(t_patrol *list, mlx_t *mlx);

void	ft_hook_idle(void *param)
{
	int			i[2];
	mlx_image_t	*collec;
	mlx_image_t	*player;
	mlx_t		*mlx;

	mlx = ft_mlx_obj(15, NULL);
	i[0] = 0;
	i[1] = 0;
	collec = ft_mlx_obj(COLLEC, NULL);
	player = ((t_player *)ft_mlx_obj(18, NULL))->idle[0];
	ft_hook_idle_player();
	ft_hook_move_patrol(((t_game *)param)->patrols, mlx);
	ft_hook_lose(player);
	while (i[0] < ((t_game *)param)->collect)
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
	t_root_list	*r_map;
	t_game		*infos;

	r_map = ft_to_root_list(ft_gc_call_root("full_map"));
	infos = ((t_gc_list *)r_map->lst->head->next->content)->content;
	patrol = ft_mlx_obj(19, NULL);
	mlx = ft_mlx_obj(15, NULL);
	i = 0;
	if (!infos->die)
	{
		while ((size_t)i < patrol->idle[0]->count)
		{
			if (patrol->idle[0]->instances[i].x == player->instances[0].x
				&& patrol->idle[0]->instances[i].y == player->instances[0].y)
			{
				ft_printf("\nYou Die!!");
				infos->die++;
				mlx_close_window(mlx);
			}
			i++;
		}
	}
}

static void	ft_hook_move_patrol(t_patrol *list, mlx_t *mlx)
{
	t_patrol	*aux;
	int			mult;
	int			i;

	i = 0;
	aux = list;
	while ((size_t)i < ((t_player *)ft_mlx_obj(19, NULL))->idle[0]->count)
	{
		aux->last_anime += mlx->delta_time;
		while (aux->last_anime >= 0.16)
		{
			if (aux->direction == 0 || aux->direction == 3)
				mult = -1;
			if (aux->direction == 1 || aux->direction == 2)
				mult = 1;
			if (aux->direction == 0 || aux->direction == 2)
				ft_animation_move_patrol(aux, 'y', WIDTH * mult);
			else if (aux->direction == 1 || aux->direction == 3)
				ft_animation_move_patrol(aux, 'x', WIDTH * mult);
			ft_hook_lose(((t_player *)ft_mlx_obj(18, NULL))->idle[0]);
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

	mlx = ft_mlx_obj(15, NULL);
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
