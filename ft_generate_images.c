/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:07:25 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/09 13:48:36 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_init_image(mlx_image_t **imgs, mlx_t *mlx)
{
	mlx_texture_t	*txt[17];
	int				i;

	i = 0;
	txt[0] = mlx_load_png("textures/floor.png");
	txt[1] = mlx_load_png("textures/wall.png");
	txt[2] = mlx_load_png("textures/wall_down.png");
	txt[3] = mlx_load_png("textures/wall_down_el.png");
	txt[4] = mlx_load_png("textures/wall_down_rl.png");
	txt[5] = mlx_load_png("textures/wall_top.png");
	txt[6] = mlx_load_png("textures/wall_top_el.png");
	txt[7] = mlx_load_png("textures/wall_top_rl.png");
	txt[8] = mlx_load_png("textures/wall_r.png");
	txt[9] = mlx_load_png("textures/wall_l.png");
	txt[10] = mlx_load_png("textures/collect.png");
	txt[11] = mlx_load_png("textures/exit_c.png");
	txt[12] = mlx_load_png("textures/exit_o.png");
	txt[13] = mlx_load_png("textures/player_r.png");
	txt[14] = mlx_load_png("textures/player_l.png");
	txt[15] = mlx_load_png("textures/wall_mid.png");
	while (i < 16)
	{
		imgs[i] = mlx_texture_to_image(mlx, txt[i]);
		mlx_delete_texture(txt[i++]);
	}
}

void	ft_resize_img(void)
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
}
