/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:38:19 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/13 14:38:25 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_img	*file_to_image(t_mlx *mlx, char *path)
{
	t_img	*texture;

	texture = malloc (sizeof (t_img));
	if (!texture)
		ft_error_buster(1);
	texture->img = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
			&texture->width, &texture->len);
	if (!texture->img)
		ft_error_buster(6);
	texture->id = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->len, &texture->endian);
	if (!texture->id)
		ft_error_buster(6);
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

int	my_mlx_pixel_get(t_mlx *mlx, int x, int y)
{
	char	*dst;

	if (mlx->win_x > x && mlx->win_y > y && x >= 0 && y >= 0)
	{
		dst = mlx->texture.id
			+ (y * mlx->texture.len + x * (mlx->texture.bpp / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}
