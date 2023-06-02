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

# ifndef MINIRT_H
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
# define WIDTH 975
# define HEIGHT 975



typedef struct s_vec2d
{
	float x, y;
} t_vector2;
typedef struct s_vec3d
{
	float x, y, z;
} t_vector3;
typedef	struct s_vec4d
{
	float r, g, b, a;
}	t_vector4;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct s_triangle
{
	t_vector3 p[3];
} t_triangle;

typedef struct s_matrix4x4
{
	float matrix[4][4];
} t_matrix4x4;
typedef struct s_world
{
	t_vector3		coord_world;
	t_vector3 	angle_world;
	t_matrix4x4	rotation_world;
}	t_world;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct s_cylinder
{
    t_vector3 centre;
	t_vector3 normal_axis;
	t_vector3 color;
	float height;
	float diameter;
} t_cylinder;

typedef struct s_plane
{
    t_vector3 point_on_plane;
	t_vector3 normal;
	t_vector3 color;
} t_plane;
typedef struct s_light
{
    t_vector3 position;
    t_vector3 color;
	float brightness;
} t_light;

typedef struct s_ambient
{
    t_vector3 color;
    float intensity;
} t_ambient;
typedef struct s_sphere
{
    t_vector3 center;
	t_vector3 color;
    double radius;
} t_sphere;

typedef struct s_camera
{
    t_vector3 position;
    t_vector3 orientation;
    float fov;
}	t_camera;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct s_input_list
{
	char *name;
	void *object;
	struct s_input_list *next;
}	t_input_list;
typedef struct s_minirt
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int32_t		width;
	int32_t		height;
	t_input_list *input_head;
	int			input_validity;
}	t_minirt;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float to_radian(float angle);
void keyhook(mlx_key_data_t keydata, void *param);
void	hook(void *param);
int	get_rgba(int r, int g, int b, int a);
#endif
