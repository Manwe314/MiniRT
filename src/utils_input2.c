/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:58:46 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/10 15:41:15 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_malloc(void)
{
	ft_putstr_fd("Error\nMalloc failed\n", 2);
	exit(0);
}

t_vector3	get_vector3(const char *line, int i, t_input_list *input)
{
	char		**values;
	char		*param;
	int			j;
	t_vector3	output;

	j = i;
	while (line[j] != ' ' && line[j] != '\0')
		j++;
	param = ft_substr(line, i, j - i);
	values = ft_split(param, ',');
	if (split_size(values) != 3)
	{
		free(input->name);
		input->name = ft_strdup("inv");
		output = vector3(0, 0, 0);
	}
	else
	{
		output.x = ft_atof(values[0]);
		output.y = ft_atof(values[1]);
		output.z = ft_atof(values[2]);
	}
	free_split(values);
	free(param);
	return (output);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}
