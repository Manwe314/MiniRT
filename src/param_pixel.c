/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:50:20 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/07 17:33:14 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	something_changed(t_minirt *minirt)
{
	if (minirt->moved == true || minirt->resized == true)
		return (true);
	return (false);
}

bool	should_stop(t_minirt *minirt)
{
	if (minirt->stop == true)
		return (true);
	return (false);
}

void	free_param(t_param *param)
{
	free(param->ray);
	free(param->accum_c);
}

void	malloc_param(t_param *param, t_minirt *minirt)
{
	param->ray = malloc(sizeof(t_ray) * (minirt->width * minirt->height));
	param->accum_c = malloc(sizeof(t_vector3)
			* (minirt->width * minirt->height));
}
