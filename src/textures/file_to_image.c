#include "../includes/cub3D.h"

void	*file_to_image(t_mlx *mlx, char *path)
{
	mlx->img2.img = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &mlx->img2.width, &mlx->img2.len);
	if (!mlx->img2.img)
	{
		printf("Error\nTexture not found");
		exit(1);
	}
	mlx->img2.id = mlx_get_data_addr(mlx->img2.img, &mlx->img2.bpp, &mlx->img2.len, &mlx->img2.endian);
	if( !mlx->img2.id)
	{
		printf("Error\nTexture not found");
		exit(1);
	}
	return (mlx->img2.img);
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
	pos->x = (((int)mlx->rays->hit_x) * mlx->img2.width) / width_n_height->x;
	pos->y = (((int)mlx->rays->hit_y) * mlx->img2.len) / width_n_height->y;

	return (pos);
}

unsigned int	my_mlx_pixel_get(t_mlx *mlx, int x, int y)
{
	char	*dst;

	if (mlx->win_x > x + 1 && mlx->win_y > y + 1 && x >= 0 && y >= 0)
	{
		dst = mlx->img2.id + (y * mlx->img2.len + x * (mlx->img2.bpp / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}
