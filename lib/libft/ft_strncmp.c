/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:09:30 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/05 19:41:45 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	if (s1 == 0 && s2 != 0)
		return (-1);
	if (s1 != 0 && s2 == 0)
		return (1);
	if (s1 == 0 && s2 == 0)
		return (0);
	i = 0;
	while (s1[i] && --n && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
