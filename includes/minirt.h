/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:14:01 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/04 17:14:01 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//# include "libft.h"

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <math.h>

# define PI 3.14159265358979323846
# define ERROR 0
# define SUCCESS 1


typedef struct s_vec3d
{
	float x, y, z;
} t_vec3d;

typedef struct s_triangle
{
	t_vec3d p[3];
} t_triangle;

typedef struct s_plane
{
	t_triangle triangle[2];

} t_plane;

typedef struct s_cuboid
{
	t_plane plane[6];
} t_cuboid;

typedef struct s_matrix4x4
{
	float matrix[4][4];
} t_matrix4x4;

typedef struct s_sphere
{
    t_vec3d center;
    double radius;
} t_sphere;

typedef struct s_world
{
	t_vec3d		coord_world;
	t_vec3d 	angle_world;
	t_matrix4x4	rotation_world;
}	t_world;


typedef struct s_camera
{
    t_vec3d pos;      // position de la caméra
    t_vec3d angle;   // point visé par la caméra
    float fov;
	t_matrix4x4 view_matrix;
}	t_camera;


typedef struct s_minirt
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int32_t		width;
	int32_t		height;
	t_world		world;
	t_camera	camera;
}	t_minirt;

extern t_minirt g_minirt;

float to_radian(float angle);
t_vec3d multiplymatrixvector(t_vec3d i, t_matrix4x4 m);
t_matrix4x4 mult_mat4x4(t_matrix4x4 mat1, t_matrix4x4 mat2);
t_vec3d vec3d_cross(t_vec3d v1, t_vec3d v2);
t_vec3d vec3d_normalize(t_vec3d v);
float vec3d_magnitude(t_vec3d v);
t_vec3d vec3d_sub(t_vec3d v1, t_vec3d v2);


t_plane add_plane(t_vec3d pos, t_vec3d angle, t_vec3d scale);
t_vec3d add_point(float x, float y, float z);
t_vec3d add_center(float x, float y, float z);
t_triangle add_triangle(t_vec3d pos);
t_vec3d add_angle(float x, float y, float z);
t_matrix4x4 createperspectivematrix(float fov, float aspect, float near, float far);

void keyhook(mlx_key_data_t keydata, void *param);

void draw_line(int x1, int y1, int x2, int y2);
void draw_triangle(t_triangle triangle);
void draw_sphere(t_sphere sphere, int nbLong, int nbLat);

t_matrix4x4 init_mat_0(void);
#endif
