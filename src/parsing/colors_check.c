/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 03:07:45 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/14 20:17:45 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	colors_existence(t_mlx *mlx)
{
	if (!mlx->c_color || !mlx->f_color)
		ft_error_buster(7, mlx);
}

void	check_colors_format(char *str, t_mlx *mlx, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != ',' && str[i] != '0'
			&& str[i] != '1' && str[i] != '2' && str[i] != '3'
			&& str[i] != '4' && str[i] != '5' && str[i] != '6'
			&& str[i] != '7' && str[i] != '8' && str[i] != '9')
			ft_error_buster(8, mlx);
		if (str[i] == ',')
		{
			j++;
			if (str[i + 1] == ',')
				ft_error_buster(8, mlx);
		}
		i++;
	}
	if (j != 2)
		ft_error_buster(8, mlx);
	check_colors_range(str, mlx, c);
}

void	ft_color_assigner(t_mlx *mlx, char c, int a, int i)
{
	if (c == 'c')
	{
		if (i == 0)
			mlx->c_color_int += a * 256 * 256;
		if (i == 1)
			mlx->c_color_int += a * 256;
		if (i == 2)
			mlx->c_color_int += a;
	}
	else if (c == 'f')
	{
		if (i == 0)
			mlx->f_color_int += a * 256 * 256;
		if (i == 1)
			mlx->f_color_int += a * 256;
		if (i == 2)
			mlx->f_color_int += a;
	}
}

void	colors_range(t_mlx *mlx, char *tmp, int i, char c)
{
	int		a;
	size_t	k;
	int		j;
	char	*str;

	j = 0;
	k = 0;
	while (tmp[j] == '0' || tmp[j] == ' ')
		j++;
	while (tmp[j])
	{
		if (tmp[j] != ' ')
			k++;
		j++;
	}
	a = ft_atoi(tmp);
	str = ft_itoa(a);
	if (k != ft_strlen(str) && a != 0)
		ft_error_buster(8, mlx);
	if (a < 0 || a > 255)
		ft_error_buster(9, mlx);
	free(str);
	ft_color_assigner(mlx, c, a, i);
	free(tmp);
}

void	check_colors_range(char	*str, t_mlx *mlx, char c)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (str[i] != ',')
		i++;
	tmp = ft_substr(str, 0, i);
	colors_range(mlx, tmp, 0, c);
	i++;
	j = i;
	while (str[i] != ',')
		i++;
	tmp = ft_substr(str, j, i - j);
	colors_range(mlx, tmp, 1, c);
	i++;
	j = i;
	while (str[i] != '\0')
		i++;
	tmp = ft_substr(str, j, i - j);
	colors_range(mlx, tmp, 2, c);
}
