/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:23:10 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/07 12:25:00 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
