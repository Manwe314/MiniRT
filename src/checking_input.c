/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:19:17 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/05 18:19:46 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int is_non_valid_character(char a)
{
	if (a >= '0' && a <= '9')
		return (0);
	if (a == '.' || a == ',' || a == '-' || a)
		return (0);
	return (1);

}

int check_file(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	len -= 3;
	if (ft_strncmp((file_name + len), ".rt", 3) != 0)
		return (1);
	len = open(file_name, O_RDONLY);
	if (len < 0)
	{
		perror(file_name);
		return (1);
	}
	close(len);
	return (0);
}
int vector3_checker(t_vector3 vector3, float range_min, float range_max)
{
	if (vector3.x < range_min || vector3.x > range_max)
		return (0);
	if (vector3.y < range_min || vector3.y > range_max)
		return (0);
	if (vector3.z < range_min || vector3.z > range_max)
		return (0);
	return (1);
}
