/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:55:39 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/07 01:44:12 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_init_image(mlx_image_t **imgs, mlx_t *mlx);
static void	ft_hook_key(mlx_key_data_t keydata, void *param);
static void	ft_animation_move(char c, int cont, t_game *game);
static void	ft_walk(mlx_image_t **player, char c, int cont, t_game *game);
static void *ft_text_game(mlx_image_t **imgs, mlx_t *mlx, t_game *game);
static	void verify_walls(mlx_image_t **player, mlx_instance_t *ist_w, size_t count);
static void ft_resize_img(void);
static void	ft_hook_idle(void *param);
static void	ft_hook_idle_aux(t_game	*game);

void	ft_hook_idle(void *param)
{
	int			i[2];
	mlx_image_t	*collec;
	mlx_image_t	*player;

	i[0] = 0;
	i[1] = 0;
	collec = ft_mlx_obj(COLLEC, NULL);
	player = ft_mlx_obj(PLAYER_R, NULL);
	while (i[0] < ((t_game *)param)->collect->qt)
	{
		if (collec->instances[i[0]].enabled
			&& (player->instances[0].x == collec->instances[i[0]].x
				&& player->instances[0].y == (collec->instances[i[0]].y)))
		{
			collec->instances[i[0]].enabled = false;
			((t_game *)param)->qt_col--;
			ft_mlx_obj(16, param);
			ft_gc_collect();
		}
		i[0]++;
	}
	ft_hook_idle_aux(param);
}

void	ft_hook_idle_aux(t_game	*game)
{
	mlx_image_t	*exit[2];
	mlx_t		*mlx;
	mlx_image_t	*player;

	mlx = ft_mlx_obj(17, NULL);
	exit[0] = ft_mlx_obj(EXIT_C, NULL);
	exit[1] = ft_mlx_obj(EXIT_O, NULL);
	player = ft_mlx_obj(PLAYER_R, NULL);
	if (game->qt_col == 0 && !exit[1]->instances[0].enabled)
	{
		exit[0]->instances[0].enabled = false;
		exit[1]->instances[0].enabled = true;
		game->map[game->end.y][game->end.x] = '0';
	}
	if (exit[1]->instances[0].enabled
		&& (player->instances[0].x == exit[1]->instances[0].x
			&& player->instances[0].y == (exit[1]->instances[0].y)))
	{
		ft_printf("\nCongratulations! You won!!");
		mlx_close_window(mlx);
	}
}

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
		image[16] = mlx_put_string(mlx,
				ft_gcfct_register(ft_strjoin("collectables: ",
						ft_gcfct_register(ft_itoa(game->qt_col),
							GC_DATA)->content), GC_DATA)->content, 0, 0);
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


static void *ft_text_game(mlx_image_t **imgs, mlx_t *mlx, t_game *game)
{
	mlx_delete_image(mlx, imgs[16]); 
	imgs[16] = mlx_put_string(mlx, ft_gcfct_register(ft_strjoin("collectables: ",
			ft_gcfct_register(ft_itoa(game->qt_col), GC_DATA)->content),
				 GC_DATA)->content, 0, 0);
	return (imgs[16]);
}

static void	ft_init_image(mlx_image_t **imgs, mlx_t *mlx)
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

static void	ft_hook_key(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;
	t_game	*game;

	game = param;
	mlx = ft_mlx_obj(17, 0);
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

static void	ft_animation_move(char c, int cont, t_game *game)
{
	mlx_image_t	*player[2];
	mlx_image_t	*wall_m;

	player[0] = ft_mlx_obj(13, NULL);
	player[1] = ft_mlx_obj(14, NULL);
	wall_m = ft_mlx_obj(WALL_MID, NULL);
	ft_walk(player, c, cont, game);
	if (cont < 0)
		player[0]->instances[0].enabled = false;
	if (cont < 0)
		player[1]->instances[0].enabled = true;
	else
	{
		player[0]->instances[0].enabled = true;
		player[1]->instances[0].enabled = false;
	}
	player[1]->instances[0].x = player[0]->instances[0].x;
	player[1]->instances[0].y = player[0]->instances[0].y;
	verify_walls(player, wall_m->instances, wall_m->count);
}

static	void verify_walls(mlx_image_t **player, mlx_instance_t *ist_w, size_t count)
{
	int	i;

	i = 0;
	while ((size_t)i < count)
	{
		if (ist_w[i].y - WIDTH == player[1]->instances[0].y 
			&& ist_w[i].x == player[1]->instances[0].x)
		{
			mlx_set_instance_depth(&player[0]->instances[0], ist_w[i].z - 3);
			mlx_set_instance_depth(&player[1]->instances[0], ist_w[i].z - 3);
		}
		if (ist_w[i].y + WIDTH == player[1]->instances[0].y 
			&& ist_w[i].x == player[1]->instances[0].x)
		{
			mlx_set_instance_depth(&player[0]->instances[0], ist_w[i].z + 3);
			mlx_set_instance_depth(&player[1]->instances[0], ist_w[i].z + 3);
		}
		else if (ist_w[i].y + (WIDTH * 2) == player[1]->instances[0].y 
			&& ist_w[i].x == player[1]->instances[0].x)
		{
			mlx_set_instance_depth(&player[0]->instances[0], ist_w[i].z + 3);
			mlx_set_instance_depth(&player[1]->instances[0], ist_w[i].z + 3);
		}
		i++;
	}
}

static void	ft_walk(mlx_image_t **player, char c, int cont, t_game *game)
{
	char		**map;
	t_root_list	*r_map;

	r_map = ft_gc_call_root("full_map");
	map = ((t_gc_list *)ft_to_root_list(r_map)->lst->head->content)->content;
	if (c == 'y')
	{
		if (ft_strchr("1E", map[(player[0]->instances[0].y + cont)
				/ WIDTH][player[0]->instances[0].x / WIDTH]))
			return ;
		player[0]->instances[0].y += cont;
		game->mov++;
		ft_printf("Moves: %d\n", game->mov);
	}
	if (c == 'x')
	{
		if (ft_strchr("1E", map[player[0]->instances[0].y
				/ WIDTH][(player[0]->instances[0].x + cont) / WIDTH]))
			return ;
		player[0]->instances[0].x += cont;
		game->mov++;
		ft_printf("Moves: %d\n", game->mov);
	}
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

static void ft_resize_img(void)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (i == PLAYER_L || i == PLAYER_R || i == EXIT_C || i == EXIT_O)
			mlx_resize_image((mlx_image_t *)ft_mlx_obj(i, NULL), WIDTH,
				HEIGHT);
		else if (i == WALL_MID)
			mlx_resize_image((mlx_image_t *)ft_mlx_obj(i, NULL), WIDTH,
				WIDTH + (WIDTH * 2));
		else if (i == COLLEC)
			mlx_resize_image((mlx_image_t *)ft_mlx_obj(i, NULL), WIDTH,
				WIDTH + (WIDTH * 0.5));
		else
			mlx_resize_image((mlx_image_t *)ft_mlx_obj(i, NULL), WIDTH,
				WIDTH);
		i++;
	}
}
