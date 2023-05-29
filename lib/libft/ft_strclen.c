/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:58:02 by beaudibe          #+#    #+#             */
/*   Updated: 2023/01/18 12:09:45 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strclen(char *s, char c)
{
	int	i;

	i = -1;
	if (!s)
		return (-1);
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	if (c == 0)
		return (i);
	return (-1);
}
