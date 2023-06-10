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

t_sphere add_sphere(t_vector3 pos, float radius, t_vector3 color, int index)
{
	t_sphere sphere;

	sphere.center = pos;
	sphere.radius = radius;
	sphere.color = color;
	sphere.material_index = index;
	return (sphere);
}

t_material add_material(t_vector3 color, float roughness, float mettalic,t_vector3 emission_color, float emission_intensity)
{
	t_material material;

	material.color = color;
	material.roughness = roughness;
	material.mettalic = mettalic;
	material.emission_color = emission_color;
	material.emission_intensity = emission_intensity;
	material.emission = vector3_multiply_float(emission_color, emission_intensity);
	return (material);
}
