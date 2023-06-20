/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:11:24 by marvin            #+#    #+#             */
/*   Updated: 2023/06/19 16:11:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_info triangle_collision(t_ray ray, t_triangle triangle)
{
	t_info hit_info;
	t_vector3 edge1;
	t_vector3 edge2;
	t_vector3 h;
	t_vector3 s;
	t_vector3 q;
	float a;
	float f;
	float u;
	float v;
	float t;

	hit_info.hit_distance = FLT_MAX;
	edge1 = vector3_subtract(triangle.p[1], triangle.p[0]);
	edge2 = vector3_subtract(triangle.p[2], triangle.p[0]);
	h = vector3_cross(ray.direction, edge2);
	a = vector3_dot(edge1, h);
	if (a > -0.00001f && a < 0.00001f)
		return (hit_info);
	f = 1.0f / a;
	s = vector3_subtract(ray.origin, triangle.p[0]);
	u = f * vector3_dot(s, h);
	if (u < 0.0f || u > 1.0f)
		return (hit_info);
	q = vector3_cross(s, edge1);
	v = f * vector3_dot(ray.direction, q);
	if (v < 0.0f || u + v > 1.0f)
		return (hit_info);
	t = f * vector3_dot(edge2, q);
	if (t < 0.0f)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = vector3_normalize(vector3_cross(edge1, edge2));
	hit_info.material = triangle.material;
	return (hit_info);
}

t_info paraboloid_collision(t_ray ray, t_paraboloid paraboloid)
{
	t_info hit_info;
	t_vector3 oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	hit_info.hit_distance = FLT_MAX;
	oc = vector3_subtract(ray.origin, paraboloid.center);
	a = vector3_dot(ray.direction, ray.direction) - vector3_dot(ray.direction, paraboloid.normal) * vector3_dot(ray.direction, paraboloid.normal);
	b = 2.0f * (vector3_dot(oc, ray.direction) - vector3_dot(oc, paraboloid.normal) * vector3_dot(ray.direction, paraboloid.normal));
	c = vector3_dot(oc, oc) - vector3_dot(oc, paraboloid.normal) * vector3_dot(oc, paraboloid.normal) - paraboloid.radius * paraboloid.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit_info);
	t = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (t < 0.0f)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = vector3_normalize(vector3_subtract(hit_info.hit_point, paraboloid.center));
	hit_info.material = paraboloid.material;
	return (hit_info);
}

t_info hyperboloid_collision(t_ray ray, t_hyperboloid hyperboloid)
{
	t_info hit_info;
	t_vector3 oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	hit_info.hit_distance = FLT_MAX;
	oc = vector3_subtract(ray.origin, hyperboloid.center);
	a = vector3_dot(ray.direction, ray.direction) - vector3_dot(ray.direction, hyperboloid.normal) * vector3_dot(ray.direction, hyperboloid.normal);
	b = 2.0f * (vector3_dot(oc, ray.direction) - vector3_dot(oc, hyperboloid.normal) * vector3_dot(ray.direction, hyperboloid.normal));
	c = vector3_dot(oc, oc) - vector3_dot(oc, hyperboloid.normal) * vector3_dot(oc, hyperboloid.normal) - hyperboloid.radius * hyperboloid.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit_info);
	t = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (t < 0.0f)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = vector3_normalize(vector3_subtract(hit_info.hit_point, hyperboloid.center));
	hit_info.material = hyperboloid.material;
	return (hit_info);
}

t_info cone_collision(t_ray ray, t_cone cone)
{
	t_info hit_info;
	t_vector3 oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	hit_info.hit_distance = FLT_MAX;
	oc = vector3_subtract(ray.origin, cone.center);
	a = vector3_dot(ray.direction, ray.direction) - (1 + cone.radius * cone.radius) * vector3_dot(ray.direction, cone.normal) * vector3_dot(ray.direction, cone.normal);
	b = 2.0f * (vector3_dot(oc, ray.direction) - (1 + cone.radius * cone.radius) * vector3_dot(oc, cone.normal) * vector3_dot(ray.direction, cone.normal));
	c = vector3_dot(oc, oc) - (1 + cone.radius * cone.radius) * vector3_dot(oc, cone.normal) * vector3_dot(oc, cone.normal);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit_info);
	t = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (t < 0.0f)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = vector3_normalize(vector3_subtract(hit_info.hit_point, cone.center));
	hit_info.material = cone.material;
	return (hit_info);
}