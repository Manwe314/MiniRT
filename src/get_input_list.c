/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:20:08 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:20:08 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*remove_new_line(char *line)
{
	int		size;
	int		i;
	char	*new;

	if (line == 0)
		return (0);
	size = ft_strlen(line);
	new = malloc(sizeof(char) * size);
	i = 0;
	while (i < size - 1)
	{
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	free(line);
	return (new);
}

char	*get_name(const char *line)
{
	int		i;
	char	*name;

	i = 0;
	name = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (line[i] == 'A' && line[i + 1] == ' ')
		name = ft_strdup("Ambient");
	if (line[i] == 'C' && line[i + 1] == ' ')
		name = ft_strdup("Camera");
	if (line[i] == 'L' && line[i + 1] == ' ')
		name = ft_strdup("Light");
	if (line[i + 1] == '\0' && name == 0)
		return (0);
	if (line[i] == 's' && line[i + 1] == 'p' && line[i + 2] == ' ')
		name = ft_strdup("Sphere");
	if (line[i] == 'p' && line[i + 1] == 'l' && line[i + 2] == ' ')
		name = ft_strdup("Plane");
	if (line[i] == 'c' && line[i + 1] == 'y' && line[i + 2] == ' ')
		name = ft_strdup("Cylinder");
	return (name);
}

void	*get_object(t_input_list *input, const char *line)
{
	void	*object;

	if (input->name == 0)
		return (0);
	if (ft_strncmp(input->name, "Ambient", 7) == 0)
		object = init_ambient(line, input);
	if (ft_strncmp(input->name, "Camera", 6) == 0)
		object = init_camera(line, input);
	if (ft_strncmp(input->name, "Light", 5) == 0)
		object = init_light(line, input);
	if (ft_strncmp(input->name, "Sphere", 6) == 0)
		object = init_sphere(line, input);
	if (ft_strncmp(input->name, "Plane", 5) == 0)
		object = init_plane(line, input);
	if (ft_strncmp(input->name, "Cylinder", 8) == 0)
		object = init_cylinder(line, input);
	return (object);
}

void	get_input_list(t_minirt *minirt, int fd)
{
	t_input_list	*head;
	t_input_list	*temp;
	t_input_list	*save;
	char			*line;

	line = remove_new_line(get_next_line(fd));
	temp = (t_input_list *)malloc(sizeof(t_input_list));
	head = temp;
	while (line != 0)
	{
		if (ft_strlen(line) > 1 && !is_all_space(line))
		{
			temp->name = get_name(line);
			temp->object = get_object(temp, line);
				// need to fix errored edge casees
			temp->next = (t_input_list *)malloc(sizeof(t_input_list));
			save = temp;
			temp = temp->next;
		}
		free(line);
		line = remove_new_line(get_next_line(fd));
	}
	free(save->next);
	save->next = 0;
	minirt->input_head = head;
}
