/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:52:20 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/05 17:52:20 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float mult(float a, float b, float c)
{
	return (a * b * c);
}

t_vector3 multiplymatrixvector(t_vector3 i, t_matrix4x4 m)
{
	t_vector3 o;
	float w;
	o.x = i.x * m.matrix[0][0] + i.y * m.matrix[1][0] + i.z * m.matrix[2][0] + m.matrix[3][0];
	o.y = i.x * m.matrix[0][1] + i.y * m.matrix[1][1] + i.z * m.matrix[2][1] + m.matrix[3][1];
	o.z = i.x * m.matrix[0][2] + i.y * m.matrix[1][2] + i.z * m.matrix[2][2] + m.matrix[3][2];
	w = i.x * m.matrix[0][3] + i.y * m.matrix[1][3] + i.z * m.matrix[2][3] + m.matrix[3][3];
	if (w != 0.0f)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
	return (o);
}

t_vector4 multiplymatrixvector4(t_vector4 i, t_matrix4x4 m)
{
	t_vector4 o;
	o.x = i.x * m.matrix[0][0] + i.y * m.matrix[1][0] + i.z * m.matrix[2][0] + i.w * m.matrix[3][0];
	o.y = i.x * m.matrix[0][1] + i.y * m.matrix[1][1] + i.z * m.matrix[2][1] + i.w * m.matrix[3][1];
	o.z = i.x * m.matrix[0][2] + i.y * m.matrix[1][2] + i.z * m.matrix[2][2] + i.w * m.matrix[3][2];
	o.w = i.x * m.matrix[0][3] + i.y * m.matrix[1][3] + i.z * m.matrix[2][3] + i.w * m.matrix[3][3];
	return (o);
}


t_matrix4x4 mult_mat4x4(t_matrix4x4 mat1, t_matrix4x4 mat2)
{
	t_matrix4x4 result;
	int i;
	int j;
	int k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			result.matrix[i][j] = 0;
			k = -1;
			while (++k < 4)
				result.matrix[i][j] += mat1.matrix[i][k] * mat2.matrix[k][j];
		}
	}
	return (result);
}

float to_degree(float angle)
{
    return (angle * (180 / M_PI));
}
