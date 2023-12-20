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

#define SPACE 1

int	g_size = 100;

// Define key codes
#define ESCAPE_KEY 65307 // ESC key
#define KEY_W 119  // W key
#define KEY_S 115  // S key
#define KEY_A 97   // A key
#define KEY_D 100   // D key
#define KEY_L_A 65361 
#define KEY_R_A 65363 
// int	g_test[][9] = {
// {1, 1, 1, 1, 1, 1, 1, 1, 1},
// {1, 0, 0, 0, 0, 1, 0, 0, 1},
// {1, 1, 1, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 1, 1, 1, 1, 1, 1, 1, 1}
// };

char  g_test[][9] = {
{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '0', '0', '1', '0', '0', '1'},
{'1', '1', '1', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

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
			if (g_test[i][j] != '0')
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

	xf = x + cos (mlx->player->rot) * (mlx->player->r * 2);
	yf = y + sin (mlx->player->rot) * (mlx->player->r * 2);
	ft_draw_circle(mlx, x, y);
	ft_draw_line(mlx, x, y, xf, yf);
}

int	ft_wall_detector(float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / g_size);
	map_y = floor(y / g_size);
	if (g_test[map_x][map_y] == '0')
		return (0);
	return (1);
}

int	ft_pos_update(t_mlx *mlx)
{
	float	x;
	float	y;

	x = mlx->player->x;
	y = mlx->player->y;
	if (mlx->player->m_f)
	{
		mlx->player->x += cos(mlx->player->rot) * mlx->player->spd;
		mlx->player->y += sin(mlx->player->rot) * mlx->player->spd;
	}
	if (mlx->player->m_b)
	{
		mlx->player->x -= cos(mlx->player->rot) * mlx->player->spd;
		mlx->player->y -= sin(mlx->player->rot) * mlx->player->spd;
	}
	if (mlx->player->m_l)
	{
		mlx->player->x -= cos(mlx->player->rot + M_PI_2) * mlx->player->spd;
		mlx->player->y -= sin(mlx->player->rot + M_PI_2) * mlx->player->spd;
	}
	if (mlx->player->m_r)
	{
		mlx->player->x += cos(mlx->player->rot + M_PI_2) * mlx->player->spd;
		mlx->player->y += sin(mlx->player->rot + M_PI_2) * mlx->player->spd;
	}
	if (mlx->player->t_l)
		mlx->player->rot -= mlx->player->rot_spd;
	if (mlx->player->t_r)
		mlx->player->rot += mlx->player->rot_spd;
	if (ft_wall_detector(mlx->player->x, mlx->player->y))
	{
		mlx->player->x = x;
		mlx->player->y = y;
		// mlx->player->rot = r;
	}
	return (1);
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
		mlx->player->m_f = 1;
	else if (keycode == KEY_S)
		mlx->player->m_b = 1;
	else if (keycode == KEY_A)
		mlx->player->m_l = 1;
	else if (keycode == KEY_D)
		mlx->player->m_r = 1;
	else if (keycode == KEY_L_A)
		mlx->player->t_l = 1;
	else if (keycode == KEY_R_A)
		mlx->player->t_r = 1;
	else if (keycode == ESCAPE_KEY)
		exit (0);
	return (0);
}

int	key_release(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
		mlx->player->m_f = 0;
	else if (keycode == KEY_S)
		mlx->player->m_b = 0;
	else if (keycode == KEY_A)
		mlx->player->m_l = 0;
	else if (keycode == KEY_D)
		mlx->player->m_r = 0;
	else if (keycode == KEY_L_A)
		mlx->player->t_l = 0;
	else if (keycode == KEY_R_A)
		mlx->player->t_r = 0;
	return (0);
}

int	update(t_mlx *mlx)
{
	ft_draw_map(mlx);
	ft_pos_update(mlx);
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
	(*player)->spd = 1;
	(*player)->walk = 0;
	(*player)->turn = 0;
	(*player)->rot = -M_PI_2;
	(*player)->rot_spd = 1 * (M_PI / 180);
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
	mlx_hook(mlx->win_ptr, 3, 1L << 1, key_release, mlx);
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
