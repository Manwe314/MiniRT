/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:30:28 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 16:30:28 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
bool	is_normal(float x)
{
	if (x < -1 || x > 1)
		return (false);
	return (true);
}

bool	is_norm(float x)
{
	if (x < 0 || x > 1)
		return (false);
	return (true);
}

bool	is_normal_vec(t_vector3 vec)
{
	if (is_normal(vec.x) == false || is_normal(vec.y) == false \
	|| is_normal(vec.z) == false)
		return (false);
	return (true);
}

bool	number_contain_space(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != ',')
	{
		if (input[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

int	go_to_next(char *input, int i)
{
	int	j;

	j = 0;
	while (input[j] && input[j] == ' ')
		j++;
	while (--i)
	{
		while (input[j] && (ft_isdigit(input[j]) || input[j] == '.' \
		|| input[j] == ',' || input[j] == '-'))
			j++;
		while (input[j] && input[j] == ' ')
			j++;
	}
	return (j);
}


t_vector3	get_vec3(char *input, int *j)
{
	t_vector3	vec;
	float		x[3];
	int			i;
	int			k;

	k = -1;
	if (!*input)
		return (vector3(0, 0, 0));
	i = go_to_next(input, *j);
	while (++k < 3)
	{
		if (k != 2 && number_contain_space(input + i))
		{
			*j = -1;
			ft_putstr_fd("Error\nWrong vector format\n", 2);
			return (vector3(0, 0, 0));
		}
		x[k] = ft_atof(input + i);
		while (input[i] && (ft_isdigit(input[i]) || input[i] == '.'))
			i++;
		if (input[i] == ',')
			i++;
		if (!input[i])
		{
			*j = -1;
			ft_putstr_fd("Error\nWrong vector format\n", 2);
			return (vector3(0, 0, 0));
		}
	}
	vec = vector3(x[0], x[1], x[2]);
	return (vec);
}

float	get_float(char *input, int *j)
{
	float	nbf;
	int		i;


	i = go_to_next(input, *j);
	if (!input[i] || (!ft_isdigit(input[i]) && input[i] != '-'))
	{
		ft_putstr_fd("Error\nWrong vector format\n", 2);
		*j = -1;
		return (0.0f);
	}
	nbf = ft_atof(input + i);
	return (nbf);
}

t_vector3	get_color(char *input, int *j)
{
	t_vector3	vec;

	vec = get_vec3(input, j);
	if ((vec.x > 255 || vec.x < 0) || (vec.y > 255 || vec.y < 0) \
	|| (vec.z > 255 || vec.z < 0))
	{
		ft_putstr_fd("Error\nWrong color format\n", 2);
		*j = -1;
		return (vector3(0, 0, 0));
	}
	vec.x = vec.x / 255.0f;
	vec.y = vec.y / 255.0f;
	vec.z = vec.z / 255.0f;
	return (vec);
}

bool	add_sphere(t_scene *scene, char *input)
{
	int	i;

	i = 1;
	if (scene->nb_sphere == 0)
		scene->sphere = malloc(sizeof(t_sphere));
	else
		scene->sphere = ft_realloc(scene->sphere, sizeof(t_sphere)
				* (scene->nb_sphere + 1));
	if (scene->sphere == NULL)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (false);
	}
	scene->sphere[scene->nb_sphere].center = get_vec3(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->sphere[scene->nb_sphere].radius = get_float(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->sphere[scene->nb_sphere].material = return_material();
	scene->sphere[scene->nb_sphere].material.color = get_color(input, &i);
	scene->nb_sphere++;
	if (i == -1)
	{
		ft_putstr_fd("Error\nWrong sphere format\n", 2);
		return (false);
	}
	return (true);
}

bool	add_cylinder(t_scene *scene, char *input)
{
	int	i;

	i = 1;
	if (scene->nb_cylinder == 0)
		scene->cylinder = malloc(sizeof(t_cylinder));
	else
		scene->cylinder = ft_realloc(scene->cylinder, sizeof(t_cylinder)
				* (scene->nb_cylinder + 1));
	if (scene->cylinder == NULL)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (false);
	}
	scene->cylinder[scene->nb_cylinder].center = get_vec3(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->cylinder[scene->nb_cylinder].normal = get_vec3(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->cylinder[scene->nb_cylinder].radius = get_float(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->cylinder[scene->nb_cylinder].height = get_float(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->cylinder[scene->nb_cylinder].material = return_material();
	scene->cylinder[scene->nb_cylinder].material.color = get_color(input, &i);
	scene->nb_cylinder++;
	if (i == -1 || 
	is_normal_vec(scene->cylinder[scene->nb_cylinder - 1].normal) == false)
	{
		ft_putstr_fd("Error\nWrong cylinder format\n", 2);
		return (false);
	}

	return (true);
}

bool	add_plane(t_scene *scene, char *input)
{
	int	i;

	i = 1;
	if (scene->nb_plane == 0)
		scene->plane = malloc(sizeof(t_plane));
	else
		scene->plane = ft_realloc(scene->plane, sizeof(t_plane)
				* (scene->nb_plane + 1));
	if (scene->plane == NULL)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (false);
	}
	scene->plane[scene->nb_plane].point_on_plane = get_vec3(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->plane[scene->nb_plane].normal = get_vec3(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->plane[scene->nb_plane].material = return_material();
	scene->plane[scene->nb_plane].material.color = get_color(input, &i);
	scene->nb_plane++;
	if (i == -1 || 
	is_normal_vec(scene->plane[scene->nb_plane - 1].normal) == false)
	{
		ft_putstr_fd("Error\nWrong plane format\n", 2);
		return (false);
	}
	return (true);
}

bool	add_light(t_scene *scene, char *input)
{
	int	i;

	i = 1;

	if (scene->nb_light == 0)
		scene->light = malloc(sizeof(t_light));
	else
		scene->light = ft_realloc(scene->light, sizeof(t_light)
				* (scene->nb_light + 1));
	if (scene->light == NULL)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (false);
	}
	scene->light[scene->nb_light].position = get_vec3(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->light[scene->nb_light].brightness = get_float(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->light[scene->nb_light].color = get_color(input, &i);
	scene->nb_light++;
	if (i == -1 || 
	is_norm(scene->light[scene->nb_light - 1].brightness) == false)
	{
		ft_putstr_fd("Error\nWrong light format\n", 2);
		return (false);
	}
	return (true);
}

bool	add_camera(t_scene *scene, char *input)
{
	t_matrix4x4	rotation;
	int			i;

	i = 1;
	scene->camera.pos = get_vec3(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->camera.angle = get_vec3(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->camera.fov = get_float(input, &i);
	i++;
	if (i == -1 || is_normal_vec(scene->camera.angle) == false
		|| scene->camera.fov < 0 || scene->camera.fov > 180)
	{
		ft_putstr_fd("Error\nWrong camera format\n", 2);
		return (false);
	}

	scene->camera.angle.y *= 90;
	scene->camera.angle.x *= 180;
	scene->camera.angle.z *= 180;
	scene->camera.pitch = scene->camera.angle.y;
	scene->camera.yaw = scene->camera.angle.x;
	scene->camera.is_clicked = false;
	rotation = mult_mat4x4(rotation_y(to_radian(scene->camera.pitch)),
			rotation_x(to_radian(scene->camera.yaw)));
	rotation = mult_mat4x4(rotation,
			rotation_z(to_radian(scene->camera.angle.z)));
	scene->camera.inv_lookat = rotation;
	scene->nb_camera++;
	return (true);
}

bool	add_ambient(t_scene *scene, char *input)
{
	int	i;

	i = 1;
	scene->ambient.intensity = get_float(input, &i);
	if (i == -1)
		return (false);
	i++;
	scene->ambient.color = get_color(input, &i);
	if (i == -1 || is_norm(scene->ambient.intensity) == false)
	{
		ft_putstr_fd("Error\nWrong ambient format\n", 2);
		return (false);
	}
	scene->ambient.ambient = vector3_multiply_float(scene->ambient.color,
			scene->ambient.intensity);
	scene->nb_ambient++;
	return (true);
}

bool	contain_alphabet(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (false);
	while (input[i] != '\0')
	{
		if (ft_isalpha(input[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	add_input(t_scene *scene, char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0' && input[i] == ' ')
		i++;
	if (contain_alphabet(input + 2 + i))
		return (false);
	if ((input[i] == 'a' || input[i] == 'A') && a_not_finished(input[i])
		&& add_ambient(scene, input + ++i))
		return (true);
	else if (((input[i] == 'c' && input[i + 1] == ' ')
			|| (input[i] == 'C' && input[i + 1] == ' '))
		&& c_not_finished(input[i]) && add_camera(scene, input + ++i))
		return (true);
	else if ((input[i] == 'l' || input[i] == 'L') && l_not_finished(input[i])
		&& add_light(scene, input + ++i))
		return (true);
	else if (((input[i] == 'p' && input[i + 1] == 'l')
			|| (input[i] == 'P' && input[i + 1] == 'L'))
		&& pl_not_finished(input[i]) && add_plane(scene, input + ++i + 1))
		return (true);
	else if (((input[i] == 's' && input[i + 1] == 'p')
			|| (input[i] == 'S' && input[i + 1] == 'P'))
		&& sp_not_finished(input[i]) && add_sphere(scene, input + ++i + 1))
		return (true);
	else if (((input[i] == 'c' && input[i + 1] == 'y')
			|| (input[i] == 'C' && input[i + 1] == 'Y'))
		&& cy_not_finished(input[i]) && add_cylinder(scene, input + ++i + 1))
		return (true);
	return (false);
}*/
