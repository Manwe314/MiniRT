/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:46:34 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/10 16:01:19 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	close_function(void *param)
{
	t_minirt	*minirt;

	minirt = param;
	mlx_delete_image(minirt->mlx, minirt->img);
	free(minirt->input_head->name);
	free(minirt->input_head->object);
}
