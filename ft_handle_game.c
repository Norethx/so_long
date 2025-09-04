/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:55:39 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/04 20:46:25 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_mlx_obj(t_mlx_init idx)
{
	static mlx_t		*mlx = NULL;
	static mlx_image_t	*image[15] = {0};
	int					i;

	i = 0;
	if (!mlx)
		mlx = mlx_init(idx.max_wid * WIDTH, idx.max_hei * WIDTH, "so_long",
				false);
	if (!image)
		ft_init_image(image, mlx);
	while (i < 15)
	{
		if (!image[i])
		{
			mlx_close_window(mlx);
			ft_printf("Error: texture no load");
			return (NULL);
		}
	}
	if (idx.idx == 15)
		return (mlx);
	else if (idx.idx >= 0 && idx.idx <= 14)
		return (image[idx.idx]);
	else
		return (NULL);
}

static void	*ft_init_image(mlx_image_t **imgs, mlx_t *mlx)
{
	mlx_texture_t	*txt[15];
	int				i;

	i = 0;
	txt[0] = mlx_load_png("floor.png");
	txt[1] = mlx_load_png("wall.png");
	txt[2] = mlx_load_png("wall_down.png");
	txt[3] = mlx_load_png("wall_down_el.png");
	txt[4] = mlx_load_png("wall_down_rl.png");
	txt[5] = mlx_load_png("wall_top.png");
	txt[6] = mlx_load_png("wall_top_el.png");
	txt[7] = mlx_load_png("wall_top_rl.png");
	txt[8] = mlx_load_png("wall_r.png");
	txt[9] = mlx_load_png("wall_l.png");
	txt[10] = mlx_load_png("collec.png");
	txt[11] = mlx_load_png("exit_c.png");
	txt[12] = mlx_load_png("exit_c.png");
	txt[13] = mlx_load_png("player_r");
	txt[14] = mlx_load_png("player_l");
	while (i < 15)
	{
		imgs[i] = mlx_texture_to_image(mlx, txt[i]);
		i++;
	}
}

void	ft_hook_key(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(mlx);
		if (mlx_is_key_down(mlx, MLX_KEY_UP))
			ft_animation_move('y', -WIDTH);
		if (keydata.key == MLX_KEY_DOWN)
			ft_animation_move('y', +WIDTH);
		if (keydata.key == MLX_KEY_LEFT)
			ft_animation_move('x', -WIDTH);
		if (keydata.key == MLX_KEY_RIGHT)
			ft_animation_move('x', +WIDTH);
	}
}

void	ft_animation_move(char c, int cont)
{
	mlx_image_t	*player[2];
	t_mlx_init	data;

	ft_bzero(&data, sizeof(t_mlx_init));
	data.idx = PLAYER_L;
	player[0] = ft_mlx_obj(data);
	data.idx = PLAYER_R;
	player[1] = ft_mlx_obj(data);
	ft_walk(player, c, cont);
	if (cont < 0)
	{
		player[0]->instances[0].enabled = false;
		player[1]->instances[0].enabled = true;
	}
	else
	{
		player[0]->instances[0].enabled = true;
		player[1]->instances[0].enabled = false;
	}
	player[1]->instances[0].x = player[0]->instances[0].x;
	player[1]->instances[0].y = player[0]->instances[0].y;
}

void	ft_walk(mlx_image_t **player, char c, int cont)
{
	char	**map;

	map = ((t_gc_list *)ft_gc_call_root("full_map")->lst->head->content)->content;
	if (c == 'y')
	{
		if (map[player[0]->instances[0].y
			+ cont][player[0]->instances[0].x] == '1')
			return ;
		player[0]->instances[0].y += cont;
	}
	if (c == 'x')
	{
		if (map[player[0]->instances[0].y
			+ cont][player[0]->instances[0].x] == '1')
			return ;
		player[0]->instances[0].x += cont;
	}
}

int	teste(t_obj_map meta_map)
{
	t_mlx_init	data;
	mlx_t		*mlx;
	int			i;

	i = 0;
	ft_bzero(&data, sizeof(t_mlx_init));
	data.idx = 15;
	mlx = ft_mlx_obj(data);
	if (!mlx)
		return (1);
	while (i < 15)
	{
		data.idx = i++;
		if (i == PLAYER_L || i == PLAYER_R || i == EXIT_C || i == EXIT_O)
			mlx_resize_image((mlx_image_t *)ft_mlx_obj(data), WIDTH, HEIGHT);
		else
			mlx_resize_image((mlx_image_t *)ft_mlx_obj(data), WIDTH, WIDTH);
	}
	ft_init_game();
	ft_build_floor();
	ft_build_wall();
	ft_build_collects();
	ft_build_exit();
	ft_build_player();
	mlx_key_hook(mlx, ft_hook_key, mlx);
	mlx_loop(mlx);
	mlx_kill_image();
	mlx_terminate(mlx);
	return (meta_map.others_char);
}

// void	hook(void *param)
// {
// 	mlx_t	*mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_P))
// 		mlx_delete_image(mlx, g_img);
// 	for (int x = 0; x < (int)g_img->width; x++)
// 		for (int y = 0; y < (int)g_img->height; y++)
// 			mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
// }
