/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:15:54 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/06 13:15:54 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3 vector3_normal(t_vector3 a,t_vector3 b)
{
    t_vector3 normal;
    normal.x = a.y * b.z - a.z * b.y;
    normal.y = a.z * b.x - a.x * b.z;
    normal.z = a.x * b.y - a.y * b.x;
    return normal;
}

t_vector4 pointintriangle(t_vector2 A, t_vector2 B, t_vector2 C, t_vector2 P)
{
		double s1 = C.y - A.y;
		double s2 = C.x - A.x;
		double s3 = B.y - A.y;
		double s4 = P.y - A.y;
		double w1 = (A.x * s1 + s4 * s2 - P.x * s1) / (s3 * s2 - (B.x-A.x) * s1);
		double w2 = (s4- w1 * s3) / s1;
		if (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1)
			return (vector4(w1, w2, 1.0f - w1 - w2, 1.0f));
		return (vector4(0.0f, 0.0f, 0.0f, 1.0f));
}

/*t_vector4 renderer(t_vector2 coord, t_minirt *minirt)
{
	t_vector3 u,v,normal, t[3];
	t_vector2 x, y, z, a,b;
	t_vector4 color;
	//float x,y,z;
	int i = -1;

	while (++i < 3)
	{
		t[0] = minirt->model.triangles[i].p[0];
		t[1] = minirt->model.triangles[i].p[1];
		t[2] = minirt->model.triangles[i].p[2];
		// u = vector3_subtract(minirt->model.triangles[i].p[0], minirt->model.triangles[i].p[1]);
		// v = vector3_subtract(minirt->model.triangles[i].p[0], minirt->model.triangles[i].p[2]);
		// normal = vector3_normal(u,v);
		// c = vector3_subtract(minirt->model.triangles[i].pos1, minirt->camera.pos);
		x = vector2(t[0].x / t[0].z, t[0].y / t[0].z);
		y = vector2(t[1].x / t[1].z, t[1].y / t[1].z);
		z = vector2(t[2].x / t[2].z, t[2].y / t[2].z);
		color = pointintriangle(y, x, z, coord);
		if (color.x != 0.0f || color.y != 0.0f || color.z != 0.0f)
			return (color);
	}
	return (vector4(0.0f, 0.0f, 0.0f, 1.0f));
}*/



int	touch_sphere(t_ray ray, t_sphere sphere)
{
	t_vector3 oc = vector3_subtract(ray.origin, sphere.center);

	float a = dot_product(ray.direction, ray.direction);
	float b = 2.0f * dot_product(oc, ray.direction);
	float c = dot_product(oc, oc) - sphere.radius * sphere.radius;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	float t = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (t < 0)
		t = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (t < 0)
		return (0);
	return (t);
}

t_vector4 renderer(t_vector2 coord, t_minirt *minirt)
{
	t_vector4 color;
	t_ray ray;


	ray.origin = minirt->camera.pos;
	ray.direction = vector3(coord.x, coord.y, -1.0f);
	// ray.direction = multiplymatrixvector(vector3(coord.x, coord.y, 1.0), minirt->camera.inv_lookat);
	// ray.direction = vector3_normalize(vector3(coord.x, coord.y, 1));

	color = vector4(0.0f, 0.0f, 0.0f, 1.0f);
	t_sphere sphere[2];
	int nb_sphere = 1;
	int i = 0;
	sphere[0] = add_sphere(vector3(0.0f, -1.0f, 3.0f), 0.5f, vector3(1.0f, 0.0f, .0f));
	//sphere[1] = add_sphere(vector3(0.0f, 1.0f, 0.0f), 1.0f, vector3(0.0f, 1.0f, 0.0f));
	//t_vector3 oc = vector3_subtract(ray.origin, sphere->center);
	t_vector3 oc = ray.origin;

	float a = dot_product(ray.direction, ray.direction);
	float b = 2.0f * dot_product(oc, ray.direction);
	float c = dot_product(oc, oc) - sphere->radius * sphere->radius;

	float det = b * b - 4 * a * c;
	if (det < 0)
		return (color);
	float t = (-b - sqrtf(det)) / (2.0f * a);
	if (t < 0)
		return (color);
		//t = (-b - sqrtf(det)) / (2.0f * a);
	//if (t < 0)
	t_vector3 hit = vector3_add(oc, vector3_multiply_float(ray.direction, t));
	t_vector3 normal = vector3_normalize(hit);
	t_vector3 light_dir = vector3_normalize(vector3(1.0f, 1.0f, 1.0f));
	float diffuse = dot_product(light_dir, normal);
	diffuse = max(diffuse, 0.0f);
	sphere->color = normal;
	sphere->color = vector3_multiply_float(sphere->color, 0.5f);
	sphere->color = vector3_add_float(sphere->color, 0.5f);
	sphere->color = vector3_multiply_float(sphere->color, diffuse);
	color = vector4(sphere->color.x, sphere->color.y, sphere->color.z, 1.0f);
	return (color);
}











