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
