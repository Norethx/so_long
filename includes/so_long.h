/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:48:55 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/03 16:07:03 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "gc.h"
# include "libft.h"

typedef enum e_map
{
	ARGS_ERROR = 1,
	MAP_ERROR,
	FILE_ERROR,
	ERROR_NOEXIT,
	ERROR_NOSTART,
	ERROR_NOWALL,
	ERROR_MAPNOTREC,
	ERROR_NOCOLLEC,
	ERROR_OTHERSCHARS,
	ERROR_MOREONESTART,
	ERROR_MOREONEEXIT
}			t_map;

typedef struct s_obj_map
{
	int		collectible;
	int		exit;
	int		starting;
	int		others_char;
}			t_obj_map;

typedef struct s_pos
{
	int		x;
	int		y;
}			t_pos;

void		ft_flood_fill(char **map, t_pos init, t_pos final,
				t_obj_map *obj_map);
int			handle_error(t_map error);
t_obj_map	ft_handle_map(char **map);

#endif
