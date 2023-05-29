/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:16:35 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/26 16:16:35 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3d vec3d_sub(t_vec3d v1, t_vec3d v2)
{
    t_vec3d result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

float vec3d_magnitude(t_vec3d v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3d vec3d_normalize(t_vec3d v)
{
    float mag = vec3d_magnitude(v);
    t_vec3d result;
    result.x = v.x / mag;
    result.y = v.y / mag;
    result.z = v.z / mag;
    return result;
}

t_vec3d vec3d_cross(t_vec3d v1, t_vec3d v2)
{
    t_vec3d result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

t_vec3d dot_product(t_vec3d vec1, t_vec3d vec2)
{
	t_vec3d vec;

	vec.x = vec1.x * vec2.x;
	vec.y = vec1.y * vec2.y;
	vec.z = vec1.z * vec2.z;
	return (vec);
}
