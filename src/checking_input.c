/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:19:51 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:19:51 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	material_checker(t_material mat)
{
	if (!vector3_checker(mat.emission_color, 0.0f, 1.0f))
		return (0);
	if (!vector3_checker(mat.specular_color, 0.0f, 1.0f))
		return (0);
	if (mat.emission_strength < 0.0f || mat.emission_strength > 1.0f)
		return (0);
	if (mat.smoothness < 0.0f || mat.smoothness > 1.0f)
		return (0);
	if (mat.specular_probability < 0.0f || mat.specular_probability > 1.0f)
		return (0);
	if (mat.flag != 0 && mat.flag != 1)
		return (0);
	return (1);
}

t_material	get_material_rt(const char *line, t_input_list *input)
{
	int i;
	t_material mat;

	i = 0;
	while (line[i] != 'm' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (return_material());
	i = get_to_next_param(line, i, input);
	mat.emission_color = vector3_multiply_float(get_vector3(line, i, input), \
	(1.0f / 255.0f));
	i = get_to_next_param(line, i, input);
	mat.specular_color = vector3_multiply_float(get_vector3(line, i, input), \
	(1.0f / 255.0f));
	i = get_to_next_param(line, i, input);
	mat.emission_strength = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	mat.smoothness = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	mat.specular_probability = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	mat.flag = ft_atoi(line + i);
	mat.color = vector3(0.0f, 0.0f, 0.0f);
	mat.emission = vector3(0.0f, 0.0f, 0.0f);
	return (mat);
}

int	is_non_valid_character(char a)
{
	if (a >= '0' && a <= '9')
		return (0);
	if (a == '.' || a == ',' || a == '-')
		return (0);
	return (1);
}

int	check_file(char *file_name)
{
	int	len;

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

int	vector3_checker(t_vector3 vector3, float range_min, float range_max)
{
	if (vector3.x < range_min || vector3.x > range_max)
		return (0);
	if (vector3.y < range_min || vector3.y > range_max)
		return (0);
	if (vector3.z < range_min || vector3.z > range_max)
		return (0);
	return (1);
}
