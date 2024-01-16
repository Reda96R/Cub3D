/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:38:19 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/16 07:23:09 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_img	*ft_file_to_image(t_mlx *mlx, char *path)
{
	t_img	*texture;

	texture = malloc (sizeof (t_img));
	if (!texture)
		ft_error_buster(1, mlx);
	texture->img = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
			&texture->width, &texture->len);
	if (!texture->img)
		ft_error_buster(6, mlx);
	texture->id = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->len, &texture->endian);
	if (!texture->id)
		ft_error_buster(6, mlx);
	return (texture);
}

t_img	ft_texture_selector(t_mlx *mlx)
{
	if (mlx->rays->heading == 'N')
		return (*mlx->n_wall);
	else if (mlx->rays->heading == 'S')
		return (*mlx->s_wall);
	else if (mlx->rays->heading == 'E')
		return (*mlx->e_wall);
	else
		return (*mlx->w_wall);
}

void	ft_render_skyfloor(t_mlx *mlx, int i, t_pos width_n_height, int n)
{
	t_pos	coordinates;
	int		color;
	char	c;

	c = mlx->rays->heading;
	if (!n)
	{
		coordinates.x = i;
		coordinates.y = 0;
		width_n_height.y = (mlx->win_y / 2) - (width_n_height.y / 2);
		color = mlx->c_color_int;
		mlx->rays->heading = 'C';
	}
	else
	{
		coordinates.x = i;
		coordinates.y = (mlx->win_y / 2) - (width_n_height.y / 2)
			+ width_n_height.y;
		width_n_height.y = (mlx->win_y - (coordinates.y));
		color = mlx->f_color_int;
		mlx->rays->heading = 'F';
	}
	mlx->rays->heading = c;
	ft_draw_rectangle(mlx, &coordinates, width_n_height, color);
}

void	ft_draw_textured_wall(t_mlx *mlx, t_pos *coordinates,
		t_pos width_n_height)
{
	int		x;
	int		y;
	float	scale;
	t_pos	*pos;

	pos = malloc(sizeof(t_pos));
	if (!pos)
		ft_error_buster(1, mlx);
	x = coordinates->x;
	if (mlx->rays->s == 'h')
		pos->x = ((mlx->rays->hit_x / mlx->cub_size)
				- (int)(mlx->rays->hit_x / mlx->cub_size)) * mlx->texture.width;
	else
		pos->x = ((mlx->rays->hit_y / mlx->cub_size)
				- (int)(mlx->rays->hit_y / mlx->cub_size)) * mlx->texture.width;
	scale = (mlx->texture.width / width_n_height.y);
	pos->y = 0;
	if (mlx->win_y < width_n_height.y)
	{
		coordinates->y = 0;
		pos->y = ((width_n_height.y - mlx->win_y) / 2) * scale;
	}
	y = coordinates->y;
	while (y < coordinates->y + width_n_height.y && y < mlx->win_y)
	{
		pos->y += scale;
		ft_put_pixel(mlx, x, y++, ft_my_mlx_pixel_get(mlx, pos->x, pos->y));
	}
	free (pos);
}

void	ft_draw_textured_wall_animated(t_mlx *mlx, t_pos *coordinates,
		t_pos width_n_height)
{
	int		x;
	int		y;
	float	scale[mlx->texter_n];
	t_pos	*pos[mlx->texter_n];

	pos[mlx->i/ANIMATION] = malloc (sizeof (t_pos));
	if (!pos[mlx->i/ANIMATION])
		ft_error_buster(1, mlx);
	x = coordinates->x;
	pos_x_init(mlx, pos);
	scale[mlx->i/ANIMATION] = (mlx->animation[mlx->i/ANIMATION].width / width_n_height.y);
	pos[mlx->i/ANIMATION]->y = 0;
	if (mlx->win_y < width_n_height.y)
	{
		coordinates->y = 0;
		pos[mlx->i/ANIMATION]->y = ((width_n_height.y - mlx->win_y) / 2) * scale[mlx->i/ANIMATION];
	}
	y = coordinates->y;
	while (y < coordinates->y + width_n_height.y && y < mlx->win_y)
	{
		pos[mlx->i/ANIMATION]->y += scale[mlx->i/ANIMATION];
		ft_put_pixel(mlx, x, y++, ft_my_mlx_pixel_get_animated(mlx, pos[mlx->i/ANIMATION]->x, pos[mlx->i/ANIMATION]->y, mlx->i/ANIMATION));
	}
	if (pos[mlx->i/ANIMATION])
		free(pos[mlx->i/ANIMATION]);
	mlx->i++;
	if (mlx->i % (mlx->texter_n * ANIMATION) == 0)
		mlx->i = 0;
}

void	pos_x_init(t_mlx *mlx, t_pos *pos[mlx->texter_n])
{

	if (mlx->rays->s == 'h')
		pos[mlx->i/ANIMATION]->x = ((mlx->rays->hit_x / mlx->cub_size)
				- (int)(mlx->rays->hit_x / mlx->cub_size)) * mlx->animation[mlx->i/ANIMATION].width;
	else
		pos[mlx->i/ANIMATION]->x = ((mlx->rays->hit_y / mlx->cub_size)
				- (int)(mlx->rays->hit_y / mlx->cub_size)) * mlx->animation[mlx->i/ANIMATION].width;
}

void	img_animations(t_mlx *mlx) // will be deleted in mandatory part
{
	int		i;

	i = 0;
	mlx->texter_n = animation_selector(mlx, TYPE);
	while (mlx->animation[i].img && i < mlx->texter_n)
	{
		mlx->animation[i].img = mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->animation[i].path, &mlx->animation[i].width, &mlx->animation[i].len);
		if (!mlx->animation[i].img)
			ft_error_buster(6, mlx);
		mlx->animation[i].id = mlx_get_data_addr(mlx->animation[i].img, &mlx->animation[i].bpp, &mlx->animation[i].len, &mlx->animation[i].endian);
		if (!mlx->animation[i].id)
			ft_error_buster(6, mlx);
		i++;
	}
}

int	animation_selector(t_mlx *mlx, int type)
{
	if (type == 1)
	{
		mlx->animation[0].path = "textres/01.xpm";
		mlx->animation[1].path = "textres/02.xpm";
		mlx->animation[2].path = "textres/03.xpm";
		mlx->animation[3].path = "textres/04.xpm";
		mlx->animation[4].path = "textres/05.xpm";
		mlx->animation[5].path = "textres/06.xpm";
		mlx->animation[6].path = "textres/07.xpm";
		mlx->animation[7].path = "textres/08.xpm";
		mlx->animation[8].path = "textres/09.xpm";
		mlx->animation[9].path = "textres/10.xpm";
		mlx->animation[10].path = "textres/11.xpm";
		return (11);
	}
	else if (type == 2)
	{
		mlx->animation[0].path = "textres/AnyConv.com__SLADDMON (64).xpm";
		mlx->animation[1].path = "textres/AnyConv.com__SLADDMON1 (64).xpm";
		mlx->animation[2].path = "textres/AnyConv.com__SLADDMON2 (64).xpm";
		mlx->animation[3].path = "textres/AnyConv.com__SLADDMON3 (64).xpm";
		return (4);
	}
	else
		return (0);	
}
