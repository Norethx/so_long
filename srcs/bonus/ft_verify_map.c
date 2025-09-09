/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:15:16 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/09 13:37:02 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static t_map	ft_verify_map(char **map, t_pos ref);
static void		ft_verify_start(char **map, t_pos ref, t_game **obj_map);
static int		ft_handle_map_aux(t_game *meta_map);
static t_game	*ft_init_meta_map(void);

t_game	*ft_handle_map(char **map)
{
	t_game	*meta_map;

	meta_map = ft_init_meta_map();
	meta_map->size.y = 0;
	while (map[meta_map->size.y + 1])
		meta_map->size.y++;
	meta_map->size.x = ft_strlen(map[0]) - 1;
	if (ft_verify_map(map, meta_map->size))
		return (NULL);
	ft_verify_start(map, meta_map->size, &meta_map);
	ft_flood_fill(map, meta_map->init, meta_map->size, &meta_map);
	if (ft_handle_map_aux(meta_map))
		return (NULL);
	ft_gc_collect();
	meta_map->size.x--;
	return (meta_map);
}

static t_map	ft_verify_map(char **map, t_pos ref)
{
	int	i[2];

	i[0] = 0;
	while (map[i[0]])
		if ((ref.x + 1) != (int)ft_strlen(map[i[0]++]))
			return (handle_error(ERROR_MAPNOTREC));
	if ((ref.y + 1) < 4 || (ref.y + 1) < 4)
		return (handle_error(MAP_ERROR));
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

static void	ft_verify_start(char **map, t_pos ref, t_game **obj_map)
{
	t_pos	init;

	init.y = 0;
	while (init.y < ref.y)
	{
		init.x = 0;
		while (init.x < ref.x)
		{
			if (map[init.y][init.x] == 'C')
				obj_map[0]->collect++;
			else if (map[init.y][init.x] == 'E')
				obj_map[0]->exit++;
			else if (map[init.y][init.x] == 'P')
			{
				obj_map[0]->player++;
				obj_map[0]->init.x = init.x;
				obj_map[0]->init.y = init.y;
			}
			else if (!ft_strchr("01CEPX", map[init.y][init.x]))
				obj_map[0]->others++;
			init.x++;
		}
		init.y++;
	}
}

static int	ft_handle_map_aux(t_game *meta_map)
{
	if (meta_map->player == 0)
		return (handle_error(ERROR_NOSTART));
	if (meta_map->exit == 0)
		return (handle_error(ERROR_NOEXIT));
	if (meta_map->collect == 0)
		return (handle_error(ERROR_NOCOLLEC));
	if (meta_map->others > 0)
		return (handle_error(ERROR_OTHERSCHARS));
	if (meta_map->player > 1)
		return (handle_error(ERROR_MOREONESTART));
	if (meta_map->exit > 1)
		return (handle_error(ERROR_MOREONEEXIT));
	if (meta_map->exit != meta_map->f_ext)
		return (handle_error(ERROR_NOEXIT));
	if (meta_map->collect != meta_map->f_col)
		return (handle_error(ERROR_NOCOLLEC));
	return (0);
}

static t_game	*ft_init_meta_map(void)
{
	t_gc_list	*gc_meta_map;
	t_game		*rtn;
	int			i;

	i = 0;
	rtn = NULL;
	gc_meta_map = ft_gc_calloc(1, sizeof(t_game), GC_DATA);
	ft_gc_register_root(gc_meta_map, "full_map");
	rtn = gc_meta_map->content;
	return (rtn);
}
