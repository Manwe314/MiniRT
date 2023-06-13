/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:41:46 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/12 15:41:46 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_info	sphere_collision(t_ray ray, t_sphere sphere)
{
	t_info hit_info;
	t_vector3 oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	hit_info.hit_distance = FLT_MAX;
	oc = vector3_subtract(ray.origin, sphere.center);
	a = vector3_dot(ray.direction, ray.direction);
	b = 2.0f * vector3_dot(oc, ray.direction);
	c = vector3_dot(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit_info);
	t = (-b - sqrt(discriminant)) / (2.0f * a);
	if (t < 0.0f)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = vector3_normalize(vector3_subtract(hit_info.hit_point, sphere.center));
	hit_info.material = sphere.material;
	hit_info.sphere = sphere;
	return (hit_info);
}

t_info	calculate_ray_collision(t_ray ray, t_scene scene)
{
	t_info hit_info;
	t_info closest_hit;
	int i;

	closest_hit.hit_distance = FLT_MAX;
	i = -1;
	while (++i < scene.nb_sphere)
	{
		hit_info = sphere_collision(ray, scene.sphere[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	return (closest_hit);
}



t_vector4 PerPixel(t_ray ray, t_scene scene, uint rng_seed)
{
	t_vector3 raycolor;
	t_vector3 incoming_light;
	int bounce;
	t_info hit_info;

	bounce = 0;
	raycolor = vector3(1.0f, 1.0f, 1.0f);
	incoming_light = vector3(0.0f, 0.0f, 0.0f);
	while (bounce++ < 5)
	{
		hit_info = calculate_ray_collision(ray, scene);
		if (hit_info.hit_distance != FLT_MAX)
		{
			//return (vector4(hit_info.material.color.x, hit_info.material.color.y, hit_info.material.color.z, 1.0f));
			ray.origin = hit_info.hit_point;
			ray.direction = vector3_normalize(vector3_add(hit_info.normal, random_direction(rng_seed)));

			// Update light calculation
			t_vector3 emitted_light = vector3_multiply_float(hit_info.material.emission_color, hit_info.material.emission_strength);
			incoming_light = vector3_add(incoming_light, vector3_multiply(emitted_light, raycolor));
			raycolor = vector3_multiply(raycolor, hit_info.material.color);
			//printf("incoming_light: %f %f %f\n", incoming_light.x, incoming_light.y, incoming_light.z);
		}
		else
		{
			// return vector4(1.0f, 0.0f, 0.0f, 1);
			break;
		}
	}
	return (vector4(incoming_light.x, incoming_light.y, incoming_light.z, 1.0f));
}
