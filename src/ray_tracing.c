/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:21:28 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:21:28 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*t_info	calculate_ray_collision(t_ray ray, const t_scene *scene)
{
	t_info	hit_info;
	t_info	closest_hit;
	int		i;

	closest_hit.hit_distance = FLT_MAX;
	i = -1;
	while (++i < scene->nb_sphere)
	{
		hit_info = sphere_collision(ray, &scene->sphere[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene->nb_plane)
	{
		hit_info = plane_collision(ray, &scene->plane[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene->nb_cylinder)
	{
		hit_info = cylinder_collision(ray, &scene->cylinder[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
		hit_info = circle_collision(ray, &scene->cylinder[i].circle_top);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
		hit_info = circle_collision(ray, &scene->cylinder[i].circle_bottom);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene->nb_circle)
	{
		hit_info = circle_collision(ray, &scene->circle[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene->nb_triangle)
	{
		hit_info = triangle_collision(ray, &scene->triangle[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene->nb_paraboloid)
	{
		hit_info = paraboloid_collision(ray, &scene->paraboloid[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene->nb_cone)
	{
		hit_info = cone_collision(ray, &scene->cone[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	i = -1;
	while (++i < scene->nb_hyperboloid)
	{
		hit_info = hyperboloid_collision(ray, &scene->hyperboloid[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	return (closest_hit);
}*/

t_vector3	add_ambient_light(const t_scene *scene, t_vector3 color_obj)
{
	if (scene->nb_ambient == 0)
		return (color_obj);
	color_obj = vector3_multiply(color_obj, scene->ambient.ambient);
	return (color_obj);
}

t_vector3	color_lights(t_ray ray, const t_scene *scene, uint rng_seed,
						int *nb_light)
{
	int			i;
	t_vector3	color;
	t_vector3	length;

	color = vector3(0.0f, 0.0f, 0.0f);
	i = -1;
	while (++i < scene->nb_light)
	{
		ray.direction = vector3_subtract(scene->light[i].position, ray.origin);
		length = ray.direction;
		if (scene->random == 1)
			ray.direction = vector3_add(ray.direction,
					random_direction(rng_seed));
		ray.direction = vector3_normalize(ray.direction);
		if (calculate_ray_collision(ray, scene).hit_distance
			>= vector3_length(length))
		{
			color = vector3_add(color, vector3_multiply_float(
						scene->light[i].color, scene->light[i].brightness));
			++*nb_light;
		}
	}
	return (color);
}

t_vector3	can_see_light(t_ray ray, const t_scene *scene, t_vector3 color_obj,
		uint rng_seed)
{
	int			nb_light;
	t_vector3	color;

	nb_light = 0;
	color = color_lights(ray, scene, rng_seed, &nb_light);
	if (nb_light == 0)
		return (add_ambient_light(scene, color_obj));
	color_obj = vector3_multiply(color_obj, color);
	color_obj = vector3_multiply_float(color_obj, 1.0f / (nb_light));
	return (color_obj);
}

t_vector3	shoot_ray(t_ray ray, const t_scene *scene, uint rng_seed)
{
	t_vector3	raycolor;
	t_info		hit_info;

	raycolor = vector3(0.0f, 0.0f, 0.0f);
	hit_info = calculate_ray_collision(ray, scene);
	if (hit_info.hit_distance != FLT_MAX)
	{
		ray.origin = hit_info.hit_point;
		ray.origin = vector3_add(ray.origin,
				vector3_multiply_float(hit_info.normal, 0.0001f));
		return (can_see_light(ray, scene, hit_info.material.color, rng_seed));
	}
	return (raycolor);
}
