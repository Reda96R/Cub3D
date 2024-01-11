#include "../includes/cub3D.h"

void	*file_to_image(t_mlx *mlx, char *path)
{
	mlx->img.img = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &mlx->img.width, &mlx->img.len);
	if (!mlx->img.img)
		return (NULL);
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
	

t_pos	*culcul_coordinate(t_mlx *mlx)
{
	t_pos *pos;
	printf("hit_x = %f\n", mlx->rays->hit_x);
	printf("hit_y = %f\n", mlx->rays->hit_y);
	check_image_driction(mlx);
	if(!mlx->img.img)
	{
		printf("Error\nTexture not found");
		exit(1);
	}
	printf("cube size = %f\n", mlx->cub_size);
	pos = malloc(sizeof(t_pos));
	pos->x = (((int)mlx->rays->hit_x % (int)mlx->cub_size) * mlx->img.width) / mlx->cub_size;
	pos->y = (((int)mlx->rays->hit_y % (int)mlx->cub_size) * mlx->img.len) / mlx->cub_size;
	printf("------------------\n");
	printf("hit_x = %f\n", mlx->rays->hit_x);
	printf("hit_y = %f\n", mlx->rays->hit_y);
	return (pos);
}

unsigned int	my_mlx_pixel_get(t_mlx *mlx, int x, int y)
{
	char	*dst;

	dst = mlx->img.id + (y * mlx->img.len + x * (mlx->img.bpp / 8));
	return (*(unsigned int *)dst);
}
