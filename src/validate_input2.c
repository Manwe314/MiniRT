/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:47:46 by lkukhale          #+#    #+#             */
/*   Updated: 2023/07/07 19:48:35 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	has_invalid_input(t_input_list *input)
{
	t_input_list	*traverse;
	int				is_invalid;

	traverse = input;
	is_invalid = 0;
	while (traverse != 0)
	{
		if (traverse->name == 0)
			is_invalid = 1;
		traverse = traverse->next;
	}
	return (is_invalid);
}

void	check_esentials(t_minirt *minirt)
{
	t_input_list	*traverse;
	int				has_esentials;
	int				has_an_object;

	has_esentials = 0;
	has_an_object = 0;
	traverse = minirt->input_head;
	while (traverse != 0)
	{
		if (ft_strncmp(traverse->name, "Ambient", 7) == 0
			|| (ft_strncmp(traverse->name, "Camera", 6) == 0)
			|| (ft_strncmp(traverse->name, "Light", 5) == 0))
			has_esentials++;
		else
			has_an_object++;
		traverse = traverse->next;
	}
	if (has_esentials != 3 || has_an_object == 0)
	{
		printf("Error\nCritical error nothing will be rendered\n");
		minirt->input_validity = -1;
	}
	else
		minirt->input_validity = 1;
}

void	validate_input(t_minirt *minirt)
{
	t_input_list	*input;

	input = minirt->input_head;
	while (input != 0)
	{
		if (input->name == 0 || ft_strncmp(input->name, "inv", 3) == 0)
			printf(\
				"Invalid object description, object will not be rendered\n");
		if (ft_strncmp(input->name, "Ambient", 7) == 0)
			validate_values_ambient(input);
		if (ft_strncmp(input->name, "Camera", 6) == 0)
			validate_values_camera(input);
		if (ft_strncmp(input->name, "Light", 5) == 0)
			validate_values_light(input);
		if (ft_strncmp(input->name, "Sphere", 6) == 0)
			validate_values_sphere(input);
		if (ft_strncmp(input->name, "Plane", 5) == 0)
			validate_values_plane(input);
		if (ft_strncmp(input->name, "Cylinder", 8) == 0)
			validate_values_cylinder(input);
		if (ft_strncmp(input->name, "Cone", 4) == 0)
			validate_values_cone(input);
		input = input->next;
	}
	final_prepare_input(minirt);
}
