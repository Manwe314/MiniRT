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
	i = -1;
	while (++i < scene.nb_triangle)
	{
		hit_info = triangle_collision(ray, scene.triangle[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene.nb_paraboloid)
	{
		hit_info = paraboloid_collision(ray, scene.paraboloid[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene.nb_cone)
	{
		hit_info = cone_collision(ray, scene.cone[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene.nb_hyperboloid)
	{
		hit_info = hyperboloid_collision(ray, scene.hyperboloid[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	
	return (closest_hit);
}

t_vector3 lerp(t_vector3 a, t_vector3 b, float t)
{
	t_vector3 result;

	result.x = a.x + (b.x - a.x) * t;
	result.y = a.y + (b.y - a.y) * t;
	result.z = a.z + (b.z - a.z) * t;
	return (result);	
}

t_vector2 vector2_mod(t_vector2 a, float b)
{
	t_vector2 result;

	result.x = a.x - b * floor(a.x / b);
	result.y = a.y - b * floor(a.y / b);
	return (result);
}

t_vector2 vector2_floor(t_vector2 a)
{
	return (vector2(floor(a.x), floor(a.y)));
}

t_vector4 perpixel(t_ray ray, t_scene scene, uint rng_seed)
{
	t_vector3 raycolor;
	t_vector3 incoming_light;
	int bounce;
	float ray_per_pixel = 1.0f;
	t_info hit_info;
	t_vector3 color_obj;

	int i = 0;
	color_obj = vector3(0.0f, 0.0f, 0.0f);
	while (i++ < ray_per_pixel)
	{
		bounce = 0;
		raycolor = vector3(1.0f, 1.0f, 1.0f);
		incoming_light = vector3(0.0f, 0.0f, 0.0f);
		while (bounce++ < 5)
		{
			hit_info = calculate_ray_collision(ray, scene);
			if (hit_info.hit_distance != FLT_MAX)
			{
				ray.origin = hit_info.hit_point;
				ray.origin = vector3_add(ray.origin, vector3_multiply_float(hit_info.normal, 0.0001f));

				t_vector3 diffuse = vector3_normalize(vector3_add(hit_info.normal, random_direction(rng_seed)));
				t_vector3 reflect = vector3_reflect(ray.direction, hit_info.normal);

				bool is_specular_bounce = hit_info.material.specular_probability >= randomvalue(rng_seed);

				ray.direction = vector3_normalize(lerp(diffuse, reflect, hit_info.material.smoothness * is_specular_bounce));
			
				incoming_light = vector3_add(incoming_light, vector3_multiply(hit_info.material.emission, raycolor));
				raycolor = vector3_multiply(raycolor, lerp(hit_info.material.color, hit_info.material.specular_color, is_specular_bounce));
			
				float p = fmaxf(raycolor.x, fmaxf(raycolor.y, raycolor.z));
				
				if (randomvalue(rng_seed) >= p)
					break;
				raycolor = vector3_multiply_float(raycolor, 1.0f / p);
			
			}
			else
			{
				//incoming_light = vector3_add(incoming_light, vector3(0.6f, 0.7f, 0.8f));
				break;
			}
		}
		color_obj = vector3_add(color_obj, incoming_light);
	}
	color_obj = vector3_multiply_float(color_obj, 1 / ray_per_pixel);
	return (vector4(color_obj.x, color_obj.y, color_obj.z, 1.0f));
}

t_vector4	can_see_light(t_ray ray, t_scene scene, t_vector3 color_obj)
{
	int	i;
	int nb_light;
	float brightness;
	t_vector3 color;

	nb_light = 0;
	brightness = 0.0f;
	color = vector3(0.0f, 0.0f, 0.0f);

	i = -1;
	while (++i < scene.nb_light)
	{
		ray.direction = vector3_normalize(vector3_subtract(scene.light[i].position, ray.origin));
		//ray.direction = vector3_normalize(vector3_add(ray.direction, random_direction(0)));
		if (calculate_ray_collision(ray, scene).hit_distance >= vector3_length(ray.direction))
		{
			color = vector3_add(color, vector3_multiply_float(scene.light[i].color, scene.light[i].brightness));
			nb_light++;
		}
	}
	if (nb_light == 0)
	{
		return (vector4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	color_obj = vector3_multiply(color_obj, color);
	return (vector4(color_obj.x, color_obj.y, color_obj.z, 1.0f));
}


t_vector4 Perpixel(t_ray ray, t_scene scene, uint rng_seed)
{
	t_vector3 raycolor;
	t_vector3 incoming_light;
	t_info hit_info;

	raycolor = vector3(0.0f, 0.0f, 0.0f);
	// return (vector4(raycolor.x, raycolor.y, raycolor.z, 1.0f));

	hit_info = calculate_ray_collision(ray, scene);
	if (hit_info.hit_distance != FLT_MAX)
	{
		return (vector4(hit_info.material.color.x, hit_info.material.color.y, hit_info.material.color.z, 1.0f));
		ray.origin = hit_info.hit_point;
		ray.origin = vector3_add(ray.origin, vector3_multiply_float(hit_info.normal, 0.0001f));
		return (can_see_light(ray, scene, hit_info.material.color));
	}

	return (vector4(raycolor.x, raycolor.y, raycolor.z, 1.0f));
}