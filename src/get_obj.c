/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:52:09 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/05 13:52:09 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

float ft_atof(const char* str)
{
    int i = 0;
    int sign = 1;
    float result = 0.0;
    float fraction = 0.0;
    float divisor = 10.0;

    while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i] != '\0')
        i++;
    if (str[i] == '-')
	{
        sign = -1;
        i++;
    }
	else if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
	{
        i++;
        while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
		{
            fraction += (str[i] - '0') / divisor;
            divisor *= 10.0;
            i++;
        }
    }
    result += fraction;
	result = roundf(result * 100) / 100;
    result *= sign;
    return (result);
}

t_scene get_obj(void)
{
	t_scene scene;
	char *line;
	char **split;
	t_vec3 *coord;
	t_vec4 *ordre;
	int i;
	int j;

	i = -1;
	j = -1;
	coord = malloc(sizeof(t_vec3) * 100);
	if (!vec3)
		return (scene);
	ordre = malloc(sizeof(t_vec4) * 100);
	if (!vec3)
	{
		free(coord);
		return (scene);
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
				return (scene);
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
			scene.triangles[k] = add_triangle(coord[(int)ordre[k + l].x], coord[(int)ordre[k + l].y], coord[(int)ordre[k + l].z]);
			printf("ordre[%d] = %f %f %f \n",k + l, ordre[k].x, ordre[k].y, ordre[k].z);
			printf("triangle[%d] = %f %f %f \n",k, scene.triangles[k].p[0].x, scene.triangles[k].p[0].y, scene.triangles[k].p[0].z);

			k++;
		}
		else
		{
			scene.planes[l] = add_plane(coord[(int)ordre[k + l].x], coord[(int)ordre[k + l].y], coord[(int)ordre[k].z], coord[(int)ordre[k + l].w]);
			l++;
		}
	}

	close(fd);
	// while (split[++i])
		// free(split[i]);
	k = -1;
	/*while (++k <= j)
	{
		l = -1;
		while (++l <=3)
		{
			if (ordre[k].w == -1 && l <= 2)
				printf("triangles[%d].p[%d] = %f %f %f \n",k, l, scene.triangles[j].p[l].x, scene.triangles[j].p[l].y, scene.triangles[j].p[l].z);
			else if (ordre[k].w != -1 && l <= 3)
				printf("planes[%d].p[%d] = %f %f %f \n",k, l, scene.planes[j].p[l].x, scene.planes[j].p[l].y, scene.planes[j].p[l].z);
		}
	}*/
	free(split);
	free(coord);
	free(ordre);
	return (scene);
}
