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
	if (line[size - 1] != '\n')
		return (line);
	new = malloc(sizeof(char) * size);
	if (new == 0)
		return (0);
	i = -1;
	while (++i < size - 1)
		new[i] = line[i];
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
	if (line[i] == 'c' && line[i + 1] == 'o' && line[i + 2] == ' ')
		name = ft_strdup("Cone");
	return (name);
}

void	*get_object(t_input_list *input, const char *line)
{
	if (input->name == 0)
		return (0);
	if (ft_strncmp(input->name, "Ambient", 7) == 0)
		return (init_ambient(line, input));
	if (ft_strncmp(input->name, "Camera", 6) == 0)
		return (init_camera(line, input));
	if (ft_strncmp(input->name, "Light", 5) == 0)
		return (init_light(line, input));
	if (ft_strncmp(input->name, "Sphere", 6) == 0)
		return (init_sphere(line, input));
	if (ft_strncmp(input->name, "Plane", 5) == 0)
		return (init_plane(line, input));
	if (ft_strncmp(input->name, "Cylinder", 8) == 0)
		return (init_cylinder(line, input));
	if (ft_strncmp(input->name, "Cone", 4) == 0)
		return (init_cone(line, input));
	return (0);
}

int	check_number(char *line, int i)
{
	int		j;
	int		dot;
	int		k;

	dot = 0;
	printf("%s\n", line + i);
	j = i - 1;
	while (line[++j] != '\0' && line[j] != ' ' && line[j] != '\t'
		&& line[j] != ',' && j < i + 22)
	{
		if (ft_isdigit(line[j]))
			continue ;
		if (line[j] == '.')
		{
			if (dot == true)
			{
				printf("Error dot\n");
				return (-1);
			}
			dot = j;
		}
		else if (((line[j] == '+' || line[j] == '-') && j != i) || ft_isalpha(line[j]))
		{
			printf("Error - \n");
			return (-1);
		}
	}
	k = 0;
	printf("line %s\n", line + i);
	while (line[i + k] != '.' && line[i + k] != '\0' && ft_isdigit(line[j]) && k < 13)
		k++;
	printf("k = %d\n", k);
	if (k > 11)
	{
		printf("Error longueur %d\n", k);
		return (-1);
	}
	k = 0;
	if (dot != 0)
	{
		while (line[dot + k] != '\0' && ft_isdigit(line[j]) && k < 13)
			k++;
		printf("k = %d\n", k);
		if (k > 11)
		{
			printf("Error longueur dot%d\n", k);
			return (-1);
		}
	}
	return (j);
}

bool	check_line(char *str, t_minirt *minirt)
{
	int	i;

	i = 1;
	while (str[++i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\0')
			continue ;
		else if ((str[i] == '+' || str[i] == '-' || ft_isdigit(str[i])) || str[i] == ',')
		{
			i = check_number(str, i);
			printf("i = %d\n", i);
			if (i == -1)
			{
				minirt->input_validity = -1;
				printf("Error number\n");
				return (false);
			}
			if (str[i] == '\0')
				break ;
		}
		else
		{
			minirt->input_validity = -1;
			printf("Error char\n");
			return (false);
		}
	}
	minirt->input_validity = 1;
	return (true);
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
	save = 0;
	while (line != 0)
	{
		if (ft_strlen(line) > 1 && !is_all_space(line)/* && check_line(line, minirt)*/)
		{
			temp->name = get_name(line);
			temp->object = get_object(temp, line);
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
