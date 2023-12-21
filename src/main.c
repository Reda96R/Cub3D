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

// int	mlx->test[][9] = {
// {1, 1, 1, 1, 1, 1, 1, 1, 1},
// {1, 0, 0, 0, 0, 1, 0, 0, 1},
// {1, 1, 1, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 1, 1, 1, 1, 1, 1, 1, 1}
// };

char	g_test[][9] = {
{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '0', '0', '1', '0', '0', '1'},
{'1', '1', '1', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

int	ft_wall_detector(float x, float y, char test[7][9])
{
	int	map_x;
	int	map_y;

	map_x = floor(y / CUB_SIZE);
	map_y = floor(x / CUB_SIZE);
	if (test[map_x][map_y] == '0')
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
	if (ft_wall_detector(mlx->player->x, mlx->player->y, mlx->test))
	{
		mlx->player->x = x;
		mlx->player->y = y;
	}
	return (1);
}

int	update(t_mlx *mlx)
{
	ft_draw_map(mlx);
	ft_pos_update(mlx);
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	return (0);
}

void	ft_player_init(t_player **player, int x, int y)
{
	*player = malloc (sizeof (t_player));
	// if (!player)
	// 	ft_janitor();
	(*player)->x = x;
	(*player)->y = y;
	(*player)->r = RADIUS;
	(*player)->spd = SPEED;
	(*player)->walk = 0;
	(*player)->turn = 0;
	(*player)->rot = -M_PI_2;
	(*player)->rot_spd = ROT_SPEED * (M_PI / 180);
}

t_mlx	*ft_game_init()
{
	t_mlx	*mlx;

	mlx = malloc (sizeof (t_mlx));
	// if (!mlx)
	// 	ft_janitor();
	mlx->win_x = (CUB_SIZE + SPACE) * MAP_X;
	mlx->win_y = (CUB_SIZE + SPACE) * MAP_Y;
	ft_player_init(&mlx->player, mlx->win_x / 2, mlx->win_y / 2);
	mlx->mlx_ptr = mlx_init();
	// if (!mlx->mlx_ptr)
	// 	ft_janitor();
	mlx->win_ptr = \
			mlx_new_window(mlx->mlx_ptr, mlx->win_x, mlx->win_y, "cub3D");
	// if (!mlx->win_ptr)
	// 	ft_janitor();
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, mlx->win_x, mlx->win_y);
	mlx->img.id = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.len, \
	&mlx->img.endian);
	return (mlx);
}

void	ft_canvas_maker(t_mlx *mlx)
{
	memcpy(mlx->test, g_test, sizeof (g_test)); // will be removed
	ft_draw_map(mlx);
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, ft_key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, ft_key_release, mlx);
	mlx_loop_hook(mlx->mlx_ptr, update, mlx);
	mlx_loop(mlx->mlx_ptr);
}

int	main(void)
{
	t_mlx	*mlx;

	mlx = ft_game_init();
	ft_canvas_maker(mlx);
	return (0);
}
