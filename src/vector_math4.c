/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:23:15 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/07 12:23:27 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	vector3_add_float(t_vector3 a, float b)
{
	t_vector3	vec;

	vec.x = a.x + b;
	vec.y = a.y + b;
	vec.z = a.z + b;
	return (vec);
}

float	vector3_length(t_vector3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector3	vector3_normalize(t_vector3 v)
{
	float		mag;
	t_vector3	result;

	mag = vector3_length(v);
	result.x = v.x / mag;
	result.y = v.y / mag;
	result.z = v.z / mag;
	return (result);
}

t_vector3	vector3_cross(t_vector3 v1, t_vector3 v2)
{
	t_vector3	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

t_vector3	vector3_reflect(t_vector3 a, t_vector3 n)
{
	return (vector3_subtract(a, \
	vector3_multiply_float(n, 2 * vector3_dot(a, n))));
}
