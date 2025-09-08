/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:48:55 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/07 23:06:10 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42.h"
# include "gc.h"
# include "libft.h"

# define WIDTH 28
# define HEIGHT (WIDTH + (WIDTH * 0.75))

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
}				t_map;

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
}				t_handle_game;

// typedef struct s_obj_map
// {
// 	int			collectible;
// 	int			exit;
// 	int			starting;
// 	int			others_char;
// }				t_obj_map;

typedef struct s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_mlx_init
{
	int			idx;
	int			max_wid;
	int			max_hei;
}				t_mlx_init;

// typedef struct s_player
// {
// 	mlx_texture_t	**texture;
// 	mlx_image_t		**image;
// 	int				actual;
// 	double			last_anime;
// }					t_player;

typedef struct s_mlx_lst
{
	t_list		lst;
	int			qt;
	int			active;
	double		last_i;
}				t_mlx_lst;

typedef struct s_game
{
	t_mlx_lst	*player;
	t_mlx_lst	*collect;
	t_mlx_lst	*exit;
	int			others;
	int			qt_col;
	int			mov;
	t_pos		size;
	t_pos		init;
	char		**map;
}				t_game;

typedef struct s_player
{
	mlx_image_t		*idle[8];
	mlx_image_t		*run[8];
	int				actual;
	double			last_anime;
}					t_player;

// typedef struct s_game
// {
// 	t_player		*iddle;
// 	t_player		*move;
// 	t_collec		*collect;
// 	t_pos			exit;
// 	t_player		*enemy_i;
// 	t_player		*enemy_m;
// }					t_game;

void			ft_flood_fill(char **map, t_pos init, t_pos final,
					t_game **obj_map);
int				handle_error(t_map error);
t_game			*ft_handle_map(char **map);
void			*ft_mlx_obj(int idx, t_game *game);
int				ft_handle_game(t_game *meta_map);
void			ft_fill_scene(t_game *game);
void			ft_animation_move(char c, int cont, t_game *game);

#endif
