/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:21:05 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:21:05 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4x4	init_mat_0(void)
{
	t_matrix4x4	mat;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			mat.matrix[i][j] = 0.0f;
	}
	return (mat);
}

t_matrix4x4	rotation_x(float angle)
{
	t_matrix4x4		matrix;
	float			c;
	float			s;

	c = cos(angle);
	s = sin(angle);
	matrix = init_mat_0();
	matrix.matrix[0][0] = 1.0f;
	matrix.matrix[1][1] = c;
	matrix.matrix[1][2] = -s;
	matrix.matrix[2][1] = s;
	matrix.matrix[2][2] = c;
	matrix.matrix[3][3] = 1.0f;
	return (matrix);
}

t_matrix4x4	rotation_y(float angle)
{
	t_matrix4x4	matrix;
	float		c;
	float		s;

	c = cos(angle);
	s = sin(angle);
	matrix = init_mat_0();
	matrix.matrix[0][0] = c;
	matrix.matrix[0][2] = s;
	matrix.matrix[1][1] = 1.0f;
	matrix.matrix[2][0] = -s;
	matrix.matrix[2][2] = c;
	matrix.matrix[3][3] = 1.0f;
	return (matrix);
}

t_matrix4x4	rotation_z(float angle)
{
	t_matrix4x4	matrix;
	float		c;
	float		s;

	c = cos(angle);
	s = sin(angle);
	matrix = init_mat_0();
	matrix.matrix[0][0] = c;
	matrix.matrix[0][1] = -s;
	matrix.matrix[1][0] = s;
	matrix.matrix[1][1] = c;
	matrix.matrix[2][2] = 1.0f;
	matrix.matrix[3][3] = 1.0f;
	return (matrix);
}

t_matrix4x4	translation(t_vector3 vec)
{
	t_matrix4x4	matrix;

	matrix = init_mat_0();
	matrix.matrix[0][0] = 1.0f;
	matrix.matrix[1][1] = 1.0f;
	matrix.matrix[2][2] = 1.0f;
	matrix.matrix[3][3] = 1.0f;
	matrix.matrix[3][0] = vec.x;
	matrix.matrix[3][1] = vec.y;
	matrix.matrix[3][2] = vec.z;
	return (matrix);
}
