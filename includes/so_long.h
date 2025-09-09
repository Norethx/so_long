/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:48:55 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/09 17:12:41 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42.h"
# include "libft.h"

# define WIDTH 28
# define HEIGHT 56

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
	ERROR_MOREONEEXIT,
	ERROR_NOBER
}			t_map;

typedef enum e_handle_game
{
	FLOOR = 0,
	WALL,
	WALL_DOWN,
	WALL_DOWN_EL,
	WALL_DOWN_ER,
	WALL_TOP,
	WALL_TOP_EL,
	WALL_TOP_ER,
	WALL_R,
	WALL_L,
	COLLEC,
	EXIT_C,
	EXIT_O,
	PLAYER_R,
	PLAYER_L,
	WALL_MID,
}			t_handle_game;

typedef struct s_pos
{
	int		x;
	int		y;
}			t_pos;

typedef struct s_mlx_init
{
	int		idx;
	int		max_wid;
	int		max_hei;
}			t_mlx_init;

typedef struct s_game
{
	int		player;
	int		collect;
	int		exit;
	int		others;
	int		qt_col;
	int		mov;
	t_pos	size;
	t_pos	init;
	t_pos	end;
	int		f_col;
	int		f_ext;
	char	**map;
}			t_game;

void		ft_flood_fill(char **map, t_pos init, t_pos final,
				t_game **obj_map);
int			handle_error(t_map error);
t_game		*ft_handle_map(char **map);
void		*ft_mlx_obj(int idx, t_game *game);
int			ft_handle_game(t_game *meta_map);
void		ft_fill_scene(t_game *game);
void		ft_build_floor(t_game *game);
void		ft_build_walls(t_game *game);
void		ft_fill_edges(t_pos max, int pos);
void		ft_render_dup(t_game *game, char c, int *img);
void		ft_init_image(mlx_image_t **imgs, mlx_t *mlx);
void		ft_hook_key(mlx_key_data_t keydata, void *param);
void		ft_resize_img(void);
void		ft_hook_idle(void *param);

#endif
