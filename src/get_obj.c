/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:20:15 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:20:15 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_model	get_model(void)
{
	t_model model;
	model.triangles = malloc(sizeof(t_triangle) * 100);
	model.planes = malloc(sizeof(t_plane) * 100);
	char *line;
	char **split;
	t_vector3 *coord;
	t_vector4 *ordre;
	int i;
	int j;

	i = -1;
	j = -1;
	coord = malloc(sizeof(t_vector3) * 100);
	if (!vector3)
		return (model);
	ordre = malloc(sizeof(t_vector4) * 100);
	if (!vector3)
	{
		free(coord);
		return (model);
	}
	int fd;

	fd = open("blender/triangle.obj", O_RDONLY);
	while (line = get_next_line(fd))
	{
		if ((line[0] == 'v' && line[1] == ' ') || line[0] == 'f')
		{
			split = ft_split(line, ' ');
			if (!split)
			{
				free(line);
				free(coord);
				free(ordre);
				return (model);
			}
			if (line[0] == 'v')
			{
				coord[++i].x = ft_atof(split[1]);
				coord[i].y = ft_atof(split[2]);
				coord[i].z = ft_atof(split[3]);
			}
			else if (line[0] == 'f')
			{
				ordre[++j].x = ft_atof(split[1]) - 1;
				ordre[j].y = ft_atof(split[2]) - 1;
				ordre[j].z = ft_atof(split[3]) - 1;
				if (split[4])
				{
					ordre[j].w = ft_atof(split[4]) - 1;
				}
				else
					ordre[j].w = -1;
			}
		}
		free(line);
	}
	int k;
	int l;

	k = 0;
	l = 0;
	while (k + l <= j)
	{
		if (ordre[k + l].w == -1)
		{
			model.triangles[k] = add_triangle(coord[(int)ordre[k + l].x],
				coord[(int)ordre[k + l].y], coord[(int)ordre[k + l].z]);
			// printf("triangle[%d] = %f %f %f \n",k, model.triangles[k].p[0].x, model.triangles[k].p[0].y, model.triangles[k].p[0].z);

			k++;
		}
		else
		{
			// model.planes[l] = add_plane(coord[(int)ordre[k + l].x], bcoord[(int)ordre[k + l].y], coord[(int)ordre[k].z],coord[(int)ordre[k + l].w]);
			l++;
		}
	}

	close(fd);
	free_split(split);
	/*k = -1;
	while (++k <= j)
	{
		l = -1;
		while (++l <=3)
		{
			if (ordre[k].w == -1 && l <= 2)
				printf("triangles[%d].p[%d] = %f %f %f \n",k, l,
					model.triangles[k].p[l].x, model.triangles[k].p[l].y,
					model.triangles[k].p[l].z);
			else if (ordre[k].w != -1 && l <= 3)
				printf("planes[%d].p[%d] = %f %f %f \n",k, l,
					model.planes[k].plane[l].x, model.planes[k].plane[l].y,
					model.planes[k].plane[l].z);
		}
	}*/

	free(coord);
	free(ordre);
	return (model);
}
