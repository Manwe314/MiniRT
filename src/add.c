/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:01:27 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/06 15:01:27 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3 add_point(float x, float y, float z)
{
	t_vector3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_triangle add_triangle(t_vector3 pos, t_vector3 pos1, t_vector3 pos2)
{
	t_triangle triangle;

	triangle.p[0] = pos;
    triangle.p[1] = pos1;
    triangle.p[2] = pos2;
	return (triangle);
}


t_sphere add_sphere(t_vector3 pos, float radius, t_vector3 color)
{
	t_sphere sphere;

	sphere.center = pos;
	sphere.radius = radius;
	sphere.color = color;
	return (sphere);
}

