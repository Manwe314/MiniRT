/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:42:32 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 18:42:32 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_info	cone_collision(t_ray ray, const t_cone *cone)
{
	t_info		hit_info;
	t_vector3	oc;
	float		abc[3];
	float		discriminant;
	float		t;

	hit_info.hit_distance = FLT_MAX;
	oc = vector3_subtract(ray.origin, cone->center);
	// t_matrix4x4 rotation_matrix = rotation(cone->normal);
	// oc = multiplymatrixvector(oc, rotation_matrix);
	// ray.direction = multiplymatrixvector(ray.direction, rotation_matrix);
	abc[0] = ray.direction.x * ray.direction.x - (cone->radius / cone->height)
		* (cone->radius / cone->height) * ray.direction.y * ray.direction.y
		+ ray.direction.z * ray.direction.z;
	abc[1] = 2.0f * (ray.direction.x * oc.x - (cone->radius / cone->height)
			* (cone->radius / cone->height) * ray.direction.y * oc.y
			+ ray.direction.z * oc.z);
	abc[2] = oc.x * oc.x - (cone->radius / cone->height)
		* (cone->radius / cone->height) * oc.y * oc.y + oc.z * oc.z;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (miss());
	t = (-abc[1] - sqrtf(discriminant)) / (2.0f * abc[0]);
	if (t < 0.0f)
		return (miss());
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, \
		vector3_multiply_float(ray.direction, t));
	abc[1] = (hit_info.hit_point.y - cone->center.y) / cone->height;
	if (abc[1] < 0.0f || abc[1] > 1.0f)
		return (miss());
	hit_info.normal = vector3((hit_info.hit_point.x - cone->center.x)
			/ cone->radius, cone->height * (cone->radius / cone->height),
			(hit_info.hit_point.z - cone->center.z) / cone->radius);
	hit_info.material = cone->material;
	return (hit_info);
}

// t_info	triangle_collision(t_ray ray, const t_triangle *triangle)
// {
// 	t_info		hit_info;
// 	t_vector3	edge1;
// 	t_vector3	edge2;
// 	t_vector3	h;
// 	t_vector3	s;
// 	t_vector3	q;
// 	float		a;
// 	float		f;
// 	float		u;
// 	float		v;
// 	float		t;

// 	hit_info.hit_distance = FLT_MAX;
// 	edge1 = vector3_subtract(triangle->p[1], triangle->p[0]);
// 	edge2 = vector3_subtract(triangle->p[2], triangle->p[0]);
// 	h = vector3_cross(ray.direction, edge2);
// 	a = vector3_dot(edge1, h);
// 	if (a > -0.00001f && a < 0.00001f)
// 		return (hit_info);
// 	f = 1.0f / a;
// 	s = vector3_subtract(ray.origin, triangle->p[0]);
// 	u = f * vector3_dot(s, h);
// 	if (u < 0.0f || u > 1.0f)
// 		return (hit_info);
// 	q = vector3_cross(s, edge1);
// 	v = f * vector3_dot(ray.direction, q);
// 	if (v < 0.0f || u + v > 1.0f)
// 		return (hit_info);
// 	t = f * vector3_dot(edge2, q);
// 	if (t < 0.0f)
// 		return (hit_info);
// 	hit_info.hit_distance = t;
// 	hit_info.hit_point = vector3_add(ray.origin, 
// 		vector3_multiply_float(ray.direction, t));
// 	hit_info.normal = vector3_normalize(vector3_cross(edge1, edge2));
// 	hit_info.material = triangle->material;
// 	return (hit_info);
// }

// t_info	cone_collision(t_ray ray, const t_cone *cone)
// {
// 	t_info		hit_info;
// 	t_vector3	oc;
// 	float		abc[3];
// 	float		discriminant;
// 	float		t;

// 	hit_info.hit_distance = FLT_MAX;
// 	oc = vector3_subtract(ray.origin, cone->center);
// 	abc[0] = vector3_dot(ray.direction, ray.direction) - (1 + cone->radius 
// 		* cone->radius) * vector3_dot(ray.direction, cone->normal)
// 		* vector3_dot(ray.direction, cone->normal);
// 	abc[1] = 2.0f * (vector3_dot(oc, ray.direction) - (1 + cone->radius 
// 			* cone->radius) * vector3_dot(oc, cone->normal) 
// 		* vector3_dot(ray.direction, cone->normal));
// 	abc[2] = vector3_dot(oc, oc) - (1 + cone->radius * cone->radius)
// 		* vector3_dot(oc, cone->normal) * vector3_dot(oc, cone->normal);
// 	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
// 	if (discriminant < 0)
// 		return (hit_info);
// 	t = (-abc[1] - sqrtf(discriminant)) / (2.0f * abc[0]);
// 	if (t < 0.0f)
// 		return (hit_info);
// 	hit_info.hit_distance = t;
// 	hit_info.hit_point = vector3_add(ray.origin, 
// 		vector3_multiply_float(ray.direction, t));
// 	if (vector3_dot(vector3_subtract(hit_info.hit_point, cone->center),
		//cone->normal) < 0 
// 	|| vector3_dot(vector3_subtract(hit_info.hit_point, cone->center),
//		cone->normal) > cone->height * vector3_length(cone->normal))
// 	{
// 		hit_info.hit_distance = FLT_MAX;
// 		return (hit_info);
// 	}
// 	hit_info.normal = vector3_normalize(vector3_subtract(hit_info.hit_point, 
// 			cone->center));
// 	hit_info.material = cone->material;
// 	return (hit_info);
// }

// t_info cone_collision(t_ray ray, const t_cone* cone)
// {
// 	t_info hit_info;
// 	t_vector3 oc;
// 	float abc[3];
// 	float discriminant;
// 	float t;

// 	hit_info.hit_distance = FLT_MAX;
// 	oc = vector3_subtract(ray.origin, cone->center);
	//abc[0] = ray.direction.x * ray.direction.x
		//- (cone->radius / cone->height) * (cone->radius / cone->height)
		//* ray.direction.y * ray.direction.y
		//+ ray.direction.z * ray.direction.z;
// 	abc[1] = 2.0f * (ray.direction.x * oc.x - (cone->radius / cone->height)
		//* (cone->radius / cone->height) * ray.direction.y * oc.y
		//+ ray.direction.z * oc.z);
// 	abc[2] = oc.x * oc.x - (cone->radius / cone->height)
		// (cone->radius / cone->height) * oc.y * oc.y + oc.z * oc.z;
// 	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
// 	if (discriminant < 0)
// 		return (miss());
// 	t = (-abc[1] - sqrtf(discriminant)) / (2.0f * abc[0]);
// 	if (t < 0.0f)
// 		return (miss());
// 	hit_info.hit_distance = t;
// 	hit_info.hit_point =  vector3_add(ray.origin, 
// 		vector3_multiply_float(ray.direction, t));
// 	float height_ratio = (hit_info.hit_point.y - cone->center.y) / cone->height;
// 	if (height_ratio < 0.0f || height_ratio > 1.0f)
// 		return (miss());
// 	hit_info.normal = vector3((hit_info.hit_point.x - cone->center.x)
		// / cone->radius, cone->height * (cone->radius / cone->height),
		//(hit_info.hit_point.z - cone->center.z) / cone->radius);
// 	hit_info.material = cone->material;
// 	return hit_info;
// }
