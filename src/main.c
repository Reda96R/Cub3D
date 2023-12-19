/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:26:16 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/16 15:26:19 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define MAP_X 9
#define MAP_Y 7

int	g_size = 100;

#define SPACE 1

int	g_test[][9] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 1, 0, 0, 1},
{1, 1, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Define key codes
#define ESCAPE_KEY 65307 // ESC key
#define KEY_W 119  // W key
#define KEY_S 115  // S key
#define KEY_A 97   // A key
#define KEY_D 100   // D key

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*p;

	if (mlx->win_x > x && mlx->win_y > y && x >= 0 && y >= 0)
	{
		p = mlx->img.id + (y * mlx->img.len + x * (mlx->img.bpp / 8));
		*(int *)p = color;
	}
}

void	ft_draw_line(t_mlx *mlx, float x0, float y0, float x1, float y1)
{
	float	max;

	max = fmax(fabs(x1 - x0), fabs(y1 - y0));
	while (max >= 0)
	{
		ft_put_pixel(mlx, x0, y0, 0xFFFF00);
		x0 += (x1 - x0) / (float) max;
		y0 += (y1 - y0) / (float) max;
		max--;
	}
}

void	ft_draw_circle(t_mlx *mlx, int x, int y)
{
	int	i;
	int	j;
	int	dx;
	int	dy;

	i = x - mlx->player->r;
	while (i <= x + mlx->player->r)
	{
		j = y - mlx->player->r;
		while (j <= y + mlx->player->r)
		{
			dx = i - x;
			dy = j - y;
			if (dx * dx + dy * dy <= mlx->player->r * mlx->player->r)
				ft_put_pixel(mlx, i, j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	ft_draw_square(t_mlx *mlx, int x, int y, int color)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	while (w < g_size)
	{
		h = 0;
		while (h < g_size)
		{
			ft_put_pixel(mlx, x + w, y + h, color);
			h++;
		}
		w++;
	}
}

void	ft_clear_map(t_mlx *mlx)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (i < MAP_Y)
	{
		x = 0;
		j = 0;
		while (j < MAP_X)
		{
			ft_draw_square(mlx, x, y, 0x000000);
			x += g_size;
			j++;
		}
		y += g_size;
		i++;
	}
}

void	ft_draw_map(t_mlx *mlx)
{
	int	i;
	int	j;
	int	x;
	int	y;

	ft_clear_map(mlx);
	i = 0;
	y = 0;
	while (i < MAP_Y)
	{
		x = 0;
		j = 0;
		while (j < MAP_X)
		{
			if (g_test[i][j])
				ft_draw_square(mlx, x, y, 0xFFFFFF);
			else
				ft_draw_square(mlx, x, y, 0x000000);
			x += g_size + SPACE;
			j++;
		}
		y += g_size + SPACE;
		i++;
	}
}

void	ft_clear_player(t_mlx *mlx, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_put_pixel(mlx, x + i, y + j, 0x000000);
			j++;
		}
		i++;
	}
}

void	ft_draw_player(t_mlx *mlx, int x, int y)
{
	int	xf;
	int	yf;
	// int	s;
	mlx->player->rot += (mlx->player->turn * mlx->player->rot_spd);
	mlx->player->turn = 0;
	xf = x + cos (mlx->player->rot) * 40;
	yf = y + sin (mlx->player->rot) * 40;
	// g_size = 45;
	ft_draw_circle(mlx, x, y);
	ft_draw_line(mlx, x, y, xf, yf);
	// s = g_size;
	// ft_draw_square(mlx, x, y, 0xFF0000);
	// g_size = s;
}

int	key_press(int keycode, t_mlx *mlx)
{
	ft_clear_player(mlx->mlx_ptr, mlx->player->x, mlx->player->y, 45);
	if (keycode == KEY_W)
		mlx->player->walk = 1;
	else if (keycode == KEY_S)
		mlx->player->walk = -1;
	else if (keycode == KEY_A)
		mlx->player->turn = -1;
	else if (keycode == KEY_D)
		mlx->player->turn = 1;
	else if (keycode == ESCAPE_KEY)
		exit (0);

	// if (keycode == KEY_W)
	// 	mlx->player->y -= mlx->player->spd;
	// else if (keycode == KEY_S)
	// 	mlx->player->y += mlx->player->spd;
	// else if (keycode == KEY_A)
	// 	mlx->player->x -= mlx->player->spd;
	// else if (keycode == KEY_D)
	// 	mlx->player->x += mlx->player->spd;
	// else if (keycode == ESCAPE_KEY)
	// 	exit (0);
	return (0);
}

int	update(t_mlx *mlx)
{
	ft_draw_map(mlx);
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	return (0);
}

int	ft_player_init(t_player **player, int x, int y)
{
	*player = malloc (sizeof (t_player));
	if (!player)
		return (0);
	(*player)->x = x;
	(*player)->y = y;
	(*player)->r = 15;
	(*player)->spd = 5;
	(*player)->walk = 0;
	(*player)->turn = 0;
	(*player)->rot = -M_PI / 2;
	(*player)->rot_spd = 5 * (M_PI / 180);
	return (1);
}

int	ft_canvas_maker(t_mlx *mlx)
{
	mlx = malloc (sizeof (t_mlx));
	if (!mlx)
	{
		//error msg;
		exit (1);
	}
	mlx->win_x = (g_size + SPACE) * MAP_X;
	mlx->win_y = (g_size + SPACE) * MAP_Y;
	if (!ft_player_init(&mlx->player, mlx->win_x / 2, mlx->win_y / 2))
	{
		free(mlx);
		//error msg;
		exit (1);
	}
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		//error msg;
		exit (1);
	}
	mlx->win_ptr = \
			mlx_new_window(mlx->mlx_ptr, mlx->win_x, mlx->win_y, "cub3D");
	if (!mlx->win_ptr)
	{
		//error msg;
		exit (1);
	}
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, mlx->win_x, mlx->win_y);
	mlx->img.id = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.len, \
	&mlx->img.endian);
	ft_draw_map(mlx);
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, key_press, mlx);
	mlx_loop_hook(mlx->mlx_ptr, update, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (1);
}

int	main(void)
{
	t_mlx	mlx;

	if (!ft_canvas_maker(&mlx))
		return (1);
	return (0);
}
