/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:31:50 by beaudibe          #+#    #+#             */
/*   Updated: 2022/12/08 21:38:59 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "stdio.h"
# include <limits.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_putstr_printf(char *s);
int	ft_putnbr_base_printf(long long nbr, char *base, int a);
int	ft_putchar_printf(char c);
int	ft_putnbr_printf(long long n, int a);

#endif
