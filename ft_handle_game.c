/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:55:39 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/09 14:02:03 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*ft_text_game(mlx_image_t **imgs, mlx_t *mlx, t_game *game);

void	*ft_mlx_obj(int idx, t_game *game)
{
	static mlx_t		*mlx = NULL;
	static mlx_image_t	*image[17] = {0};

	if (!mlx)
		mlx = mlx_init((game->size.x + 1) * WIDTH, (game->size.y + 2) * WIDTH,
				"so_long", false);
	if (!image[1])
	{
		ft_init_image(image, mlx);
		ft_text_game(image, mlx, game);
	}
	if (idx == 17)
		return (mlx);
	else if (idx >= 0 && idx <= 15)
		return (image[idx]);
	else if (idx == 16)
		return (ft_text_game(image, mlx, game));
	else
		return (NULL);
}

static void	*ft_text_game(mlx_image_t **imgs, mlx_t *mlx, t_game *game)
{
	mlx_delete_image(mlx, imgs[16]);
	imgs[16] = mlx_put_string(mlx,
			ft_gcfct_register(ft_strjoin("collectables: ",
					ft_gcfct_register(ft_itoa(game->qt_col), GC_DATA)->content),
				GC_DATA)->content, 0, 0);
	return (imgs[16]);
}

void	ft_fill_scene(t_game *game)
{
	int	img[4];

	img[2] = 0;
	ft_build_floor(game);
	ft_build_walls(game);
	img[0] = PLAYER_R;
	img[1] = PLAYER_L;
	ft_render_dup(game, 'P', img);
	img[0] = EXIT_C;
	img[1] = EXIT_O;
	ft_render_dup(game, 'E', img);
}

int	ft_handle_game(t_game *meta_map)
{
	int		i;
	mlx_t	*mlx;

	i = 0;
	mlx = ft_mlx_obj(17, meta_map);
	if (!mlx)
		return (1);
	ft_resize_img();
	ft_fill_scene(meta_map);
	mlx_key_hook(mlx, ft_hook_key, meta_map);
	mlx_loop_hook(mlx, ft_hook_idle, meta_map);
	mlx_loop(mlx);
	while (i < 17)
		mlx_delete_image(mlx, (mlx_image_t *)ft_mlx_obj(i++, meta_map));
	mlx_terminate(mlx);
	return (0);
}
