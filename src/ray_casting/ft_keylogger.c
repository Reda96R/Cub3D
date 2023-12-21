#include "../../includes/cub3D.h"

int	ft_key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
		mlx->player->m_f = 1;
	else if (keycode == KEY_S)
		mlx->player->m_b = 1;
	else if (keycode == KEY_A)
		mlx->player->m_l = 1;
	else if (keycode == KEY_D)
		mlx->player->m_r = 1;
	else if (keycode == KEY_L_A)
		mlx->player->t_l = 1;
	else if (keycode == KEY_R_A)
		mlx->player->t_r = 1;
	else if (keycode == ESCAPE_KEY)
		exit (0);
	return (0);
}

int	ft_key_release(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
		mlx->player->m_f = 0;
	else if (keycode == KEY_S)
		mlx->player->m_b = 0;
	else if (keycode == KEY_A)
		mlx->player->m_l = 0;
	else if (keycode == KEY_D)
		mlx->player->m_r = 0;
	else if (keycode == KEY_L_A)
		mlx->player->t_l = 0;
	else if (keycode == KEY_R_A)
		mlx->player->t_r = 0;
	return (0);
}
