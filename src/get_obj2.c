/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:54:35 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/09 23:20:53 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_circle	get_circle_from_cylinder(t_cylinder cylinder, bool is_top)
{
	t_circle	circle;

	circle.radius = cylinder.radius;
	circle.material = cylinder.material;
	if (is_top)
	{
		circle.center = vector3_add(cylinder.center, \
			vector3_multiply_float(cylinder.normal, cylinder.height));
		circle.normal = cylinder.normal;
	}
	else
	{
		circle.center = vector3_subtract(cylinder.center, \
			vector3_multiply_float(cylinder.normal, cylinder.height));
		circle.normal = vector3_multiply_float(cylinder.normal, -1.0f);
	}
	return (circle);
}

void	get_cylinder(t_minirt *minirt, t_cylinder cylinder)
{
	int	i;

	if (minirt->scene.nb_cylinder == 0)
		minirt->scene.cylinder = malloc(sizeof(t_cylinder));
	else
		minirt->scene.cylinder = ft_realloc(minirt->scene.cylinder,
				sizeof(t_cylinder) * (minirt->scene.nb_cylinder + 1));
	if (!minirt->scene.cylinder)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		minirt->error = 1;
		return ;
	}
	i = minirt->scene.nb_cylinder++;
	cylinder.normal = vector3_normalize(cylinder.normal);
	cylinder.material.color = vector3_multiply_float(
			cylinder.color, 1 / 255.0f);
	cylinder.circle_bottom = get_circle_from_cylinder(cylinder, 0);
	cylinder.circle_top = get_circle_from_cylinder(cylinder, 1);
	minirt->scene.cylinder[i] = cylinder;
	minirt->scene.cylinder[i].material.color = vector3_multiply_float(
			cylinder.color, 1 / 255.0f);
}

t_circle	get_circle_from_cone(t_cone cone)
{
	t_circle	circle;

	circle.center = vector3_add(cone.center, vector3_multiply_float(
				cone.normal, cone.height));
	circle.radius = cone.radius * cone.height / cone.radius;
	circle.normal = cone.normal;
	circle.material = cone.material;
	return (circle);
}

void	get_cone(t_minirt *minirt, t_cone cone)
{
	int	i;

	if (minirt->scene.nb_cone == 0)
		minirt->scene.cone = malloc(sizeof(t_cone));
	else
		minirt->scene.cone = ft_realloc(minirt->scene.cone, sizeof(t_cone)
				* (minirt->scene.nb_cone + 1));
	if (!minirt->scene.cone)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		minirt->error = 1;
		return ;
	}
	i = minirt->scene.nb_cone++;
	cone.normal = vector3_normalize(cone.normal);
	cone.circle = get_circle_from_cone(cone);
	minirt->scene.cone[i] = cone;
	minirt->scene.cone[i].material.color = vector3_multiply_float(
			cone.color, 1 / 255.0f);
}

void	get_plane(t_minirt *minirt, t_plane plane)
{
	int	i;

	if (minirt->scene.nb_plane == 0)
		minirt->scene.plane = malloc(sizeof(t_plane));
	else
		minirt->scene.plane = ft_realloc(minirt->scene.plane, sizeof(t_plane)
				* (minirt->scene.nb_plane + 1));
	if (!minirt->scene.plane)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		minirt->error = 1;
		return ;
	}
	i = minirt->scene.nb_plane++;
	minirt->scene.plane[i] = plane;
	minirt->scene.plane[i].material.color = vector3_multiply_float(
			plane.color, 1 / 255.0f);
}
