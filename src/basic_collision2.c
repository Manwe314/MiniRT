/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_collision2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:56:02 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/10 20:22:29 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_info	circle_collision(t_ray ray, const t_circle *cirle)
{
	float	t;
	float	distance_to_center;

	t = vector3_dot(vector3_subtract(cirle->center, ray.origin), cirle->normal) \
		/ vector3_dot(ray.direction, cirle->normal);
	if (t < 0.0f)
		return (miss());
	distance_to_center = vector3_length(vector3_subtract(cirle->center, \
			vector3_add(ray.origin, vector3_multiply_float(ray.direction, \
					t))));
	if (distance_to_center > cirle->radius)
		return (miss());
	return (return_hit_info(ray, t, cirle->material, cirle->normal));
}

bool	check_cylinder_height(const t_cylinder *cylinder, t_vector3 hit_point)
{
	t_vector3	cylinder_top;
	t_vector3	cylinder_bottom;
	t_vector3	cylinder_height;
	float		height;

	cylinder_top = vector3_add(cylinder->center, \
		vector3_multiply_float(cylinder->normal, cylinder->height));
	cylinder_bottom = vector3_subtract(cylinder->center, \
		vector3_multiply_float(cylinder->normal, cylinder->height));
	cylinder_height = vector3_subtract(cylinder_top, cylinder_bottom);
	height = vector3_dot(vector3_subtract(hit_point, cylinder_bottom), \
		cylinder_height);
	if (height < 0.0f || height > vector3_dot(cylinder_height,
			cylinder_height))
		return (false);
	return (true);
}

t_vector3 cylinder_normal(t_vector3 pointOnLine, t_vector3 directionVector)
{
    t_vector3	arbitrarypoint;
    t_vector3	perpendicularvector;

    arbitrarypoint.x = 1.0;
    arbitrarypoint.y = 1.0;
    arbitrarypoint.z = 1.0;
    t_vector3 vectorpq;
    vectorpq = vector3_subtract(arbitrarypoint, pointOnLine);
    
    double dotProduct = vectorpq.x * directionVector.x + vectorpq.y * directionVector.y + vectorpq.z * directionVector.z;
    double dotProductV = directionVector.x * directionVector.x + directionVector.y * directionVector.y + directionVector.z * directionVector.z;

    perpendicularvector.x = vectorpq.x - (dotProduct / dotProductV) * directionVector.x;
    perpendicularvector.y = vectorpq.y - (dotProduct / dotProductV) * directionVector.y;
    perpendicularvector.z = vectorpq.z - (dotProduct / dotProductV) * directionVector.z;
    return perpendicularvector;
}

t_info	cylinder_info(t_ray ray, float t, const t_cylinder *cylinder)
{
	t_info	hit_info;

	hit_info.hit_distance = t;
	hit_info.hit_point = vector3_add(ray.origin, \
		vector3_multiply_float(ray.direction, t));
	if (check_cylinder_height(cylinder, hit_info.hit_point) == false)
		return (miss());
	hit_info.normal = cylinder_normal(cylinder->center, hit_info.hit_point);
	hit_info.material = cylinder->material;
	return (hit_info);
}

/*t_info	cylinder_collision(t_ray ray, const t_cylinder *cylinder)
{
	t_vector3	oc;
	float		abc[3];
	float		discriminant;
	float		t;

	oc = vector3_subtract(ray.origin, cylinder->center);
	abc[0] = vector3_dot(ray.direction, ray.direction)
		- pow(vector3_dot(ray.direction, cylinder->normal), 2);
	abc[1] = 2.0f * (vector3_dot(oc, ray.direction) - vector3_dot \
	(ray.direction, cylinder->normal) * vector3_dot(oc, cylinder->normal));
	abc[2] = vector3_dot(oc, oc) - pow(vector3_dot(oc, cylinder->normal), 2) \
		- cylinder->radius * cylinder->radius;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (miss());
	t = (-abc[1] - sqrt(discriminant)) / (2.0f * abc[0]);
	if (t < 0.0f)
		return (miss());
	return (cylinder_info(ray, t, cylinder));
}*/

t_info	cylinder_collision(t_ray ray, const t_cylinder *cylinder)
{
	t_vector3	oc;
	float		abc[3];
	float		discriminant;
	float		t;

	oc = vector3_subtract(ray.origin, cylinder->center);
	abc[0] = vector3_dot(ray.direction, ray.direction) - \
		pow(vector3_dot(ray.direction, cylinder->normal), 2);
	abc[1] = 2 * (vector3_dot(ray.direction, oc) - \
		vector3_dot(ray.direction, cylinder->normal) * \
		vector3_dot(oc, cylinder->normal));
	abc[2] = vector3_dot(oc, oc) - pow(vector3_dot(oc, cylinder->normal), 2) - \
		pow(cylinder->radius, 2);
	discriminant = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (miss());
	t = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	if (t < 0.0f)
		return (miss());
	return (cylinder_info(ray, t, cylinder));
}




/*

t^2(xD^2+yD^2)+t(2xExD+2yEyD) +(xE^2+yE^2-1)=0

x = 
*/