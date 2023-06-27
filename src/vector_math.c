/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:18:55 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:18:55 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_vector2	vector2_subtract(t_vector2 v1, t_vector2 v2)
{
	t_vector2	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	return (result);
}

t_vector2	vector2_add(t_vector2 a, t_vector2 b)
{
	t_vector2	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	return (vec);
}

t_vector2	vector2_multiply(t_vector2 a, t_vector2 b)
{
	t_vector2	vec;

	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	return (vec);
}

t_vector2	vector2_multiply_float(t_vector2 a, float b)
{
	t_vector2	vec;

	vec.x = a.x * b;
	vec.y = a.y * b;
	return (vec);
}

t_vector3	vector3_subtract(t_vector3 v1, t_vector3 v2)
{
	t_vector3	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vector3	vector3_add(t_vector3 a, t_vector3 b)
{
	t_vector3	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}

t_vector3	vector3_multiply(t_vector3 a, t_vector3 b)
{
	t_vector3	vec;

	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	vec.z = a.z * b.z;
	return (vec);
}

t_vector3	vector3_multiply_float(t_vector3 a, float b)
{
	t_vector3	vec;

	vec.x = a.x * b;
	vec.y = a.y * b;
	vec.z = a.z * b;
	return (vec);
}

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

float	vector3_dot(t_vector3 vec1, t_vector3 vector2)
{
	return (vec1.x * vector2.x + vec1.y * vector2.y + vec1.z * vector2.z);
}

t_vector4	vector4_add(t_vector4 a, t_vector4 b)
{
	t_vector4	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	vec.w = a.w + b.w;
	return (vec);
}

t_vector4	vector4_multiply_float(t_vector4 a, float b)
{
	t_vector4	vec;

	vec.x = a.x * b;
	vec.y = a.y * b;
	vec.z = a.z * b;
	vec.w = a.w * b;
	return (vec);
}

t_vector3	vector3_clamp(t_vector3 color, float min, float max)
{
	if (color.x < min)
		color.x = min;
	else if (color.x > max)
		color.x = max;
	if (color.y < min)
		color.y = min;
	else if (color.y > max)
		color.y = max;
	if (color.z < min)
		color.z = min;
	else if (color.z > max)
		color.z = max;
	return (color);
}

t_vector2	vector2(float x, float y)
{
	t_vector2	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vector3	vector3(float x, float y, float z)
{
	t_vector3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vector4	vector4(float x, float y, float z, float w)
{
	t_vector4	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = w;
	return (vec);
}
