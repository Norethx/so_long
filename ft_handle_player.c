/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:29:59 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/09 13:54:37 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_animation_move(char c, int cont, t_game *game);
static void	verify_walls(mlx_image_t **player, mlx_instance_t *ist_w,
				size_t count);
static void	ft_walk(mlx_image_t **player, char c, int cont, t_game *game);

void	ft_hook_key(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;
	t_game	*game;

	game = param;
	mlx = ft_mlx_obj(17, 0);
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(mlx);
		if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			ft_animation_move('y', -WIDTH, game);
		if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			ft_animation_move('y', +WIDTH, game);
		if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			ft_animation_move('x', -WIDTH, game);
		if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			ft_animation_move('x', +WIDTH, game);
	}
}

static void	ft_animation_move(char c, int cont, t_game *game)
{
	mlx_image_t	*player[2];
	mlx_image_t	*wall_m;

	player[0] = ft_mlx_obj(13, NULL);
	player[1] = ft_mlx_obj(14, NULL);
	wall_m = ft_mlx_obj(WALL_MID, NULL);
	ft_walk(player, c, cont, game);
	if (cont < 0)
		player[0]->instances[0].enabled = false;
	if (cont < 0)
		player[1]->instances[0].enabled = true;
	else
	{
		player[0]->instances[0].enabled = true;
		player[1]->instances[0].enabled = false;
	}
	player[1]->instances[0].x = player[0]->instances[0].x;
	player[1]->instances[0].y = player[0]->instances[0].y;
	verify_walls(player, wall_m->instances, wall_m->count);
}

static void	verify_walls(mlx_image_t **player, mlx_instance_t *ist_w,
		size_t count)
{
	int	i;

	i = 0;
	while ((size_t)i < count)
	{
		if (ist_w[i].y - WIDTH == player[1]->instances[0].y
			&& ist_w[i].x == player[1]->instances[0].x)
		{
			mlx_set_instance_depth(&player[0]->instances[0], ist_w[i].z - 3);
			mlx_set_instance_depth(&player[1]->instances[0], ist_w[i].z - 3);
		}
		if (ist_w[i].y + WIDTH == player[1]->instances[0].y
			&& ist_w[i].x == player[1]->instances[0].x)
		{
			mlx_set_instance_depth(&player[0]->instances[0], ist_w[i].z + 3);
			mlx_set_instance_depth(&player[1]->instances[0], ist_w[i].z + 3);
		}
		else if (ist_w[i].y + (WIDTH * 2) == player[1]->instances[0].y
			&& ist_w[i].x == player[1]->instances[0].x)
		{
			mlx_set_instance_depth(&player[0]->instances[0], ist_w[i].z + 3);
			mlx_set_instance_depth(&player[1]->instances[0], ist_w[i].z + 3);
		}
		i++;
	}
}

static void	ft_walk(mlx_image_t **player, char c, int cont, t_game *game)
{
	char		**map;
	t_root_list	*r_map;

	r_map = ft_gc_call_root("full_map");
	map = ((t_gc_list *)ft_to_root_list(r_map)->lst->head->content)->content;
	if (c == 'y')
	{
		if (ft_strchr("1E", map[(player[0]->instances[0].y + cont)
					/ WIDTH][player[0]->instances[0].x / WIDTH]))
			return ;
		player[0]->instances[0].y += cont;
		game->mov++;
		ft_printf("Moves: %d\n", game->mov);
	}
	if (c == 'x')
	{
		if (ft_strchr("1E", map[player[0]->instances[0].y
					/ WIDTH][(player[0]->instances[0].x + cont) / WIDTH]))
			return ;
		player[0]->instances[0].x += cont;
		game->mov++;
		ft_printf("Moves: %d\n", game->mov);
	}
}
