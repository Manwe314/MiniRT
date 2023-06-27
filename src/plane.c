/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:21:12 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:21:12 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	validate_line_plane(const char *line)
{
	char	**inputs;
	int		i;
	int		j;

	inputs = ft_split(line, ' ');
	if (split_size(inputs) != 4)
		return (0);
	i = 1;
	while (inputs[i] != 0)
	{
		j = 0;
		while (inputs[i][j] != '\0')
		{
			if (is_non_valid_character(inputs[i][j]))
			{
				printf(\
	"Non valid character on line: \n%s\nObject will not be rendered\n", line);
				free_split(inputs);
				return (0);
			}
			j++;
		}
		i++;
	}
	free_split(inputs);
	return (1);
}

t_plane	*init_plane(const char *line, t_input_list *input)
{
	t_plane	*obj;
	int		i;

	obj = (t_plane *)malloc(sizeof(t_plane));
	if (!validate_line_plane(line))
	{
		free(input->name);
		input->name = ft_strdup("inv");
		return (obj);
	}
	i = get_to_next_param(line, 0, input);
	obj->point_on_plane = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	obj->normal = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	obj->color = get_vector3(line, i, input);
	return (obj);
}

void	validate_values_plane(t_input_list *input)
{
	int		failed;
	t_plane	*obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->color, 0.0, 255.0))
	{
		printf("plane color out of range\n");
		failed = 1;
	}
	if (!vector3_checker(obj->normal, -1.0, 1.0))
	{
		printf("plane normal out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}