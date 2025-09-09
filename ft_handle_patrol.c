/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_patrol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:18:18 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/08 19:39:03 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_alter_instance(t_player *player, int cont, int i, t_patrol *idx);
static void	ft_alter_position_all(t_player *player, t_patrol *idx);
static void	verify_walls(mlx_image_t *player, mlx_instance_t *ist_w,
				size_t count, t_patrol *idx);
static void	ft_walk(t_player *player, char c, int cont, t_patrol **idx);

void	ft_animation_move_patrol(t_patrol *info, char c, int cont)
{
	t_player	*patrol;
	mlx_image_t	*wall_m;
	int			s_dir;

	patrol = ft_mlx_obj(19, NULL);
	s_dir = info->direction;
	wall_m = ft_mlx_obj(WALL_MID, NULL);
	info->actual_i = 3;
	ft_walk(patrol, c, cont, &info);
	if (s_dir % 2 != info->direction % 2)
		cont *= -1;
	verify_walls(patrol->run[0], wall_m->instances, wall_m->count, info);
	ft_alter_instance(patrol, cont, 0, info);
	ft_alter_position_all(patrol, info);
	info->last_anime = mlx_get_time();
}

static void	ft_alter_position_all(t_player *player, t_patrol *idx)
{
	int		i;
	int32_t	z;
	t_pos	pos;

	i = 0;
	pos.x = player->run[0]->instances[idx->idx].x;
	pos.y = player->run[0]->instances[idx->idx].y;
	z = player->run[0]->instances[idx->idx].z;
	while (i < 8)
	{
		if (i > 0)
		{
			player->run[i]->instances[idx->idx].x = pos.x;
			player->run[i]->instances[idx->idx].y = pos.y;
			mlx_set_instance_depth(&player->run[i]->instances[idx->idx], z);
		}
		player->idle[i]->instances[idx->idx].x = pos.x;
		player->idle[i]->instances[idx->idx].y = pos.y;
		mlx_set_instance_depth(&player->idle[i++]->instances[idx->idx], z);
	}
}

static void	ft_alter_instance(t_player *player, int cont, int i, t_patrol *idx)
{
	idx->actual = (idx->actual + 1) % 4;
	if (cont > 0)
	{
		while (i < 8)
		{
			if (idx->actual + 4 == i)
				player->run[i]->instances[idx->idx].enabled = true;
			else
				player->run[i]->instances[idx->idx].enabled = false;
			player->idle[i++]->instances[idx->idx].enabled = false;
		}
	}
	else
	{
		while (i < 8)
		{
			if (idx->actual == i)
				player->run[i]->instances[idx->idx].enabled = true;
			else
				player->run[i]->instances[idx->idx].enabled = false;
			player->idle[i++]->instances[idx->idx].enabled = false;
		}
	}
}

static void	verify_walls(mlx_image_t *player, mlx_instance_t *ist_w,
		size_t count, t_patrol *idx)
{
	int	i;

	i = 0;
	while ((size_t)i < count)
	{
		if (ist_w[i].y - WIDTH == player->instances[idx->idx].y
			&& ist_w[i].x == player->instances[idx->idx].x)
			mlx_set_instance_depth(&player->instances[idx->idx], ist_w[i].z
				- 4);
		if (ist_w[i].y + WIDTH == player->instances[idx->idx].y
			&& ist_w[i].x == player->instances[idx->idx].x)
			mlx_set_instance_depth(&player->instances[idx->idx], ist_w[i].z
				+ 4);
		else if (ist_w[i].y + (WIDTH * 2) == player->instances[idx->idx].y
			&& ist_w[i].x == player->instances[idx->idx].x)
			mlx_set_instance_depth(&player->instances[idx->idx], ist_w[i].z
				+ 4);
		i++;
	}
}

static void	ft_walk(t_player *player, char c, int cont, t_patrol **idx)
{
	char		**map;
	t_root_list	*r_map;

	r_map = ft_gc_call_root("full_map");
	map = ((t_gc_list *)ft_to_root_list(r_map)->lst->head->content)->content;
	if (c == 'y')
	{
		if (ft_walk_aux_y(player, map, cont, idx))
			idx[0]->direction = (idx[0]->direction + 1) % 4;
		else
		{
			player->run[0]->instances[idx[0]->idx].y += cont;
			idx[0]->last_dir = (idx[0]->direction + 2) % 4;
		}
	}
	else if (c == 'x')
	{
		if (ft_walk_aux_x(player, map, cont, idx))
			idx[0]->direction = (idx[0]->direction + 1) % 4;
		else
		{
			player->run[0]->instances[idx[0]->idx].x += cont;
			idx[0]->last_dir = (idx[0]->direction + 2) % 4;
		}
	}
}
