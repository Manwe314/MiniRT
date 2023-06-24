/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:09:20 by marvin            #+#    #+#             */
/*   Updated: 2023/06/19 16:09:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_info	sphere_collision(t_ray ray, const t_sphere *sphere)
{
	t_info hit_info;
	t_vector3 oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	hit_info.hit_distance = FLT_MAX;
	oc = vector3_subtract(ray.origin, sphere->center);
	a = vector3_dot(ray.direction, ray.direction);
	b = 2.0f * vector3_dot(oc, ray.direction);
	c = vector3_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit_info);
	t = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (t < 0.0f)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = vector3_normalize(vector3_subtract(hit_info.hit_point, sphere->center));
	hit_info.material = sphere->material;
	return (hit_info);
}

t_info	plane_collision(t_ray ray, const  t_plane *plane)
{
	t_info hit_info;
	float t;

	hit_info.hit_distance = FLT_MAX;
	t = vector3_dot(vector3_subtract(plane->point_on_plane, ray.origin), plane->normal) / vector3_dot(ray.direction, plane->normal);
	if (t < 0.0f)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = plane->normal;
	hit_info.material = plane->material;
	return (hit_info);
}

t_info circle_collision(t_ray ray, const t_circle *cirle)
{
	t_info hit_info;
	float t;

	hit_info.hit_distance = FLT_MAX;
	t = vector3_dot(vector3_subtract(cirle->center, ray.origin), cirle->normal) / vector3_dot(ray.direction, cirle->normal);
	if (t < 0.0f)
		return (hit_info);
	float distance_to_center = vector3_length(vector3_subtract(cirle->center, vector3_add(ray.origin, vector3_multiply_float(ray.direction, t))));
	if (distance_to_center > cirle->radius)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = cirle->normal;
	hit_info.material = cirle->material;
	return (hit_info);
}

bool 	check_cylinder_height(const t_cylinder *cylinder, t_vector3 hit_point)
{
	t_vector3 cylinder_top;
	t_vector3 cylinder_bottom;
	t_vector3 cylinder_height;
	float height;

	cylinder_top = vector3_add(cylinder->center, vector3_multiply_float(cylinder->normal, cylinder->height));
	cylinder_bottom = vector3_subtract(cylinder->center, vector3_multiply_float(cylinder->normal, cylinder->height));
	cylinder_height = vector3_subtract(cylinder_top, cylinder_bottom);
	height = vector3_dot(vector3_subtract(hit_point, cylinder_bottom), cylinder_height);
	if (height < 0.0f || height > vector3_dot(cylinder_height, cylinder_height))
		return (false);
	return (true);
}

t_info	cylinder_collision(t_ray ray, const t_cylinder *cylinder)
{
	t_info hit_info;
	t_vector3 oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	hit_info.hit_distance = FLT_MAX;
	oc = vector3_subtract(ray.origin, cylinder->center);
	a = vector3_dot(ray.direction, ray.direction) - pow(vector3_dot(ray.direction, cylinder->normal), 2);
	b = 2.0f * (vector3_dot(oc, ray.direction) - vector3_dot(ray.direction, cylinder->normal) * vector3_dot(oc, cylinder->normal));
	c = vector3_dot(oc, oc) - pow(vector3_dot(oc, cylinder->normal), 2) - cylinder->radius * cylinder->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (hit_info);
		hit_info = circle_collision(ray, &cylinder->circle_top);
		if (hit_info.hit_distance != FLT_MAX)
			return (hit_info);
		hit_info = circle_collision(ray, &cylinder->circle_bottom);
		if (hit_info.hit_distance != FLT_MAX)
		return (hit_info);
	}
	t = (-b - sqrt(discriminant)) / (2.0f * a);
	if (t < 0.0f)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	if (check_cylinder_height(cylinder, hit_info.hit_point) == false)
	{
		hit_info.hit_distance = FLT_MAX;
		return (hit_info);
	}
	hit_info.normal = vector3_normalize(vector3_subtract(hit_info.hit_point, cylinder->center));
	hit_info.material = cylinder->material;
	return (hit_info);
}


