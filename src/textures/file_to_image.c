#include "../../includes/cub3D.h"

t_img	*file_to_image(t_mlx *mlx, char *path)
{
	t_img	*texture;

	texture = malloc (sizeof (t_img));
	if (!texture)
		ft_error_buster(1);
	texture->img = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &texture->width, &texture->len);
	if (!texture->img)
	{
		printf("Error\nTexture not found");
		exit(1);
	}
	texture->id = mlx_get_data_addr(texture->img, &texture->bpp, &texture->len, &texture->endian);
	if (!texture->id)
	{
		printf("Error\nTexture not found");
		exit(1);
	}
	//TODO: replacing the errors printf's with error_buster()
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

t_pos	*culcul_coordinate(t_mlx *mlx, t_pos *width_n_height)
{
	t_pos	*pos;

	pos = malloc(sizeof(t_pos));
	if (!pos)
		ft_error_buster(1);
	pos->x = (((int)mlx->rays->hit_x) * mlx->texture.width) / width_n_height->x;
	pos->y = (((int)mlx->rays->hit_y) * mlx->texture.len) / width_n_height->y;
	return (pos);
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
