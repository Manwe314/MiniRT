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
	t = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (t < 0.0f)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = vector3_normalize(vector3_subtract(hit_info.hit_point, sphere.center));
	hit_info.material = sphere.material;
	return (hit_info);
}

t_info	plane_collision(t_ray ray, t_plane plane)
{
	t_info hit_info;
	float t;

	hit_info.hit_distance = FLT_MAX;
	t = vector3_dot(vector3_subtract(plane.point_on_plane, ray.origin), plane.normal) / vector3_dot(ray.direction, plane.normal);
	if (t < 0.0f)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = plane.normal;
	hit_info.material = plane.material;
	return (hit_info);
}

t_info circle_collision(t_ray ray, t_circle cirle)
{
	t_info hit_info;
	float t;

	hit_info.hit_distance = FLT_MAX;
	t = vector3_dot(vector3_subtract(cirle.center, ray.origin), cirle.normal) / vector3_dot(ray.direction, cirle.normal);
	if (t < 0.0f)
		return (hit_info);
	float distance_to_center = vector3_length(vector3_subtract(cirle.center, vector3_add(ray.origin, vector3_multiply_float(ray.direction, t))));
	if (distance_to_center > cirle.radius)
		return (hit_info);
	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	hit_info.normal = cirle.normal;
	hit_info.material = cirle.material;
	return (hit_info);
}


bool 	check_cylinder_height(t_cylinder cylinder, t_vector3 hit_point)
{
	t_vector3 cylinder_top;
	t_vector3 cylinder_bottom;
	t_vector3 cylinder_height;
	float height;

	cylinder_top = vector3_add(cylinder.center, vector3_multiply_float(cylinder.normal, cylinder.height));
	cylinder_bottom = vector3_subtract(cylinder.center, vector3_multiply_float(cylinder.normal, cylinder.height));
	cylinder_height = vector3_subtract(cylinder_top, cylinder_bottom);
	height = vector3_dot(vector3_subtract(hit_point, cylinder_bottom), cylinder_height);
	if (height < 0.0f || height > vector3_dot(cylinder_height, cylinder_height))
		return (false);
	return (true);
}

t_info	cylinder_collision(t_ray ray, t_cylinder cylinder)
{
	t_info hit_info;
	t_vector3 oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	hit_info.hit_distance = FLT_MAX;
	oc = vector3_subtract(ray.origin, cylinder.center);
	a = vector3_dot(ray.direction, ray.direction) - pow(vector3_dot(ray.direction, cylinder.normal), 2);
	b = 2.0f * (vector3_dot(oc, ray.direction) - vector3_dot(ray.direction, cylinder.normal) * vector3_dot(oc, cylinder.normal));
	c = vector3_dot(oc, oc) - pow(vector3_dot(oc, cylinder.normal), 2) - cylinder.radius * cylinder.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (hit_info);
		hit_info = circle_collision(ray, cylinder.circle_top);
		if (hit_info.hit_distance != FLT_MAX)
			return (hit_info);
		hit_info = circle_collision(ray, cylinder.circle_bottom);
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
	hit_info.normal = vector3_normalize(vector3_subtract(hit_info.hit_point, cylinder.center));
	hit_info.material = cylinder.material;
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
	i = -1;
	while (++i < scene.nb_plane)
	{
		hit_info = plane_collision(ray, scene.plane[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene.nb_cylinder)
	{
		hit_info = cylinder_collision(ray, scene.cylinder[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
		hit_info = circle_collision(ray, scene.cylinder[i].circle_top);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
		hit_info = circle_collision(ray, scene.cylinder[i].circle_bottom);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene.nb_circle)
	{
		hit_info = circle_collision(ray, scene.circle[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	return (closest_hit);
}

t_vector3 lerp(t_vector3 a, t_vector3 b, float t)
{
	if (t == 0.0f)
		return (a);
	if (t == 1.0f)
		return (b);
	if (t == 0.5f)
		return (vector3_multiply_float(vector3_add(a, b), 0.5f));
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
	while (bounce++ < 3)
	{
		hit_info = calculate_ray_collision(ray, scene);
		if (hit_info.hit_distance != FLT_MAX)
		{

			//return (vector4(hit_info.material.color.x, hit_info.material.color.y, hit_info.material.color.z, 1.0f));
			ray.origin = hit_info.hit_point;
			//ray.direction = vector3_normalize(vector3_add(hit_info.normal, random_direction(rng_seed)));

			// Update light calculation
			t_vector3 emitted_light = vector3_multiply_float(hit_info.material.emission_color, hit_info.material.emission_strength);
			incoming_light = vector3_add(incoming_light, vector3_multiply(emitted_light, raycolor));
			raycolor = vector3_multiply(raycolor, hit_info.material.color);

			bool is_specular_bounce = hit_info.material.specular_probability >= randomvalue(rng_seed);
			t_vector3 diffusedir = vector3_normalize(vector3_add(hit_info.normal, random_direction(rng_seed)));
			t_vector3 speculardir = vector3_reflect(ray.direction, hit_info.normal);
			ray.direction = vector3_normalize(lerp(diffusedir, speculardir, hit_info.material.smoothness * is_specular_bounce));

			// Update light calculations
			raycolor = vector3_multiply(raycolor, lerp(hit_info.material.color, hit_info.material.specular_color, is_specular_bounce));
			//printf("raycolor: %f %f %f\n", raycolor.x, raycolor.y, raycolor.z);
		}
		else
		{
			incoming_light = vector3_add(incoming_light, vector3(0.6f, 0.7f, 0.8f));
			break;
		}
	}
	return (vector4(incoming_light.x, incoming_light.y, incoming_light.z, 1.0f));
}
