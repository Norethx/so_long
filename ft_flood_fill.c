/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:43:41 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/01 11:35:34 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	aux_flood_fill(t_pos init, t_pos *new);

void	ft_flood_fill(char map[10][10], t_pos init, t_pos final, t_obj_map *obj_map)
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


int	main(void)
{
	char str[10][10] = {"1111111111", "10E0000001","100P00C001","1000000001","1000C00001","1000000001","1000C00001","1000000001","1000000001","1111111111"};
	t_obj_map map;
	t_pos init;
	t_pos final;
	map.collectible = 0;
	map.exit = 0;
	map.starting = 0;
	init.x = 2;
	init.y = 3;
	final.x = 9;
	final.y = 9;
	ft_flood_fill(str,init,final,&map);
	printf("%c",str[init.x][init.y]);
	printf("\n%d%d%d",map.collectible, map.exit,map.starting);

}
