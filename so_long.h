/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:48:55 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/01 20:44:21 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"

typedef enum t_map
{
	MAP_ERROR,
	ARCHIVE_ERROR

}		e_map;

typedef struct s_obj_map
{
	int	collectible;
	int	exit;
	int	starting;
}		t_obj_map;

typedef struct s_pos
{
	int	x;
	int	y;
}		t_pos;


void	ft_flood_fill(char **map, t_pos init, t_pos final, t_obj_map *obj_map);

#endif
