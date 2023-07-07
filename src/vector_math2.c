/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:21:41 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/07 12:21:52 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_vector3	vector3_mod(t_vector3 a, int b)
{
	t_vector3	result;

	result.x = (int)a.x % b;
	result.y = (int)a.y % b;
	result.z = (int)a.z % b;
	if (result.x < 0.0f)
		result.x = -result.x;
	if (result.y < 0.0f)
		result.y = -result.y;
	if (result.z < 0.0f)
		result.z = -result.z;
	return (result);
}

t_vector3	vector3_floor(t_vector3 a)
{
	t_vector3	result;

	result.x = floor(a.x);
	result.y = floor(a.y);
	result.z = floor(a.z);
	return (result);
}

t_vector3	lerp(t_vector3 a, t_vector3 b, float t)
{
	t_vector3	result;

	result.x = a.x + (b.x - a.x) * t;
	result.y = a.y + (b.y - a.y) * t;
	result.z = a.z + (b.z - a.z) * t;
	return (result);
}
