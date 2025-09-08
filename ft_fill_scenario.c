/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_scenario.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:49:22 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/07 23:40:48 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_build_floor(t_game *game);
static void	ft_build_walls(t_game *game);
static void	ft_fill_edges(t_pos max, int pos);
static void	ft_render_dup(t_game *game, char c, int *img);
static void	ft_render_solo_image_line(t_game *game, int line);
static void	ft_render_child(t_game *game, char c, t_player *child, mlx_t *mlx);

void	ft_fill_scene(t_game *game)
{
	int	img[4];

	img[2] = 0;
	ft_build_floor(game);
	ft_build_walls(game);
	// img[0] = PLAYER_R;
	// img[1] = PLAYER_L;
	ft_render_child(game,'P',ft_mlx_obj(18,NULL),ft_mlx_obj(17,NULL));
	img[0] = EXIT_C;
	img[1] = EXIT_O;
	ft_render_dup(game, 'E', img);
}

static void	ft_render_child(t_game *game, char c, t_player *child, mlx_t *mlx)
{
	int		i[3];

	i[0] = 1;
	i[2] = 0;
	while (i[0] < game->size.y)
	{
		i[1] = 1;
		while (i[1] < game->size.x)
		{
			i[2] = 0;
			if (game->map[i[0]][i[1]] == c)
				while (i[2] < 8)
				{
					if (i[2] == 0)
					{
						mlx_image_to_window(mlx, child->idle[i[2]], i[1] * WIDTH,
							 i[0] * WIDTH);
						mlx_image_to_window(mlx, child->run[i[2]], i[1] * WIDTH,
							 i[0] * WIDTH);
						child->run[i[2]++]->instances->enabled = false;
					}
					else
					{
						mlx_image_to_window(mlx, child->idle[i[2]], i[1] * WIDTH,
							 i[0] * WIDTH);
						mlx_image_to_window(mlx, child->run[i[2]], i[1] * WIDTH,
							 i[0] * WIDTH);
						child->run[i[2]]->instances->enabled = false;
						child->idle[i[2]++]->instances->enabled = false;
					}
				}
			i[1]++;
		}
		i[0]++;
	}
}

static void	ft_render_solo_image_line(t_game *game, int line)
{
	mlx_t	*mlx;
	int		i;

	i = 0;
	mlx = ft_mlx_obj(17, NULL);
	while (i <= game->size.x)
	{
		if (game->map[line][i] == '1' && i != 0 && i != game->size.x)
			mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(15, NULL),
				i * WIDTH, line * WIDTH);
		else if (game->map[line][i] == '1' && i == 0)
			mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(9, NULL),
				i * WIDTH, line * WIDTH);
		else if (game->map[line][i] == '1' && i == game->size.x)
			mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(8, NULL),
				i * WIDTH, line * WIDTH);
		if (game->map[line][i] == 'C')
			mlx_image_to_window(mlx, (mlx_image_t *)ft_mlx_obj(10, NULL),
				i * WIDTH, line * WIDTH);
		i++;
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
			else
			{
				ft_render_solo_image_line(game, i[0]);
				i[1] = game->size.x;
			}
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
