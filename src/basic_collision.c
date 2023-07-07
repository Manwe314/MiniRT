/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:48:08 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 18:48:08 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_info	miss(void)
{
	t_info	hit_info;

	hit_info.hit_distance = FLT_MAX;
	return (hit_info);
}

t_info	return_hit_info(t_ray ray, float t, t_material material,
	t_vector3 normal)
{
	t_info	hit_info;

	hit_info.hit_distance = t;
	if (t < 0.0f)
		return (miss());
	hit_info.hit_point = vector3_add(ray.origin, \
			vector3_multiply_float(ray.direction, t));
	hit_info.normal = normal;
	hit_info.material = material;
	return (hit_info);
}

t_info	sphere_collision(t_ray ray, const t_sphere *sphere)
{
	t_info		hit_info;
	t_vector3	oc;
	float		abc[3];
	float		discriminant;
	float		t;

	oc = vector3_subtract(ray.origin, sphere->center);
	abc[0] = vector3_dot(ray.direction, ray.direction);
	abc[1] = 2.0f * vector3_dot(oc, ray.direction);
	abc[2] = vector3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (miss());
	t = (-abc[1] - sqrtf(discriminant)) / (2.0f * abc[0]);
	if (t < 0.0f)
		return (miss());
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, \
		vector3_multiply_float(ray.direction, t));
	hit_info.normal = vector3_normalize(vector3_subtract(hit_info.hit_point, \
			sphere->center));
	hit_info.material = sphere->material;
	return (hit_info);
}

t_info	plane_collision(t_ray ray, const t_plane *plane)
{
	t_info	hit_info;
	float	t;

	t = vector3_dot(vector3_subtract(plane->point_on_plane, ray.origin), \
		plane->normal) / vector3_dot(ray.direction, plane->normal);
	if (t < 0.0f)
		return (miss());
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, \
		vector3_multiply_float(ray.direction, t));
	hit_info.normal = plane->normal;
	hit_info.material = plane->material;
	return (hit_info);
}
