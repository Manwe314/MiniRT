/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:56:41 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/09 13:11:42 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	min(float a, float b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

float	max(float a, float b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

float	to_radian(float angle)
{
	return (angle * (M_PI / 180));
}

void	ft_draw_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	ft_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t	*pixelstart;

	pixelstart = &image->pixels[(y * image->width + x) * sizeof(uint32_t)];
	ft_draw_pixel(pixelstart, color);
}
