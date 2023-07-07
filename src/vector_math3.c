/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:22:24 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/07 12:22:35 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
