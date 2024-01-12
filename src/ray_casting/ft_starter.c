/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_starter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:53:15 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/12 08:59:17 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_mlx	*ft_data_init(char *av[])
{
	t_mlx	*mlx;

	ft_mlx_init(&mlx);
	ft_player_init(&mlx->player);
	ft_rays_init(&mlx->rays, mlx);
	ft_file_parser(mlx, av[1]);
	ft_map_parser(mlx);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		ft_error_buster(2);
	mlx->win_ptr = \
			mlx_new_window(mlx->mlx_ptr, mlx->win_x, mlx->win_y, "cub3D");
	if (!mlx->win_ptr)
		ft_error_buster(2);
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, mlx->win_x, mlx->win_y);
	mlx->img.id = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.len, &mlx->img.endian);
	// The value of map width is not correct, it always bigger by one, correct it and be aware
	// of any buffer-overflows that can result from that
	ft_textures_init(mlx);
	printf("map_height = %d\n", mlx->map_height);  //// ------> will be removed
	printf("map_width = %d\n", mlx->map_width);    //// ------->will be removed
	ft_free(mlx->map);
	return (mlx);
}

void	ft_mlx_init(t_mlx **mlx)
{
	*mlx = malloc (sizeof (t_mlx));
	if (!(*mlx))
		ft_error_buster(1);
	(*mlx)->win_x = 1337;//(CUB_SIZE + SPACE) * MAP_X;
	(*mlx)->win_y = 800;//(CUB_SIZE + SPACE) * MAP_Y;
	(*mlx)->east_texture = NULL;
	(*mlx)->west_texture = NULL;
	(*mlx)->south_texture = NULL;
	(*mlx)->north_texture = NULL;
	(*mlx)->c_color = NULL;
	(*mlx)->f_color = NULL;
	(*mlx)->map = NULL;
	(*mlx)->full_file = NULL;
	(*mlx)->new_map = NULL;
	(*mlx)->map_height = 0;
	(*mlx)->map_width = 0;
	(*mlx)->c_color_int = 0;
	(*mlx)->f_color_int = 0;
}

void	ft_rays_init(t_rays **rays, t_mlx *mlx)
{
	*rays = malloc (sizeof (t_rays));
	if (!rays)
		ft_error_buster(1);
	(*rays)->rays_num = mlx->win_x;
	(*rays)->ray_size = (mlx->player->r * RAY_SIZE);
	(*rays)->hit_x = 0;
	(*rays)->hit_y = 0;
	(*rays)->colision_distance = 0;
}

void	ft_player_init(t_player **player)
{
	*player = malloc (sizeof (t_player));
	if (!player)
		ft_error_buster(1);
	(*player)->fov = FOV * (M_PI / 180);
	(*player)->r = RADIUS * MINIMAP_SCALE;
	(*player)->spd = SPEED * MINIMAP_SCALE;
	(*player)->walk = 0;
	(*player)->turn = 0;
	(*player)->rot_spd = (ROT_SPEED * (M_PI / 180)) * MINIMAP_SCALE;
}

void	ft_textures_init(t_mlx *mlx)
{
	mlx->n_wall = file_to_image(mlx, mlx->north_texture);
	mlx->s_wall = file_to_image(mlx, mlx->south_texture);
	mlx->w_wall = file_to_image(mlx, mlx->west_texture);
	mlx->e_wall = file_to_image(mlx, mlx->east_texture);
}
