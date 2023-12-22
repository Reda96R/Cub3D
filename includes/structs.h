/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:54:40 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/21 17:54:40 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_player
{
	int		m_f;
	int		m_b;
	int		m_r;
	int		m_l;
	int		t_r;
	int		t_l;
	float	fov;
	float	x;
	float	y;
	float	r;
	float	turn;
	float	walk;
	float	spd;
	float	rot;
	float	rot_spd;
}	t_player;

typedef struct s_rays {
	float	rays_num;
	float	ray_size;
}	t_rays;	

typedef struct s_img
{
	void	*img;
	char	*id;
	int		endian;
	int		bpp;
	int		len;
}	t_img;

typedef struct s_pos {
	float	x;
	float	y;
	float	rot;
}	t_pos;

#endif
