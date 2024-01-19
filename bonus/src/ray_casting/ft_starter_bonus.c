/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_starter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <rerayyad@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:53:15 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/16 17:48:12 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

t_mlx	*ft_data_init(char *av[])
{
	t_mlx	*mlx;

	ft_mlx_init(&mlx);
	ft_player_init(&mlx->player, mlx);
	ft_rays_init(&mlx->rays, mlx);
	ft_file_parser(mlx, av[1]);
	ft_map_parser(mlx);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		ft_error_buster(2, mlx);
	ft_textures_init(mlx);
	mlx->win_ptr = \
			mlx_new_window(mlx->mlx_ptr, mlx->win_x, mlx->win_y, "cub3D");
	if (!mlx->win_ptr)
		ft_error_buster(2, mlx);
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, mlx->win_x, mlx->win_y);
	mlx->img.id = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp,
			&mlx->img.len, &mlx->img.endian);
	ft_free(mlx->map);
	return (mlx);
}

void	ft_mlx_init(t_mlx **mlx)
{
	*mlx = malloc (sizeof (t_mlx));
	if (!(*mlx))
		ft_error_buster(1, *mlx);
	(*mlx)->win_x = 1337;
	(*mlx)->win_y = 800;
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
		ft_error_buster(1, mlx);
	(*rays)->rays_num = mlx->win_x;
	(*rays)->ray_size = (mlx->player->r * RAY_SIZE);
	(*rays)->hit_x = 0;
	(*rays)->hit_y = 0;
	(*rays)->colision_distance = 0;
}

void	ft_player_init(t_player **player, t_mlx *mlx)
{
	(void)mlx;
	*player = malloc (sizeof (t_player));
	if (!player)
		ft_error_buster(1, mlx);
	(*player)->fov = FOV * (M_PI / 180);
	(*player)->spd = SPEED * MINIMAP_SCALE;
	(*player)->walk = 0;
	(*player)->turn = 0;
	(*player)->rot_spd = (ROT_SPEED * (M_PI / 180)) * MINIMAP_SCALE;
}

void	ft_animated_textures_init(t_mlx *mlx)
{
	int	i;

	mlx->animated_texture = malloc(sizeof (char *) * 5);
	if (!mlx->animated_texture)
		ft_error_buster(1, mlx);
	mlx->animation = 0;
	i = 0;
	mlx->animated_texture[0] = "textres/animated00.xpm";
	mlx->animated_texture[1] = "textres/animated01.xpm";
	mlx->animated_texture[2] = "textres/animated00.xpm";
	mlx->animated_texture[3] = "textres/animated03.xpm";
	mlx->animated_texture[4] = NULL;
	while (i < 4)
	{
		mlx->a_wall[i] = ft_file_to_image(mlx, mlx->animated_texture[i]);
		if (!mlx->a_wall[i++])
			ft_error_buster(6, mlx);
	}
}
