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

# define WIDTH 1000
# define HEIGHT 500

# define PI 3.14159265358979323846
# define ERROR 0
# define SUCCESS 1
typedef struct inverse
{
	float a;
	float p;
	float q;
	float r;
	float s;
	float t;
	float u;
	float v;
	float w;
	float x;
	float y;
	float z;
} t_inverse;

typedef struct s_vec2
{
	float x, y;
} t_vec2;


typedef struct s_vec3d
{
	float x, y, z;
} t_vec3;

typedef struct s_vec4d
{
	float x, y, z, w;
} t_vec4;

typedef struct s_triangle
{
	t_vec3 p[3];
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
    t_vec3 center;
    double radius;
} t_sphere;

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
} t_ray;

typedef struct s_camera
{
	t_vec3 pos;
	t_vec3 *ray_dir;
	t_vec3 angle;
	float fov;
	t_vec3 forward;
	t_matrix4x4 inv_perspective;
	t_matrix4x4 inv_lookat;
}	t_camera;


typedef struct s_minirt
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int32_t		width;
	int32_t		height;
	t_camera	camera;
	int			error;
	int			moved;
}	t_minirt;


float to_radian(float angle);
float to_degree(float angle);
t_vec3 multiplymatrixvector(t_vec3 i, t_matrix4x4 m);
t_matrix4x4 mult_mat4x4(t_matrix4x4 mat1, t_matrix4x4 mat2);

t_vec3 vec3_cross(t_vec3 v1, t_vec3 v2);
float dot_product(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_normalize(t_vec3 v);
float vec3d_magnitude(t_vec3 v);

t_vec3 vec3(float x, float y, float z);
t_vec2 vec2(float x, float y);
t_vec4 vec4(float x, float y, float z, float w);

t_vec2 vec2_sub(t_vec2 v1, t_vec2 v2);
t_vec2 vec2_add(t_vec2 a, t_vec2 b);
t_vec2 vec2_mult(t_vec2 a, t_vec2 b);
t_vec2 vec2_multf(t_vec2 a, float b);

t_vec3 vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_mult(t_vec3 a, t_vec3 b);
t_vec3 vec3_multf(t_vec3 a, float b);
t_vec3 vec3_addf(t_vec3 a, float b);


void calculateraydirections(t_minirt *minirt);
void calculateview(t_minirt *minirt);
void calculateprojection(t_minirt *minirt);

t_plane add_plane(t_vec3 pos, t_vec3 angle, t_vec3 scale);
t_vec3 add_point(float x, float y, float z);
t_vec3 add_center(float x, float y, float z);
t_triangle add_triangle(t_vec3 pos, t_vec3 pos1, t_vec3 pos2);
t_vec3 add_angle(float x, float y, float z);

void keyhook(mlx_key_data_t keydata, void *param);

void draw_line(int x1, int y1, int x2, int y2);
void draw_triangle(t_triangle triangle);
void draw_sphere(t_sphere sphere, int nbLong, int nbLat);

t_matrix4x4 init_mat_0(void);
t_matrix4x4 rotation_x(float angle);
t_matrix4x4 rotation_y(float angle);
t_matrix4x4 rotation_z(float angle);
t_matrix4x4 translation(t_vec3 vec);
t_matrix4x4 scale(t_vec3 vec);


t_matrix4x4 lookat(t_vec3 eye, t_vec3 target, t_vec3 up);
t_matrix4x4 inverse_lookat_matrix(t_vec3 eye, t_vec3 target, t_vec3 up);
t_matrix4x4 projection_transform(float fov, float aspect, float near, float far);
t_matrix4x4 createperspectivematrix(float fov, float aspect, float near, float far);
t_matrix4x4 inverse_perspective_matrix(float fov, float aspect, float near, float far);

t_matrix4x4 FPSViewRH( t_vec3 eye, float pitch, float yaw );

float	max(float a, float b);
float mult(float a, float b, float c);
void print_mat(t_matrix4x4 mat);
t_matrix4x4 matrixInverse(t_matrix4x4 matrix, int size);



#endif
