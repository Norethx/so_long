/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_scenario.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:49:22 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/05 20:51:16 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_build_floor(t_game *game);
static void	ft_build_walls(t_game *game);
static void	ft_fill_edges(t_pos max, int pos);
static void	ft_render_solo_image(t_game *game, char c, int img);
static void	ft_render_dup(t_game *game, char c, int *img);

void	ft_fill_scene(t_game *game)
{
	int	img[2];

	ft_build_floor(game);
	ft_build_walls(game);
	img[0] = PLAYER_R;
	img[1] = PLAYER_L;
	ft_render_dup(game, 'P', img);
	img[0] = EXIT_C;
	img[1] = EXIT_O;
	ft_render_dup(game, 'E', img);
	ft_render_solo_image(game, '1', WALL_MID);
	ft_render_solo_image(game, 'C', COLLEC);
}

static void	ft_render_solo_image(t_game *game, char c, int img)
{
	mlx_t	*mlx;
	int		i[2];

	i[0] = 1;
	mlx = ft_mlx_obj(17, NULL);
	while (i[0] < game->size.y)
	{
		i[1] = 1;
		while (i[1] < game->size.x)
		{
			if (game->map[i[0]][i[1]] == c && c == 'C')
				mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(img, NULL),
					i[1] * WIDTH, i[0] * WIDTH);
			else if (game->map[i[0]][i[1]] == c)
				mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(img, NULL),
					i[1] * WIDTH, i[0] * WIDTH);
			i[1]++;
		}
		i[0]++;
	}
}

static void	ft_render_dup(t_game *game, char c, int *img)
{
	mlx_t	*mlx;
	int		i[2];

	i[0] = 1;
	mlx = ft_mlx_obj(17, NULL);
	while (i[0] < game->size.y)
	{
		i[1] = 1;
		while (i[1] < game->size.x)
		{
			if (game->map[i[0]][i[1]] == c)
			{
				mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(img[0],
						game), i[1] * WIDTH, i[0] * WIDTH);
				mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(img[1],
						game), i[1] * WIDTH, i[0] * WIDTH);
				((mlx_image_t *)ft_mlx_obj(img[1],
							game))->instances[0].enabled = false;
				return ;
			}
			i[1]++;
		}
		i[0]++;
	}
}

static void	ft_build_floor(t_game *game)
{
	mlx_t	*mlx;
	int		i[2];

	i[0] = 0;
	mlx = ft_mlx_obj(17, NULL);
	while (i[0] <= game->size.y)
	{
		i[1] = 0;
		while (i[1] <= game->size.x)
		{
			if (i[0] > 0)
				mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(0, NULL),
					i[1]++ * WIDTH, i[0] * WIDTH);
			else
			{
				if (i[1] == 0)
					mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(5, NULL),
						i[1]++ * WIDTH, i[0] * WIDTH);
				else
					mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(2, NULL),
						i[1]++ * WIDTH, i[0] * WIDTH);
			}
		}
		i[0]++;
	}
}

static void	ft_build_walls(t_game *game)
{
	mlx_t	*mlx;
	int		i[2];

	i[0] = 0;
	mlx = ft_mlx_obj(17, NULL);
	while (i[0] <= game->size.y)
	{
		i[1] = 0;
		while (i[1] <= game->size.x)
		{
			if (i[0] == 0 || i[0] == game->size.y)
				mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(WALL, NULL),
					i[1] * WIDTH, (i[0] + 1) * WIDTH);
			else if (i[1] == 0 && i[0] && i[0] != game->size.y)
				mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(WALL_L,
						NULL), i[1] * WIDTH, i[0] * WIDTH);
			else if (i[1] == game->size.x && i[0] && i[0] != game->size.y)
				mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(WALL_R,
						NULL), i[1] * WIDTH, i[0] * WIDTH);
			i[1]++;
		}
		if (i[0] == 0 || i[0] == game->size.y)
			ft_fill_edges(game->size, i[0]);
		i[0]++;
	}
}

static void	ft_fill_edges(t_pos max, int pos)
{
	mlx_t	*mlx;
	int		i;

	mlx = ft_mlx_obj(17, NULL);
	i = 1;
	if (max.y == pos)
	{
		mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(WALL_DOWN_EL, NULL),
			0 * WIDTH, pos * WIDTH);
		mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(WALL_DOWN_ER, NULL),
			max.x * WIDTH, pos * WIDTH);
	}
	if (pos == 0)
	{
		mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(WALL_TOP_EL, NULL), 0
			* WIDTH, (pos + 1) * WIDTH);
		mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(WALL_TOP_ER, NULL),
			max.x * WIDTH, (pos + 1) * WIDTH);
	}
	while (pos == max.y && i < max.x)
		mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(WALL_DOWN, NULL), i++
			* WIDTH, pos * WIDTH);
}
