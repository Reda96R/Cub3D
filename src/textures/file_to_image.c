#include "../includes/cub3D.h"

void	*file_to_image(t_mlx *mlx, char *path)
{
	mlx->img.img = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &mlx->img.width, &mlx->img.len);
	if (!mlx->img.img)
	{
		printf("Error\nTexture not found");
		exit(1);
	}
	return (mlx->img.img);
}

void	check_image_driction(t_mlx *mlx)
{
	if (mlx->rays->heading == 'N')
		mlx->img.img = file_to_image(mlx, mlx->north_texture);
	else if (mlx->rays->heading == 'S')
		mlx->img.img = file_to_image(mlx, mlx->south_texture);
	else if (mlx->rays->heading == 'E')
		mlx->img.img = file_to_image(mlx, mlx->east_texture);
	else if (mlx->rays->heading == 'W')
		mlx->img.img = file_to_image(mlx, mlx->west_texture);
}
	

t_pos	*culcul_coordinate(t_mlx *mlx, t_pos *width_n_height)
{
	t_pos *pos;

	pos = malloc(sizeof(t_pos));
	if (!pos)
		ft_error_buster(1);
	pos->x = (((int)mlx->rays->hit_x) * mlx->img.width) / width_n_height->x;
	pos->y = (((int)mlx->rays->hit_y) * mlx->img.len) / width_n_height->y;

	return (pos);
}

unsigned int	my_mlx_pixel_get(t_mlx *mlx, int x, int y)
{
	char	*dst;

	if (mlx->win_x > x && mlx->win_y > y && x >= 0 && y >= 0)
	{
		dst = mlx->img.id + (x * mlx->img.len + y * (mlx->img.bpp / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}
