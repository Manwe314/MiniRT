/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_collision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:55:36 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/07 17:41:13 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_info	calculate_three(t_ray ray, const t_scene *scene, int i)
{
	t_info	hit_info;
	t_info	closest_hit;

	closest_hit.hit_distance = FLT_MAX;
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
	while (++i < scene->nb_paraboloid)
	{
		hit_info = paraboloid_collision(ray, &scene->paraboloid[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	return (closest_hit);
}

t_info	calculate_two(t_ray ray, const t_scene *scene, int i)
{
	t_info	hit_info;
	t_info	closest_hit;

	closest_hit.hit_distance = FLT_MAX;
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
	while (++i < scene->nb_cone)
	{
		hit_info = cone_collision(ray, &scene->cone[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	return (closest_hit);
}

t_info	calculate_one(t_ray ray, const t_scene *scene, int i)
{
	t_info	hit_info;
	t_info	closest_hit;

	closest_hit.hit_distance = FLT_MAX;
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
	while (++i < scene->nb_hyperboloid)
	{
		hit_info = hyperboloid_collision(ray, &scene->hyperboloid[i]);
		if (hit_info.hit_distance < closest_hit.hit_distance)
			closest_hit = hit_info;
	}
	return (closest_hit);
}

t_info	calculate_ray_collision(t_ray ray, const t_scene *scene)
{
	t_info	hit_info;
	t_info	closest_hit;

	closest_hit.hit_distance = FLT_MAX;
	hit_info = calculate_one(ray, scene, -1);
	if (hit_info.hit_distance < closest_hit.hit_distance)
		closest_hit = hit_info;
	hit_info = calculate_two(ray, scene, -1);
	if (hit_info.hit_distance < closest_hit.hit_distance)
		closest_hit = hit_info;
	hit_info = calculate_three(ray, scene, -1);
	if (hit_info.hit_distance < closest_hit.hit_distance)
		closest_hit = hit_info;
	return (closest_hit);
}
