// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "libft.h"
#include <MLX42/MLX42.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_GRID_WIDTH 32
#define SIZE_GRID_HEIGHT (SIZE_GRID_WIDTH + (SIZE_GRID_WIDTH * 0.75))

// #define SIZE_REAL_HEIGHT SIZE_GRID_HEIGHT + (SIZE_GRID_HEIGHT * 0.75)

static mlx_image_t		*image[4];
static mlx_image_t		*floor;

static mlx_texture_t	*teste[4];
static mlx_texture_t	*t_floor;

// -----------------------------------------------------------------------------

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_randomize(void *param)
{
	(void)param;
	for (uint32_t i = 0; i < image[0]->width; ++i)
	{
		for (uint32_t y = 0; y < image[0]->height; ++y)
		{
			uint32_t color = ft_pixel(rand() % 0xFF, // R
										rand() % 0xFF, // G
										rand() % 0xFF, // B
										rand() % 0xFF  // A
			);
			mlx_put_pixel(image[0], i, y, color);
		}
	}
}

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		ft_printf("up\n");
		image[0]->instances[0].y -= 2;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		ft_printf("down\n");
		image[0]->instances[0].y += 2;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		ft_printf("left\n");
		image[0]->instances[0].x -= 2;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		ft_printf("right\n");
		image[0]->instances[0].x += 2;
	}
}
void	ft_att_move(char c, int cont)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		ft_printf("%d\n%d\n", image[3]->instances[0].x,
			image[3]->instances[0].y);
		image[i]->instances[0].x = image[3]->instances[0].x;
		image[i++]->instances[0].y = image[3]->instances[0].y;
	}
}

void	ft_animation_move(char c, int cont)
{
	double	now[2];
	int		i;

	i = 0;
	now[1] = 0;
	while (i < 4)
	{
		now[0] = mlx_get_time();
		if (now[0] - now[1] > 0.05)
		{
			if (i == 0)
				image[3]->instances[0].enabled = false;
			else
				image[i - 1]->instances[0].enabled = false;
			image[i]->instances[0].enabled = true;
			if (c == 'y')
				image[i]->instances[0].y += (cont / 4) * (i + 1);
			if (c == 'x')
				image[i]->instances[0].x += (cont / 4) * (i + 1);
			if (i++ == 3)
				ft_att_move(c, cont);
			now[1] = now[0];
		}
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
		{
			ft_printf("up\n");
			ft_animation_move('y', -SIZE_GRID_WIDTH);
		}
		if (keydata.key == MLX_KEY_DOWN)
		{
			ft_printf("down\n");
			ft_animation_move('y', +SIZE_GRID_WIDTH);
		}
		if (keydata.key == MLX_KEY_LEFT)
		{
			ft_printf("left\n");
			ft_animation_move('x', -SIZE_GRID_WIDTH);
		}
		if (keydata.key == MLX_KEY_RIGHT)
		{
			ft_printf("right\n");
			ft_animation_move('x', +SIZE_GRID_WIDTH);
		}
	}
}

// -----------------------------------------------------------------------------

int32_t	main(void)
{
	mlx_t	*mlx;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	// Gotta error check this stuff
	teste[0] = mlx_load_png("textures/player_l.png");
	teste[1] = mlx_load_png("textures/player_l.png");
	teste[2] = mlx_load_png("textures/player_l.png");
	teste[3] = mlx_load_png("textures/player_l.png");
	t_floor = mlx_load_png("textures/exit_o.png");
	if (!(mlx = mlx_init(SIZE_GRID_WIDTH * 8, SIZE_GRID_WIDTH * (8 + 1),
				"MLX42", false)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(image[3] = mlx_texture_to_image(mlx, teste[0])))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_resize_image(image[3], SIZE_GRID_WIDTH, SIZE_GRID_HEIGHT);
	if (!(image[1] = mlx_texture_to_image(mlx, teste[1])))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_resize_image(image[1], SIZE_GRID_WIDTH, SIZE_GRID_HEIGHT);
	if (!(image[2] = mlx_texture_to_image(mlx, teste[2])))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_resize_image(image[2], SIZE_GRID_WIDTH, SIZE_GRID_HEIGHT);
	if (!(image[0] = mlx_texture_to_image(mlx, teste[3])))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_resize_image(image[0], SIZE_GRID_WIDTH, SIZE_GRID_HEIGHT);
	if (!(floor = mlx_texture_to_image(mlx, t_floor)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_resize_image(floor, SIZE_GRID_WIDTH, SIZE_GRID_HEIGHT);
	mlx_put_string(mlx, "Teste: x0", SIZE_GRID_WIDTH * 0, SIZE_GRID_WIDTH * 8);
	while (i < 8)
	{
		i2 = 0;
		while (i2 < 8)
			mlx_image_to_window(mlx, floor, SIZE_GRID_WIDTH * i2++,
				SIZE_GRID_WIDTH * i);
		i++;
	}
	mlx_image_to_window(mlx, image[0], SIZE_GRID_WIDTH * 0, SIZE_GRID_HEIGHT
		* 0);
	mlx_image_to_window(mlx, image[1], SIZE_GRID_WIDTH * 0, SIZE_GRID_HEIGHT
		* 0);
	mlx_image_to_window(mlx, image[2], SIZE_GRID_WIDTH * 0, SIZE_GRID_HEIGHT
		* 0);
	mlx_image_to_window(mlx, image[3], SIZE_GRID_WIDTH * 0, SIZE_GRID_HEIGHT
		* 0);
	image[0]->instances[0].enabled = false;
	image[1]->instances[0].enabled = false;
	image[2]->instances[0].enabled = false;
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_key_hook(mlx, ft_hook_key, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
