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

void	get_camera(t_minirt *minirt, t_camera camera)
{
	t_matrix4x4	rotation;

	minirt->camera.fov = camera.fov;
	minirt->camera.pos = camera.position;
	minirt->camera.angle = camera.orientation;
	minirt->camera.angle.y *= 90;
	minirt->camera.angle.x *= 180;
	minirt->camera.angle.z *= 180;
	minirt->camera.pitch = minirt->camera.angle.y;
	minirt->camera.yaw = minirt->camera.angle.x;
	minirt->camera.is_clicked = false;
	minirt->scene.nb_camera++;
	rotation = mult_mat4x4(rotation_y(to_radian(minirt->camera.pitch)),
			rotation_x(to_radian(minirt->camera.yaw)));
	rotation = mult_mat4x4(rotation,
			rotation_z(to_radian(minirt->camera.angle.z)));
	minirt->camera.inv_lookat = rotation;
	minirt->scene.camera = minirt->camera;
}

void	get_ambient(t_minirt *minirt, t_ambient ambient)
{
	minirt->scene.ambient = ambient;
	ambient.color = vector3_multiply_float(ambient.color, 1 / 255.0f);
	minirt->scene.ambient.ambient = vector3_multiply_float(ambient.color,
			ambient.intensity);
	minirt->scene.nb_ambient = 1;
}

void	get_light(t_minirt *minirt, t_light light)
{
	int	i;

	if (minirt->scene.nb_light == 0)
		minirt->scene.light = malloc(sizeof(t_light));
	else
		minirt->scene.light = ft_realloc(minirt->scene.light, sizeof(t_light)
				* (minirt->scene.nb_light + 1));
	if (!minirt->scene.light)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		minirt->error = 1;
		return ;
	}
	i = minirt->scene.nb_light++;
	minirt->scene.light[i] = light;
	minirt->scene.light[i].color = vector3_multiply_float(
			light.color, 1 / 255.0f);
}

void	get_sphere(t_minirt *minirt, t_sphere sphere)
{
	int	i;

	if (minirt->scene.nb_sphere == 0)
		minirt->scene.sphere = malloc(sizeof(t_sphere));
	else
		minirt->scene.sphere = ft_realloc(minirt->scene.sphere,
				sizeof(t_sphere) * (minirt->scene.nb_sphere + 1));
	if (!minirt->scene.sphere)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		minirt->error = 1;
		return ;
	}
	i = minirt->scene.nb_sphere++;
	minirt->scene.sphere[i] = sphere;
	minirt->scene.sphere[i].material.color = vector3_multiply_float(
			sphere.color, 1 / 255.0f);
}

t_material	return_material(void)
{
	t_material	material;

	material.emission_color = vector3(1.0f, 1.0f, 1.0f);
	material.color = vector3(1.0f, 0.0f, 0.0f);
	material.specular_color = vector3(1, 1, 1);
	material.emission_strength = 0.0f;
	material.emission = vector3_multiply_float(material.emission_color, \
		material.emission_strength);
	material.smoothness = 1.0f;
	material.specular_probability = 0.0f;
	material.flag = 0;
	return (material);
}
