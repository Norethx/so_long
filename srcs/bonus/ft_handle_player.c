/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:13:44 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/09 13:36:48 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_alter_instance(t_player *player, int cont, int i);
static void	ft_alter_position_all(t_player *player);
static void	verify_walls(mlx_image_t *player, mlx_instance_t *ist_w,
				size_t count);
static void	ft_walk(t_player *player, char c, int cont, t_game *game);

void	ft_animation_move(char c, int cont, t_game *game)
{
	t_player	*player;
	mlx_image_t	*wall_m;

	player = ft_mlx_obj(18, NULL);
	wall_m = ft_mlx_obj(WALL_MID, NULL);
	player->actual_i = 3;
	player->direction = cont;
	ft_walk(player, c, cont, game);
	verify_walls(player->run[0], wall_m->instances, wall_m->count);
	ft_alter_instance(player, cont, 0);
	ft_alter_position_all(player);
	player->last_anime = 0;
	ft_gc_collect();
}

static void	ft_alter_position_all(t_player *player)
{
	int		i;
	int32_t	z;

	i = 0;
	z = player->run[0]->instances[0].z;
	while (i < 8)
	{
		if (i == 0)
		{
			player->idle[i]->instances[0].x = player->run[0]->instances[0].x;
			player->idle[i]->instances[0].y = player->run[0]->instances[0].y;
			mlx_set_instance_depth(&player->idle[i++]->instances[0], z);
		}
		else
		{
			player->idle[i]->instances[0].x = player->run[0]->instances[0].x;
			player->idle[i]->instances[0].y = player->run[0]->instances[0].y;
			mlx_set_instance_depth(&player->idle[i]->instances[0], z);
			player->run[i]->instances[0].x = player->run[0]->instances[0].x;
			player->run[i]->instances[0].y = player->run[0]->instances[0].y;
			mlx_set_instance_depth(&player->run[i++]->instances[0], z);
		}
	}
}

static void	ft_alter_instance(t_player *player, int cont, int i)
{
	player->actual = (player->actual + 1) % 4;
	if (cont < 0)
	{
		while (i < 8)
		{
			if (player->actual + 4 == i)
				player->run[i]->instances[0].enabled = true;
			else
				player->run[i]->instances[0].enabled = false;
			player->idle[i++]->instances[0].enabled = false;
		}
	}
	else
	{
		while (i < 8)
		{
			if (player->actual == i)
				player->run[i]->instances[0].enabled = true;
			else
				player->run[i]->instances[0].enabled = false;
			player->idle[i++]->instances[0].enabled = false;
		}
	}
}

static void	verify_walls(mlx_image_t *player, mlx_instance_t *ist_w,
		size_t count)
{
	int	i;

	i = 0;
	while ((size_t)i < count)
	{
		if (ist_w[i].y - WIDTH == player->instances[0].y
			&& ist_w[i].x == player->instances[0].x)
			mlx_set_instance_depth(&player->instances[0], ist_w[i].z - 3);
		if (ist_w[i].y + WIDTH == player->instances[0].y
			&& ist_w[i].x == player->instances[0].x)
			mlx_set_instance_depth(&player->instances[0], ist_w[i].z + 3);
		else if (ist_w[i].y + (WIDTH * 2) == player->instances[0].y
			&& ist_w[i].x == player->instances[0].x)
			mlx_set_instance_depth(&player->instances[0], ist_w[i].z + 3);
		i++;
	}
}

static void	ft_walk(t_player *player, char c, int cont, t_game *game)
{
	char		**map;
	t_root_list	*r_map;

	r_map = ft_gc_call_root("full_map");
	map = ((t_gc_list *)ft_to_root_list(r_map)->lst->head->content)->content;
	if (c == 'y')
	{
		if (ft_strchr("1E", map[(player->run[0]->instances[0].y + cont)
					/ WIDTH][player->run[0]->instances[0].x / WIDTH]))
			return ;
		player->run[0]->instances[0].y += cont;
		game->mov++;
		ft_mlx_obj(14, game);
		ft_printf("Moves: %d\n", game->mov);
	}
	if (c == 'x')
	{
		if (ft_strchr("1E", map[player->run[0]->instances[0].y
					/ WIDTH][(player->run[0]->instances[0].x + cont) / WIDTH]))
			return ;
		player->run[0]->instances[0].x += cont;
		game->mov++;
		ft_mlx_obj(14, game);
		ft_printf("Moves: %d\n", game->mov);
	}
}
