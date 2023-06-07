/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:14:01 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/07 07:39:57 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINIRT_H
# define MINIRT_H

//# include "libft.h"

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/includes/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
#include <time.h>

# define PI 3.14159265358979323846
# define ERROR 0
# define SUCCESS 1
# define WIDTH  500
# define HEIGHT 500



typedef struct s_vec2d
{
	float x, y;
} t_vector2;
typedef struct s_vec3d
{
	float x, y, z;
} t_vector3;

typedef struct s_vec4d
{
	float x, y, z, w;
} t_vector4;


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
	t_vector3 plane[4];
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

typedef struct s_obj
{
	t_vector3 *vertex;
	t_vector3 *normal;
	int index;
} t_obj;


typedef struct s_camera_eye
{
	t_vector3 pos;
	t_vector3 *ray_dir;
	t_vector3 angle;
	float fov;
	t_vector3 forward;
	t_matrix4x4 inv_perspective;
	t_matrix4x4 inv_lookat;
}	t_camera_eye;

typedef struct s_cuboid
{
	t_plane plane[6];
} t_cuboid;


typedef struct s_ray
{
	t_vector3 origin;
	t_vector3 direction;
} t_ray;

typedef struct s_scene
{
	t_sphere *sphere;
	t_plane planes[100];
	//t_cone *cones;
	t_triangle triangles[100];
	t_cuboid *cuboid;
	t_obj *obj;
	int nb_sphere;
	int nb_plane;
	int nb_triangle;
	int nb_cuboid;
	int nb_obj;
	//t_light *light;

}	t_scene;

typedef struct s_model
{
	t_sphere sphere;
	t_plane *planes;
	t_triangle *triangles;
	t_cuboid cuboid;
	t_obj *obj;
	int nb_obj;
}	t_model;

typedef struct s_minirt
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int32_t		width;
	int32_t		height;
	t_camera_eye	camera;
	t_input_list *input_head;
	int			error;
	int			moved;
	int			input_validity;
	t_model		model;
	t_scene		scene;
}	t_minirt;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float to_radian(float angle);
void keyhook(mlx_key_data_t keydata, void *param);
void	hook(void *param);


/*~~~~~~~~~~~~~~~~~~input stuff~~~~~~~~~~~~~~~~~~~~~~~*/
void print_input(t_minirt *minirt);

int vector3_checker(t_vector3 vector3, float range_min, float range_max);
int check_file(char *file_name);
int is_non_valid_character(char a);
int	is_all_space(char *input);
float ft_atof(const char* str);
void	free_split(char **split);
int split_size(char **split);
t_vector3 get_vector3(const char *line, int i, t_input_list *input);
int	jump_spaces(const char *line, int i);
int	jump_non_spaces(const char *line, int i);
int evaluator(t_input_list *input, int i);
int get_to_next_param(const char *line, int i, t_input_list *input);
int has_invalid_input(t_input_list *input);
void check_esentials(t_minirt *minirt);
t_input_list *get_first_valid_node(t_input_list *lst);
void	final_prepare_input(t_minirt *minirt);
void validate_input(t_minirt *minirt);
char *remove_new_line(char *line);
char *get_name(const char *line);
void	*get_object(t_input_list *input, const char *line);
void get_input_list(t_minirt *minirt, int fd);

int validate_line_cylinder(const char *line);
t_cylinder *init_cylinder(const char *line, t_input_list *input);
void validate_values_cylinder(t_input_list *input);

int validate_line_plane(const char *line);
t_plane *init_plane(const char *line, t_input_list *input);
void validate_values_plane(t_input_list *input);

int validate_line_sphere(const char *line);
t_sphere *init_sphere(const char *line, t_input_list *input);
void validate_values_sphere(t_input_list *input);

int validate_line_camera(const char *line);
t_camera *init_camera(const char *line, t_input_list *input);
void validate_values_camera(t_input_list *input);

int validate_line_ambient(const char *line);
t_ambient *init_ambient(const char *line, t_input_list *input);
void validate_values_ambient(t_input_list *input);

int validate_line_light(const char *line);
t_light *init_light(const char *line, t_input_list *input);
void validate_values_light(t_input_list *input);
/*~~~~~~~~~~~~~~~~~~input stuff~~~~~~~~~~~~~~~~~~~~~~~*/




void close_function(void *param);
float to_radian(float angle);
float to_degree(float angle);
t_vector3 multiplymatrixvector(t_vector3 i, t_matrix4x4 m);
t_matrix4x4 mult_mat4x4(t_matrix4x4 mat1, t_matrix4x4 mat2);

t_vector3 vector3_cross(t_vector3 v1, t_vector3 v2);
float dot_product(t_vector3 v1, t_vector3 v2);
t_vector3 vector3_normalize(t_vector3 v);
float vec3d_magnitude(t_vector3 v);


t_vector2 vector2(float x, float y);
t_vector3 vector3(float x, float y, float z);
t_vector4 vector4(float x, float y, float z, float w);

t_vector2 vector2_subtract(t_vector2 v1, t_vector2 v2);
t_vector2 vector2_add(t_vector2 a, t_vector2 b);
t_vector2 vector2_multiply(t_vector2 a, t_vector2 b);
t_vector2 vector2_multiply_float(t_vector2 a, float b);

t_vector3 vector3_subtract(t_vector3 v1, t_vector3 v2);
t_vector3 vector3_add(t_vector3 a, t_vector3 b);
t_vector3 vector3_multiply(t_vector3 a, t_vector3 b);
t_vector3 vector3_multiply_float(t_vector3 a, float b);
t_vector3 vector3_add_float(t_vector3 a, float b);


void calculateraydirections(t_minirt *minirt);
void calculateview(t_minirt *minirt);
void calculateprojection(t_minirt *minirt);

t_plane add_plane(t_vector3 pos, t_vector3 pos2, t_vector3 pos3, t_vector3 pos4);
t_vector3 add_point(float x, float y, float z);
t_vector3 add_center(float x, float y, float z);
t_triangle add_triangle(t_vector3 pos, t_vector3 pos1, t_vector3 pos2);
t_sphere add_sphere(t_vector3 pos, float radius, t_vector3 color);

void keyhook(mlx_key_data_t keydata, void *param);

void draw_line(int x1, int y1, int x2, int y2);
void draw_triangle(t_triangle triangle);
void draw_sphere(t_sphere sphere, int nbLong, int nbLat);

t_matrix4x4 init_mat_0(void);
t_matrix4x4 rotation_x(float angle);
t_matrix4x4 rotation_y(float angle);
t_matrix4x4 rotation_z(float angle);
t_matrix4x4 translation(t_vector3 vec);
t_matrix4x4 scale(t_vector3 vec);

void calculatelookat(t_minirt *minirt);
t_matrix4x4 lookat(t_vector3 eye, t_vector3 target, t_vector3 up);
t_matrix4x4 inverse_lookat_matrix(t_vector3 eye, t_vector3 target, t_vector3 up);
t_matrix4x4 projection_transform(float fov, float aspect, float near, float far);
t_matrix4x4 createperspectivematrix(float fov, float aspect, float near, float far);
t_matrix4x4 inverse_perspective_matrix(float fov, float aspect, float near, float far);

t_matrix4x4 FPSViewRH( t_vector3 eye, float pitch, float yaw );

float	max(float a, float b);
float mult(float a, float b, float c);
void print_mat(t_matrix4x4 mat);
t_matrix4x4 matrixInverse(t_matrix4x4 matrix, int size);

t_vector4 renderer(t_vector2 coord, t_minirt *minirt);

void hook(void *param);
void	resize(int32_t width, int32_t height, void *param);
void	cursor(double xpos, double ypos, void *param);
t_model get_model(void);
int	get_rgba(t_vector4 color);
#endif


