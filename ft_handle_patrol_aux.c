/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_patrol_aux.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:11:18 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/08 21:20:57 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_verify_others_patrols(t_player *player, int idx, t_pos pos);

int	ft_walk_aux_y(t_player *player, char **map, int cont, t_patrol **idx)
{
	t_pos	pos;
	int		i;

	i = 0;
	pos.x = player->run[0]->instances[idx[0]->idx].x;
	pos.y = player->run[0]->instances[idx[0]->idx].y;
	if (!ft_strchr("1E", map[(pos.y / WIDTH) + 1][(pos.x / WIDTH)]))
		i++;
	if (!ft_strchr("1E", map[(pos.y / WIDTH) - 1][(pos.x / WIDTH)]))
		i++;
	if (!ft_strchr("1E", map[(pos.y / WIDTH)][(pos.x / WIDTH) + 1]))
		i++;
	if (!ft_strchr("1E", map[(pos.y / WIDTH)][(pos.x / WIDTH) - 1]))
		i++;
	if (ft_strchr("1E", map[(pos.y + cont) / WIDTH][pos.x / WIDTH]))
		return (1);
	if (idx[0]->last_dir == idx[0]->direction && i > 1 && !idx[0]->flag)
		return (++idx[0]->flag);
	pos.y += cont;
	if (ft_verify_others_patrols(player, idx[0]->idx, pos))
		return (1);
	idx[0]->flag = 0;
	return (0);
}

int	ft_walk_aux_x(t_player *player, char **map, int cont, t_patrol **idx)
{
	t_pos	pos;
	int		i;

	i = 0;
	pos.x = player->run[0]->instances[idx[0]->idx].x;
	pos.y = player->run[0]->instances[idx[0]->idx].y;
	if (!ft_strchr("1E", map[(pos.y / WIDTH) + 1][(pos.x / WIDTH)]))
		i++;
	if (!ft_strchr("1E", map[(pos.y / WIDTH) - 1][(pos.x / WIDTH)]))
		i++;
	if (!ft_strchr("1E", map[(pos.y / WIDTH)][(pos.x / WIDTH) + 1]))
		i++;
	if (!ft_strchr("1E", map[(pos.y / WIDTH)][(pos.x / WIDTH) - 1]))
		i++;
	if (ft_strchr("1E", map[pos.y / WIDTH][(pos.x + cont) / WIDTH]))
		return (1);
	if (idx[0]->last_dir == idx[0]->direction && i > 1 && !idx[0]->flag)
		return (++idx[0]->flag);
	pos.x += cont;
	if (ft_verify_others_patrols(player, idx[0]->idx, pos))
		return (1);
	idx[0]->flag = 0;
	return (0);
}

static int	ft_verify_others_patrols(t_player *player, int idx, t_pos pos)
{
	int	i;

	i = 0;
	while ((size_t)i < player->run[0]->count)
	{
		if (i != idx)
		{
			if (pos.x == player->run[0]->instances[i].x
				&& pos.y == player->run[0]->instances[i].y)
				return (1);
		}
		i++;
	}
	return (0);
}
