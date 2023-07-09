/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_collision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:55:36 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/09 16:04:37 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_info	return_closest(t_info closest_hit, t_info hit_info)
{
	if (hit_info.hit_distance < closest_hit.hit_distance)
		closest_hit = hit_info;
	return (closest_hit);
}

t_info	calculate_three(t_ray ray, const t_scene *scene, int i)
{
	t_info	hit_info;
	t_info	closest_hit;

	closest_hit.hit_distance = FLT_MAX;
	while (++i < scene->nb_cylinder)
	{
		hit_info = cylinder_collision(ray, &scene->cylinder[i]);
		closest_hit = return_closest(closest_hit, hit_info);
		hit_info = circle_collision(ray, &scene->cylinder[i].circle_top);
		closest_hit = return_closest(closest_hit, hit_info);
		hit_info = circle_collision(ray, &scene->cylinder[i].circle_bottom);
		closest_hit = return_closest(closest_hit, hit_info);
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
		closest_hit = return_closest(closest_hit, hit_info);
	}
	i = -1;
	while (++i < scene->nb_cone)
	{
		hit_info = cone_collision(ray, &scene->cone[i]);
		closest_hit = return_closest(closest_hit, hit_info);
		hit_info = circle_collision(ray, &scene->cone[i].circle);
		closest_hit = return_closest(closest_hit, hit_info);
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
		closest_hit = return_closest(closest_hit, hit_info);
	}
	i = -1;
	while (++i < scene->nb_plane)
	{
		hit_info = plane_collision(ray, &scene->plane[i]);
		closest_hit = return_closest(closest_hit, hit_info);
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
