/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:14:01 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/14 15:39:05 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINIRT_H
# define MINIRT_H

//# include "libft.h"

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
#include <time.h>
#include <sys/time.h>
#include <float.h>

# define PI 3.14159265358979323846
# define ERROR 0
# define SUCCESS 1
# define WIDTH  150
# define HEIGHT 150

# define CHECKER_PATTERN 1

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

typedef struct s_material
{
	t_vector3 emission_color;
	t_vector3 color;
	t_vector3 specular_color;
	float emission_strength;
	t_vector3 emission;
	float smoothness;
	float specular_probability;
	int flag;
} t_material;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct s_triangle
{
	t_vector3 p[3];
	t_material material;
} t_triangle;

typedef struct s_cone
{
	t_vector3 center;
	t_vector3 normal;
	t_vector3 color;
	float height;
	float radius;
	t_material material;
} t_cone;

typedef struct hyperboloid
{
	t_vector3 center;
	t_vector3 normal;
	t_vector3 color;
	float height;
	float radius;
	t_material material;
} t_hyperboloid;

typedef struct paraboloid
{
	t_vector3 center;
	t_vector3 normal;
	t_vector3 color;
	float height;
	float radius;
	t_material material;
} t_paraboloid;

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

typedef struct s_circle
{
	t_vector3 center;
	t_vector3 normal;
	t_vector3 color;
	float radius;
	t_material material;
} t_circle;


typedef struct s_cylinder
{
    t_vector3 center;
	t_vector3 normal;
	t_vector3 color;
	float height;
	float radius;
	t_circle circle_top;
	t_circle circle_bottom;
	t_material material;
} t_cylinder;

typedef struct s_plane
{
	t_vector3 point_on_plane;
	t_vector3 normal;
	t_vector3 color;
	t_material material;
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
	t_vector4 ambient;
} t_ambient;

typedef struct s_sphere
{
    t_vector3 center;
	t_vector3 color;
    double radius;
	t_material material;
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
	int	material_index;
	int index;
} t_obj;




typedef struct s_camera_eye
{
	t_vector3 pos;
	t_vector3 *ray_dir;
	t_vector3 angle;
	float fov;
	bool is_clicked;
	t_vector3 forward;
	t_matrix4x4 inv_perspective;
	t_matrix4x4 inv_lookat;
	float pitch;
	float yaw;
}	t_camera_eye;


typedef struct s_ray
{
	t_vector3 origin;
	t_vector3 direction;
} t_ray;



typedef struct s_info
{
	t_vector3 hit_point;
	t_vector3 normal;
	t_material material;
	float hit_distance;
} t_info;

typedef struct s_scene
{
	t_sphere sphere[100];
	t_plane plane[100];
	t_cylinder cylinder[100];
	t_cone cone[100];
	t_hyperboloid hyperboloid[100];
	t_paraboloid paraboloid[100];
	t_triangle triangle[100];
	t_circle circle[100];
	//t_cuboid *cuboid;
	t_light light[100];
	t_ambient ambient;
	t_obj obj;
	int nb_light;
	int nb_sphere;
	int nb_plane;
	int nb_triangle;
	int nb_cylinder;
	int nb_circle;
	int nb_cone;
	int nb_hyperboloid;
	int nb_paraboloid;
	//int nb_cuboid;
	int nb_obj;
	t_material material[20];
	//t_light *light;

}	t_scene;

typedef struct s_hitpayload
{
	float HitDistance;
	t_vector3 WorldPosition;
	t_vector3 WorldNormal;

	int ObjectIndex;
} t_hitpayload;

typedef struct s_model
{
	t_sphere sphere;
	t_plane *planes;
	t_triangle *triangles;
	//t_cuboid cuboid;
	t_obj *obj;
	int nb_obj;
}	t_model;

typedef struct s_minirt
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	int32_t			width;
	int32_t			height;
	t_camera_eye	camera;
	t_input_list	*input_head;
	bool				error;
	bool				moved;
	bool			resized;
	int				input_validity;
	float x;
	float y;
	float z;
	float radius;
	t_model			model;
	t_scene			scene;
}	t_minirt;

void close_function(void *param);
float to_radian(float angle);
float to_degree(float angle);
t_vector3 multiplymatrixvector(t_vector3 i, t_matrix4x4 m);
t_vector4 multiplymatrixvector4(t_vector4 i, t_matrix4x4 m);
t_matrix4x4 mult_mat4x4(t_matrix4x4 mat1, t_matrix4x4 mat2);

t_vector3 vector3_cross(t_vector3 v1, t_vector3 v2);
float vector3_dot(t_vector3 vec1, t_vector3 vector2);
t_vector3 vector3_normalize(t_vector3 v);
float vector3_length(t_vector3 v);


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
t_vector3 vector3_reflect(t_vector3 a, t_vector3 n);
t_vector3	vector3_clamp(t_vector3 color, float min, float max);
t_vector4 vector4_multiply_float(t_vector4 a, float b);
t_vector4 vector4_add(t_vector4 a, t_vector4 b);

t_vector3 vector3_random(float x, float y);
float	random_float(void);
float randomvalue(uint state);
t_vector3 random_direction(uint state);

void calculateraydirections(t_minirt *minirt);
void calculateview(t_minirt *minirt);
void calculateprojection(t_minirt *minirt);

t_plane add_plane(t_vector3 pos, t_vector3 pos2, t_vector3 pos3, t_vector3 pos4);
t_vector3 add_point(float x, float y, float z);
t_vector3 add_center(float x, float y, float z);
t_triangle add_triangle(t_vector3 pos, t_vector3 pos1, t_vector3 pos2);
t_sphere add_sphere(t_vector3 pos, float radius, t_vector3 color);
t_material add_material(t_vector3 color, float roughness, float mettalic);


void keyhook(mlx_key_data_t keydata, void *param);
void mousehook(mouse_key_t button, action_t action, modifier_key_t mods, void *param);

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

t_vector3 Perpixel(t_ray ray, const t_scene *scene, uint rng_seed);
t_vector3 perpixel(t_ray ray, const t_scene *scene, uint rng_seed);


void hook(void *param);
void	resize(int32_t width, int32_t height, void *param);
void	cursor(double xpos, double ypos, void *param);
t_model get_model(void);
int	get_rgba(t_vector3 color);


t_vector3 create_ray(float x, float y, t_minirt *minirt);

t_info	sphere_collision(t_ray ray, t_sphere sphere);
t_info	plane_collision(t_ray ray, t_plane plane);
t_info circle_collision(t_ray ray, t_circle cirle);
t_info	cylinder_collision(t_ray ray, t_cylinder cylinder);
t_info triangle_collision(t_ray ray, t_triangle triangle);

t_info paraboloid_collision(t_ray ray, t_paraboloid paraboloid);
t_info hyperboloid_collision(t_ray ray, t_hyperboloid hyperboloid);
t_info cone_collision(t_ray ray, t_cone cone);

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



#endif


