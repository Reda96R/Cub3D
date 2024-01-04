/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_janitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:57:02 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/04 09:57:09 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_error_buster(int id)
{
	if (id == 1)
		ft_putstr_fd("\033[0;31mError: unable to allocate memory\n", 2);
	else if (id == 2)
		ft_putstr_fd("\033[0;31m\n", 2);
	printf("\033[0m");
}
