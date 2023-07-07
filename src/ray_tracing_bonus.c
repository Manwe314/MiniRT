/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:19:08 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/07 16:06:41 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	checker(const t_vector3 *point, const t_info *hit_info)
{
	t_vector3	uv;

	uv = vector3_floor(vector3_multiply_float(*point, 2.0f / 1.0f));
	if ((int)(uv.x + uv.y + uv.z) % 2 == 0)
		return (hit_info->material.color);
	return (hit_info->material.specular_color);
}

void	ray_tracing(t_ray *ray, t_info *hit_info, uint rng_seed,
		t_vector3 *raycolor)
{
	t_vector3	diffuse;
	t_vector3	reflect;
	int			bounce;
	bool		is_specular_bounce;

	if (hit_info->material.flag == CHECKER_PATTERN)
		hit_info->material.color = checker(&hit_info->hit_point, hit_info);
	ray->origin = hit_info->hit_point;
	ray->origin = vector3_add(ray->origin,
			vector3_multiply_float(hit_info->normal, 0.0001f));
	is_specular_bounce = hit_info->material.specular_probability
		>= randomvalue(rng_seed);
	if (is_specular_bounce)
		reflect = vector3_reflect(ray->direction, hit_info->normal);
	else
		reflect = vector3(0.0f, 0.0f, 0.0f);
	diffuse = vector3_add(hit_info->normal, random_direction(rng_seed));
	ray->direction = lerp(diffuse, reflect, hit_info->material.smoothness
			* is_specular_bounce);
	*raycolor = vector3_multiply(*raycolor, lerp(hit_info->material.color,
				hit_info->material.specular_color, is_specular_bounce));
}

bool	is_too_little(t_vector3 *raycolor, t_vector3 *incoming_light,
		const t_info *hit_info, uint rng_seed)
{
	float		p;

	*incoming_light = vector3_add(*incoming_light,
			vector3_multiply(hit_info->material.emission, *raycolor));
	p = fmaxf(raycolor->x, fmaxf(raycolor->y, raycolor->z));
	if (randomvalue(rng_seed) >= p)
		return (true);
	*raycolor = vector3_multiply_float(*raycolor, 1.0f / p);
	return (false);
}

t_vector3	shoot_bonus(t_ray ray, const t_scene *scene, uint rng_seed)
{
	t_vector3	raycolor;
	t_vector3	incoming_light;
	int			bounce;
	t_info		hit_info;
	bool		is_specular_bounce;

	bounce = 0;
	raycolor = vector3(1.0f, 1.0f, 1.0f);
	incoming_light = vector3(0.0f, 0.0f, 0.0f);
	while (bounce++ < 3)
	{
		hit_info = calculate_ray_collision(ray, scene);
		if (hit_info.hit_distance != FLT_MAX)
		{
			ray_tracing(&ray, &hit_info, rng_seed, &raycolor);
			if (is_too_little(&raycolor, &incoming_light, &hit_info, rng_seed))
				break ;
		}
		else
		{
			add_ambient_light(scene, incoming_light);
			break ;
		}
	}
	return (incoming_light);
}
