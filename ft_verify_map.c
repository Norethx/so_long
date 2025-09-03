/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:15:16 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/03 14:33:58 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_map		ft_verify_map(char **map, t_pos ref);
static t_pos		ft_verify_start(char **map, t_pos ref);
static int			ft_handle_map_aux(t_obj_map meta_map);
static t_obj_map	ft_init_meta_map(void);

t_obj_map	ft_handle_map(char **map)
{
	t_pos		ref;
	t_pos		init;
	t_obj_map	meta_map;

	meta_map = ft_init_meta_map();
	ref.y = 0;
	while (map[ref.y])
		ref.y++;
	ref.x = ft_strlen(map[0]) - 1;
	ref.y -= 1;
	if (ft_verify_map(map, ref))
		return (ft_init_meta_map());
	init = ft_verify_start(map, ref);
	if (init.y == -1)
	{
		handle_error(ERROR_NOSTART);
		return (ft_init_meta_map());
	}
	ft_flood_fill(map, init, ref, &meta_map);
	if (ft_handle_map_aux(meta_map))
		return (ft_init_meta_map());
	ft_gc_collect();
	return (meta_map);
}

static t_map	ft_verify_map(char **map, t_pos ref)
{
	int	i[2];

	i[0] = 0;
	while (map[i[0]])
		if ((ref.x + 1) != ft_strlen(map[i[0]++]))
			return (handle_error(ERROR_MAPNOTRET));
	i[0] = 0;
	while (i[0] <= ref.y)
	{
		if (i[0] == 0 || i[0] == ref.y)
		{
			i[1] = 0;
			while (i[1] < ref.x)
				if (map[i[0]][i[1]++] != '1')
					return (handle_error(ERROR_NOWALL));
		}
		else if (map[i[0]][0] != '1' || map[i[0]][ref.x - 1] != '1')
			return (handle_error(ERROR_NOWALL));
		i[0]++;
	}
	return (0);
}

static t_pos	ft_verify_start(char **map, t_pos ref)
{
	t_pos	init;

	init.y = 0;
	while (init.y <= ref.y)
	{
		init.x = 0;
		while (init.x <= ref.x)
		{
			if (map[init.y][init.x] == 'P')
				return (init);
			init.x++;
		}
		init.y++;
	}
	init.x = -1;
	init.y = -1;
	return (init);
}

static int	ft_handle_map_aux(t_obj_map meta_map)
{
	if (meta_map.starting == 0)
		return (handle_error(ERROR_NOSTART));
	if (meta_map.exit == 0)
		return (handle_error(ERROR_NOEXIT));
	if (meta_map.collectible == 0)
		return (handle_error(ERROR_NOCOLLEC));
	if (meta_map.others_char > 0)
		return (handle_error(ERROR_OTHERSCHARS));
	if (meta_map.starting > 1)
		return (handle_error(ERROR_MOREONESTART));
	if (meta_map.exit > 1)
		return (handle_error(ERROR_MOREONEEXIT));
	return (0);
}

static t_obj_map	ft_init_meta_map(void)
{
	t_obj_map	rtn;

	rtn.collectible = 0;
	rtn.exit = 0;
	rtn.starting = 0;
	rtn.others_char = 0;
	return (rtn);
}
