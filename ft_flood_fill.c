/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:43:41 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/01 20:10:46 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	aux_flood_fill(t_pos init, t_pos *new);

void	ft_flood_fill(char **map, t_pos init, t_pos final, t_obj_map *obj_map)
{
	t_pos	p_init[4];

	if (init.x < 0 || init.y < 0 || final.x == init.x || final.y == init.y
		|| map[init.x][init.y] == '1' || !ft_strchr("01CEP", map[init.x][init.y]))
		return ;
	if (map[init.x][init.y]== 'C')
		obj_map->collectible++;
	if (map[init.x][init.y] == 'E')
		obj_map->exit++;
	if (map[init.x][init.y] == 'P')
		obj_map->starting++;
	map[init.x][init.y] = 'F';
	aux_flood_fill(init,p_init);
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
