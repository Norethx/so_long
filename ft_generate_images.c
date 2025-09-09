/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:49:50 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/08 20:11:12 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void		ft_render_child(t_game *game, char c, t_player *child,
					mlx_t *mlx);
static t_patrol	*ft_fill_info_patrol(t_player *patrol, int i);
static void		ft_resize_childs(void);
static void		ft_resize_img(void);

void	*ft_fill_scene(t_game *game)
{
	int		img[4];
	mlx_t	*mlx;

	mlx = ft_mlx_obj(17, game);
	if (!mlx)
		return (NULL);
	img[2] = 0;
	ft_build_floor(game);
	ft_build_walls(game);
	ft_render_child(game, 'P', ft_mlx_obj(18, NULL), ft_mlx_obj(17, NULL));
	ft_render_child(game, 'X', ft_mlx_obj(19, NULL), ft_mlx_obj(17, NULL));
	game->patrols = ft_fill_info_patrol(ft_mlx_obj(19, NULL), 0);
	img[0] = EXIT_C;
	img[1] = EXIT_O;
	ft_render_dup(game, 'E', img);
	ft_resize_img();
	return (mlx);
}

static t_patrol	*ft_fill_info_patrol(t_player *patrol, int i)
{
	t_patrol	*info[3];
	t_gc_list	*root;

	if (patrol->idle[0]->count == 0)
		return (NULL);
	root = ft_gc_calloc(1, sizeof(t_patrol), GC_DATA);
	ft_gc_register_root(root, "full_map");
	info[0] = root->content;
	info[0]->idx = i++;
	info[0]->actual = i % 4;
	info[1] = info[0];
	while ((size_t)i < patrol->idle[0]->count)
	{
		root = ft_gc_calloc(1, sizeof(t_patrol), GC_DATA);
		ft_gc_register_root(root, "full_map");
		info[2] = root->content;
		info[2]->idx = i++;
		info[2]->actual = i % 4;
		info[1]->next = info[2];
		info[1] = info[2];
	}
	return (info[0]);
}

static void	ft_render_child(t_game *game, char c, t_player *child, mlx_t *mlx)
{
	int	i[4];

	i[0] = 1;
	while (i[0] < game->size.y)
	{
		i[1] = 1;
		while (i[1] < game->size.x)
		{
			i[2] = 0;
			i[3] = child->idle[0]->count;
			if (game->map[i[0]][i[1]] == c)
				while (i[2] < 8)
				{
					mlx_image_to_window(mlx, child->idle[i[2]], i[1] * WIDTH,
						i[0] * WIDTH);
					mlx_image_to_window(mlx, child->run[i[2]], i[1] * WIDTH,
						i[0] * WIDTH);
					if (i[2] != 0)
						child->idle[i[2]]->instances[i[3]].enabled = false;
					child->run[i[2]++]->instances[i[3]].enabled = false;
				}
			i[1]++;
		}
		i[0]++;
	}
}

static void	ft_resize_img(void)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (i == PLAYER_L || i == PLAYER_R || i == EXIT_C || i == EXIT_O)
			mlx_resize_image((mlx_image_t *)ft_mlx_obj(i, NULL), WIDTH, HEIGHT);
		else if (i == WALL_MID)
			mlx_resize_image((mlx_image_t *)ft_mlx_obj(i, NULL), WIDTH, WIDTH
				+ (WIDTH * 2));
		else if (i == COLLEC)
			mlx_resize_image((mlx_image_t *)ft_mlx_obj(i, NULL), WIDTH, WIDTH
				+ (WIDTH * 0.5));
		else
			mlx_resize_image((mlx_image_t *)ft_mlx_obj(i, NULL), WIDTH, WIDTH);
		i++;
	}
	ft_resize_childs();
}

static void	ft_resize_childs(void)
{
	t_player	*player;
	int			i;

	i = 0;
	player = ft_mlx_obj(18, NULL);
	while (i < 8)
	{
		mlx_resize_image(player->idle[i], WIDTH, HEIGHT);
		mlx_resize_image(player->run[i++], WIDTH, HEIGHT);
	}
	i = 0;
	player = ft_mlx_obj(19, NULL);
	while (i < 8)
	{
		mlx_resize_image(player->idle[i], WIDTH, WIDTH + (WIDTH * 0.5));
		mlx_resize_image(player->run[i++], WIDTH, WIDTH + (WIDTH * 0.5));
	}
}
