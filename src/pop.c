/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:53:10 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/10 18:56:46 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_info	cylinder_collision(t_ray ray, const t_cylinder *cylinder)
{
	t_vector3	oc;
	float		abc[3];
	float		discriminant;
	float		t;

	oc = vector_sub(ray.origin, cylinder->origin);
	


	
	discriminant = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (miss());
	t = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	if (t < 0.0f)
		return (miss());
	return (cylinder_info(ray, t, cylinder));
}