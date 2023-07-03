/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:19:44 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:19:44 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_line_camera(const char *line)
{
	char	**inputs;
	int		i;
	int		j;

	inputs = ft_split(line, ' ');
	if (split_size(inputs) != 4)
		return (0);
	i = 0;
	while (inputs[++i] != 0)
	{
		j = -1;
		while (inputs[i][++j] != '\0')
		{
			if (is_non_valid_character(inputs[i][j]))
			{
				printf(\
	"Non valid character on line: \n%s\nObject will not be rendered\n", line);
				free_split(inputs);
				return (0);
			}
		}
	}
	free_split(inputs);
	return (1);
}

t_camera	*init_camera(const char *line, t_input_list *input)
{
	t_camera	*obj;
	int			i;

	obj = (t_camera *)malloc(sizeof(t_camera));
	if (!validate_line_camera(line))
	{
		free(input->name);
		input->name = ft_strdup("inv");
		return (obj);
	}
	i = get_to_next_param(line, 0, input);
	obj->position = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	obj->orientation = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	obj->fov = ft_atof(line + i);
	return (obj);
}

void	validate_values_camera(t_input_list *input)
{
	int			failed;
	t_camera	*obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->orientation, -1.0, 1.0))
	{
		printf("Camera orientation out of range\n");
		failed = 1;
	}
	if (obj->fov < 0 || obj->fov > 180)
	{
		printf("Camera FOV out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}
