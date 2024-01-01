#include "../../includes/cub3D.h"

void	ft_move_front(t_mlx *mlx)
{
	float	x;
	float	y;

	x = mlx->player->x;
	y = mlx->player->y;
	mlx->player->x += cos(mlx->player->rot) * mlx->player->spd;
	if (ft_wall_colision(mlx))
		mlx->player->x = x;
	mlx->player->y += sin(mlx->player->rot) * mlx->player->spd;
	if (ft_wall_colision(mlx))
		mlx->player->y = y;
}

void	ft_move_back(t_mlx *mlx)
{
	float	x;
	float	y;

	x = mlx->player->x;
	y = mlx->player->y;
	mlx->player->x -= cos(mlx->player->rot) * mlx->player->spd;
	if (ft_wall_colision(mlx))
		mlx->player->x = x;
	mlx->player->y -= sin(mlx->player->rot) * mlx->player->spd;
	if (ft_wall_colision(mlx))
		mlx->player->y = y;
}

void	ft_move_left(t_mlx *mlx)
{
	float	x;
	float	y;

	x = mlx->player->x;
	y = mlx->player->y;
	mlx->player->x -= cos(mlx->player->rot + M_PI_2) * mlx->player->spd;
	if (ft_wall_colision(mlx))
		mlx->player->x = x;
	mlx->player->y -= sin(mlx->player->rot + M_PI_2) * mlx->player->spd;
	if (ft_wall_colision(mlx))
		mlx->player->y = y;
}

void	ft_move_right(t_mlx *mlx)
{
	float	x;
	float	y;

	x = mlx->player->x;
	y = mlx->player->y;
	mlx->player->x += cos(mlx->player->rot + M_PI_2) * mlx->player->spd;
	if (ft_wall_colision(mlx))
		mlx->player->x = x;
	mlx->player->y += sin(mlx->player->rot + M_PI_2) * mlx->player->spd;
	if (ft_wall_colision(mlx))
		mlx->player->y = y;
}
