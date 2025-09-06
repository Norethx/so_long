/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:43:41 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/05 19:49:55 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	aux_flood_fill(t_pos init, t_pos *new);

void	ft_flood_fill(char **map, t_pos init, t_pos final, t_game **obj_map)
{
	t_pos	p_init[4];

	if (map[init.y][init.x] == 'E')
	{
		obj_map[0]->exit->qt++;
		obj_map[0]->end.x = init.x;
		obj_map[0]->end.y = init.y;
	}
	if (map[init.y][init.x] == 'E')
		map[init.y][init.x] = '1';
	if (init.x < 0 || init.y < 0 || final.x == init.x || final.y == init.y
		|| ft_strchr("1E", map[init.y][init.x]))
		return ;
	if (map[init.y][init.x] == 'C')
		obj_map[0]->collect->qt++;
	else if (map[init.y][init.x] == 'P')
		obj_map[0]->player->qt++;
	else if (!ft_strchr("01CEP", map[init.y][init.x]))
		obj_map[0]->others++;
	map[init.y][init.x] = '1';
	aux_flood_fill(init, p_init);
	ft_flood_fill(map, p_init[0], final, obj_map);
	ft_flood_fill(map, p_init[1], final, obj_map);
	ft_flood_fill(map, p_init[2], final, obj_map);
	ft_flood_fill(map, p_init[3], final, obj_map);
}

static void	aux_flood_fill(t_pos init, t_pos *new)
{
	new[0] = init;
	new[1] = init;
	new[2] = init;
	new[3] = init;
	new[0].x++;
	new[1].y++;
	new[2].x--;
	new[3].y--;
}
