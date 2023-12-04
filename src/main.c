#include "../includes/cub3D.h"
#include "../mlx_linux/mlx.h"

typedef struct s_mlx
{
	unsigned int	height;
	unsigned int	width;
	int				win_x;
	int				win_y;
	void			*mlx_ptr;
	void			*win_ptr;
}t_mlx;

int	ft_canvas_maker(t_mlx *mlx)
{
	mlx->win_x = 800;
	mlx->win_y = 800;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_x, mlx->win_y, "cub3D");
	if (!mlx->win_ptr)
		return (0);
	mlx_loop(mlx->mlx_ptr);
	return (1);
}

int	main(void)
{
	t_mlx	mlx;

	if (!ft_canvas_maker(&mlx))
		return (1);
	return (0);
}
