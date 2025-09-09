/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upload_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:01:01 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/08 19:49:15 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_init_image_idle_patrol(t_player **imgs, mlx_t *mlx)
{
	mlx_texture_t	*txt[8];
	t_gc_list		*child;
	int				i;

	i = 0;
	child = ft_gc_calloc(1, sizeof(t_player), GC_DATA);
	ft_gc_register_root(child, "full_map");
	imgs[0] = child->content;
	txt[0] = mlx_load_png("textures/x/patrol_l_0.png");
	txt[1] = mlx_load_png("textures/x/patrol_l_1.png");
	txt[2] = mlx_load_png("textures/x/patrol_l_2.png");
	txt[3] = mlx_load_png("textures/x/patrol_l_3.png");
	txt[4] = mlx_load_png("textures/x/patrol_r_0.png");
	txt[5] = mlx_load_png("textures/x/patrol_r_1.png");
	txt[6] = mlx_load_png("textures/x/patrol_r_2.png");
	txt[7] = mlx_load_png("textures/x/patrol_r_3.png");
	while (i < 8)
	{
		imgs[0]->idle[i] = mlx_texture_to_image(mlx, txt[i]);
		mlx_delete_texture(txt[i++]);
	}
	ft_init_image_run_patrol(imgs, mlx);
}

void	ft_init_image_run_patrol(t_player **imgs, mlx_t *mlx)
{
	mlx_texture_t	*txt[8];
	int				i;

	i = 0;
	txt[0] = mlx_load_png("textures/x/patrol_runl_0.png");
	txt[1] = mlx_load_png("textures/x/patrol_runl_1.png");
	txt[2] = mlx_load_png("textures/x/patrol_runl_2.png");
	txt[3] = mlx_load_png("textures/x/patrol_runl_3.png");
	txt[4] = mlx_load_png("textures/x/patrol_runr_0.png");
	txt[5] = mlx_load_png("textures/x/patrol_runr_1.png");
	txt[6] = mlx_load_png("textures/x/patrol_runr_2.png");
	txt[7] = mlx_load_png("textures/x/patrol_runr_3.png");
	while (i < 8)
	{
		imgs[0]->run[i] = mlx_texture_to_image(mlx, txt[i]);
		mlx_delete_texture(txt[i++]);
	}
}

void	ft_init_image_idle_player(t_player **imgs, mlx_t *mlx)
{
	mlx_texture_t	*txt[8];
	t_gc_list		*child;
	int				i;

	i = 0;
	child = ft_gc_calloc(1, sizeof(t_player), GC_DATA);
	ft_gc_register_root(child, "full_map");
	imgs[0] = child->content;
	txt[0] = mlx_load_png("textures/p/player_l_0.png");
	txt[1] = mlx_load_png("textures/p/player_l_1.png");
	txt[2] = mlx_load_png("textures/p/player_l_2.png");
	txt[3] = mlx_load_png("textures/p/player_l_3.png");
	txt[4] = mlx_load_png("textures/p/player_r_0.png");
	txt[5] = mlx_load_png("textures/p/player_r_1.png");
	txt[6] = mlx_load_png("textures/p/player_r_2.png");
	txt[7] = mlx_load_png("textures/p/player_r_3.png");
	while (i < 8)
	{
		imgs[0]->idle[i] = mlx_texture_to_image(mlx, txt[i]);
		mlx_delete_texture(txt[i++]);
	}
	ft_init_image_run_player(imgs, mlx);
}

void	ft_init_image_run_player(t_player **imgs, mlx_t *mlx)
{
	mlx_texture_t	*txt[8];
	int				i;

	i = 0;
	txt[0] = mlx_load_png("textures/p/player_runl_0.png");
	txt[1] = mlx_load_png("textures/p/player_runl_1.png");
	txt[2] = mlx_load_png("textures/p/player_runl_2.png");
	txt[3] = mlx_load_png("textures/p/player_runl_3.png");
	txt[4] = mlx_load_png("textures/p/player_runr_0.png");
	txt[5] = mlx_load_png("textures/p/player_runr_1.png");
	txt[6] = mlx_load_png("textures/p/player_runr_2.png");
	txt[7] = mlx_load_png("textures/p/player_runr_3.png");
	while (i < 8)
	{
		imgs[0]->run[i] = mlx_texture_to_image(mlx, txt[i]);
		mlx_delete_texture(txt[i++]);
	}
}

void	ft_init_image(mlx_image_t **imgs, mlx_t *mlx)
{
	mlx_texture_t	*txt[16];
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
