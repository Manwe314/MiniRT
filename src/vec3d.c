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

t_vec2 vec2_sub(t_vec2 v1, t_vec2 v2)
{
    t_vec2 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    return result;
}

t_vec2 vec2_add(t_vec2 a, t_vec2 b)
{
    t_vec2 vec;

    vec.x = a.x + b.x;
    vec.y = a.y + b.y;
    return (vec);
}

t_vec2 vec2_mult(t_vec2 a, t_vec2 b)
{
    t_vec2 vec;

    vec.x = a.x * b.x;
    vec.y = a.y * b.y;
    return (vec);
}

t_vec2 vec2_multf(t_vec2 a, float b)
{
    t_vec2 vec;

    vec.x = a.x * b;
    vec.y = a.y * b;
    return (vec);
}

t_vec3 vec3_sub(t_vec3 v1, t_vec3 v2)
{
    t_vec3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
    t_vec3 vec;

    vec.x = a.x + b.x;
    vec.y = a.y + b.y;
    vec.z = a.z + b.z;
    return (vec);
}

t_vec3 vec3_mult(t_vec3 a, t_vec3 b)
{
    t_vec3 vec;

    vec.x = a.x * b.x;
    vec.y = a.y * b.y;
    vec.z = a.z * b.z;
    return (vec);
}

t_vec3 vec3_multf(t_vec3 a, float b)
{
    t_vec3 vec;

    vec.x = a.x * b;
    vec.y = a.y * b;
    vec.z = a.z * b;
    return (vec);
}

t_vec3 vec3_addf(t_vec3 a, float b)
{
    t_vec3 vec;

    vec.x = a.x + b;
    vec.y = a.y + b;
    vec.z = a.z + b;
    return (vec);
}

float vec3_magnitude(t_vec3 v)
{
    return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3 vec3_normalize(t_vec3 v)
{
    float mag = vec3_magnitude(v);
    t_vec3 result;
    result.x = v.x / mag;
    result.y = v.y / mag;
    result.z = v.z / mag;
    return result;
}

t_vec3 vec3_cross(t_vec3 v1, t_vec3 v2)
{
    t_vec3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

float dot_product(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec2 vec2(float x, float y)
{
	t_vec2 vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vec3 vec3(float x, float y, float z)
{
    t_vec3 vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    return (vec);
}

t_vec4 vec4(float x, float y, float z, float w)
{
    t_vec4 vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;
    return (vec);
}
