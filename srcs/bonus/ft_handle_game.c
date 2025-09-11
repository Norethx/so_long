/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:55:39 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/11 13:53:20 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	*ft_text_game(mlx_image_t **imgs, mlx_t *mlx, t_game *game);
static void	ft_hook_key(mlx_key_data_t keydata, void *param);

void	*ft_mlx_obj(int idx, t_game *game)
{
	static mlx_t		*mlx = NULL;
	static mlx_image_t	*image[15] = {0};
	static t_player		*child[2] = {0};

	if (!mlx)
		mlx = mlx_init((game->size.x + 1) * WIDTH, (game->size.y + 2) * WIDTH,
				"so_long", false);
	if (!image[1])
		ft_init_image(image, mlx);
	if (!image[14])
		ft_text_game(image, mlx, game);
	if (!child[0])
		ft_init_image_idle_player(&child[0], mlx);
	if (!child[1])
		ft_init_image_idle_patrol(&child[1], mlx);
	if (idx == 15)
		return (mlx);
	else if (idx >= 0 && idx <= 13)
		return (image[idx]);
	else if (idx == 14)
		return (ft_text_game(image, mlx, game));
	else if (idx >= 18 && idx <= 19)
		return (child[idx - 18]);
	else
		return (NULL);
}

static void	*ft_text_game(mlx_image_t **imgs, mlx_t *mlx, t_game *game)
{
	mlx_delete_image(mlx, imgs[14]);
	imgs[14] = mlx_put_string(mlx, ft_gcfct_register(ft_strjoin("Moves: ",
					ft_gcfct_register(ft_itoa(game->mov), GC_DATA)->content),
				GC_DATA)->content, 0, 0);
	return (imgs[14]);
}

static void	ft_hook_key(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;
	t_game	*game;

	game = param;
	mlx = ft_mlx_obj(15, 0);
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(mlx);
		if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			ft_animation_move('y', -WIDTH, game);
		if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			ft_animation_move('y', +WIDTH, game);
		if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			ft_animation_move('x', -WIDTH, game);
		if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			ft_animation_move('x', +WIDTH, game);
	}
}

int	ft_handle_game(t_game *meta_map)
{
	int			i;
	mlx_t		*mlx;
	t_player	*child[2];

	i = 0;
	mlx = ft_fill_scene(meta_map);
	if (!mlx)
		return (1);
	mlx_key_hook(mlx, ft_hook_key, meta_map);
	mlx_loop_hook(mlx, ft_hook_idle, meta_map);
	mlx_loop(mlx);
	child[0] = ft_mlx_obj(18, NULL);
	child[1] = ft_mlx_obj(19, NULL);
	while (i < 15)
		mlx_delete_image(mlx, (mlx_image_t *)ft_mlx_obj(i++, meta_map));
	i = 0;
	while (i < 7)
	{
		mlx_delete_image(mlx, child[0]->idle[i]);
		mlx_delete_image(mlx, child[0]->run[i]);
		mlx_delete_image(mlx, child[1]->idle[i]);
		mlx_delete_image(mlx, child[1]->run[i++]);
	}
	mlx_terminate(mlx);
	return (0);
}
