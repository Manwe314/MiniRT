/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:16:05 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/04 17:16:05 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_minirt g_minirt;

static int	init_minirt(void)
{
	int i;
	int j;

	g_minirt.width = 256;
	g_minirt.height = 256;

	g_minirt.world.coord_world.x = 0.0f;
	g_minirt.world.coord_world.y = 1.0f;
	g_minirt.world.coord_world.z = 0.0f;

	g_minirt.world.angle_world.x = 0.0f;
	g_minirt.world.angle_world.y = 0.0f;
	g_minirt.world.angle_world.z = 0.0f;

	//g_minirt.camera.view_matrix.matrix = { {0, 0, 0}, {0, 0, -1}, {0, 1, 0}, 90.0f };
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			g_minirt.world.rotation_world.matrix[i][j] = 0.0f;
			g_minirt.camera.view_matrix.matrix[i][j] = 0.0f;
	}
	g_minirt.camera.view_matrix.matrix[1][2] = -1.0f;
	g_minirt.camera.view_matrix.matrix[2][1] = 1.0f;

	// Init mlx with a canvas size of 256x256 and the ability to resize the window.
	g_minirt.mlx = mlx_init(g_minirt.width ,g_minirt.height, "minirt", true);

	if (!g_minirt.mlx)
		exit(ERROR);
	g_minirt.img = mlx_new_image(g_minirt.mlx, 256, 256);
	mlx_image_to_window(g_minirt.mlx, g_minirt.img, 0, 0);

	// Run the main loop and terminate on quit.
	return (SUCCESS);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void create_icosahedron(t_triangle *triangles)
{
    // points for icosahedron, coordinates are rescaled to fit in unit sphere
    t_vec3d points[12] = {
        (t_vec3d){ -0.525731f, 0.0f, 0.850651f },
        (t_vec3d){ 0.525731f, 0.0f, 0.850651f },
        (t_vec3d){ -0.525731f, 0.0f, -0.850651f },
        (t_vec3d){ 0.525731f, 0.0f, -0.850651f },
        (t_vec3d){ 0.0f, 0.850651f, 0.525731f },
        (t_vec3d){ 0.0f, 0.850651f, -0.525731f },
        (t_vec3d){ 0.0f, -0.850651f, 0.525731f },
        (t_vec3d){ 0.0f, -0.850651f, -0.525731f },
        (t_vec3d){ 0.850651f, 0.525731f, 0.0f },
        (t_vec3d){ -0.850651f, 0.525731f, 0.0f },
        (t_vec3d){ 0.850651f, -0.525731f, 0.0f },
        (t_vec3d){ -0.850651f, -0.525731f, 0.0f }
    };

    // indices for icosahedron triangles
    int indices[20][3] = {
        { 0, 4, 1 }, { 0, 9, 4 }, { 9, 5, 4 }, { 4, 5, 8 }, { 4, 8, 1 },
        { 8, 10, 1 }, { 8, 3, 10 }, { 5, 3, 8 }, { 5, 2, 3 }, { 2, 7, 3 },
        { 7, 10, 3 }, { 7, 6, 10 }, { 7, 11, 6 }, { 11, 0, 6 }, { 0, 1, 6 },
        { 6, 1, 10 }, { 9, 0, 11 }, { 9, 11, 2 }, { 9, 2, 5 }, { 7, 2, 11 }
    };

    // create triangles
    for (int i = 0; i < 20; i++)
    {
        t_triangle triangle;
        for (int j = 0; j < 3; j++)
        {
            triangle.p[j] = points[indices[i][j]];
        }
        triangles[i] = triangle;
    }
}

void	resize(int32_t width, int32_t height, void *param)
{
	(void) param;
	mlx_delete_image( g_minirt.mlx,  g_minirt.img);
	 g_minirt.img = mlx_new_image( g_minirt.mlx, width, height);
	if (! g_minirt.img)
		exit(EXIT_FAILURE);
	g_minirt.width = width;
	g_minirt.height = height;
	mlx_image_to_window( g_minirt.mlx,  g_minirt.img, 0, 0);
}

t_triangle init_triangle()
{
	t_triangle triangle;

	// static float x = 0.0f;

	// x += 0.01f;
	// if (x > 5)
	// 	x = 0.001f;
	triangle.p[0] = (t_vec3d){0 + g_minirt.world.coord_world.x, 0.25 + g_minirt.world.coord_world.y, 0 + g_minirt.world.coord_world.z};
	triangle.p[1] = (t_vec3d){0 + g_minirt.world.coord_world.x, 0 + g_minirt.world.coord_world.y, 0 + g_minirt.world.coord_world.z};
	triangle.p[2] = (t_vec3d){0.25 + g_minirt.world.coord_world.x, 0.25 + g_minirt.world.coord_world.y, 0 + g_minirt.world.coord_world.z};
	return (triangle);
}

t_sphere init_sphere()
{
	t_sphere sphere;

	sphere.center = (t_vec3d){0, 0, 1};
	sphere.radius = 0.5f;

	return (sphere);
}

void	hook(void *param)
{
	(void)param;
	t_matrix4x4 matrix;
	// Draw a line from (0, 0) to (256, 256)
	int i = -1;
	int j;

	while (++i < g_minirt.width)
	{
		j = -1;
		while (++j < g_minirt.height)
		{
			mlx_put_pixel(g_minirt.img, i, j, get_rgba(255, 255, 255, 255));
		}
	}
	//memset(g_minirt.img->pixels, 255, g_minirt.img->width * g_minirt.img->height * sizeof(int32_t));
	//draw_sphere(init_sphere(), 5, 5);

	t_plane plane = add_plane(add_center(1, 0, 0), add_angle(90,0,0), add_point(0.5,0.5,0) );
	draw_triangle(plane.triangle[0]);
	draw_triangle(plane.triangle[1]);
}



int main()
{
	if (init_minirt() == ERROR)
		return (ERROR);
	t_triangle triangle = init_triangle();
	mlx_resize_hook(g_minirt.mlx, &resize, 0);
	mlx_loop_hook(g_minirt.mlx, &hook, 0);
	mlx_key_hook(g_minirt.mlx, &keyhook, 0);

	mlx_loop(g_minirt.mlx);
	mlx_terminate(g_minirt.mlx);
	system("leaks minirt");
	return (SUCCESS);
}
