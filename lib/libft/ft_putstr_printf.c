/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:56:57 by beaudibe          #+#    #+#             */
/*   Updated: 2022/11/20 11:00:16 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_printf(char *s)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[++i])
		j += write(1, &s[i], 1);
	return (j);
}
