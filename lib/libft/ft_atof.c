/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:57:56 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/06 10:57:56 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(const char *str)
{
	float	result;
	float	fractionfactor;
	int		sign;

	result = 0.0;
	fractionfactor = 0.1;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' && *str++)
		sign = -1;
	while (ft_isdigit(*str))
		result = result * 10 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			result += (*str++ - '0') * fractionfactor;
			fractionfactor *= 0.1;
		}
	}
	return (result * sign);
}
