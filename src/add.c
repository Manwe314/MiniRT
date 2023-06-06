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

t_plane add_plane(t_vector3 pos, t_vector3 pos2, t_vector3 pos3, t_vector3 pos4)
{
	t_plane plane;

	plane.plane[0] = pos;
	plane.plane[1] = pos2;
	plane.plane[2] = pos3;
	plane.plane[3] = pos4;
	return (plane);
}
