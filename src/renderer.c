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

t_vector4 renderer(t_ray ray, t_minirt *minirt)
{
	t_vector4 color;
	t_sphere* closestsphere = 0;
	float closest = FLT_MAX;


	color = vector4(0.0f, 0.0f, 0.0f, 1.0f);
	t_sphere sphere[2];
	int nb_sphere = 2;
	int i = -1;
	sphere[0] = add_sphere(vector3(0.5f, 0.5f, 0.0f), 1.0f, vector3(1.0f, 0.0f, 0.0f));
	sphere[1] = add_sphere(vector3(0.0f, 0.0f, 0.0f), 1.0f, vector3(0.0f, 1.0f, 0.0f));
	//t_vector3 oc = ray.origin;

	while (++i < nb_sphere)
	{
		t_vector3 oc = vector3_subtract(ray.origin, sphere[i].center);

		float a = dot_product(ray.direction, ray.direction);
		float b = 2.0f * dot_product(oc, ray.direction);
		float c = dot_product(oc, oc) - sphere[i].radius * sphere[i].radius;

		float det = b * b - 4 * a * c;
		if (det < 0)
			continue;
		float t = (-b - sqrtf(det)) / (2.0f * a);
		if (t < 0)
			continue;
			//t = (-b - sqrtf(det)) / (2.0f * a);
		if (closest > t)
		{
			closest = t;
			closestsphere = &sphere[i];
		}
	}
	if (closestsphere == 0)
		return (color);

	t_vector3 oc = vector3_subtract(ray.origin, closestsphere->center);
	t_vector3 hit = vector3_add(oc, vector3_multiply_float(ray.direction, closest));
	t_vector3 normal = vector3_normalize(hit);
	t_vector3 light_dir = vector3_normalize(vector3(1.0f, 1.0f, 1.0f));
	float diffuse = dot_product(light_dir, normal);
	diffuse = max(diffuse, 0.0f);

	// sphere[i].color = normal;
	// sphere[i].color = vector3_multiply(sphere[i].color, normal);
	// sphere[i].color = vector3_normalize(sphere[i].color);
	// sphere[i].color = vector3_multiply_float(sphere[i].color, 0.5f);
	// sphere[i].color = vector3_add_float(sphere[i].color, 0.5f);

	closestsphere->color = vector3_multiply_float(closestsphere->color, diffuse);
	color = vector4(closestsphere->color.x, closestsphere->color.y, closestsphere->color.z, 1.0f);
	return (color);
}











