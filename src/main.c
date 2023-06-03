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
#include "../lib/libft/includes/libft.h"

static int	init_minirt(t_minirt *minirt)
{
	minirt->width = WIDTH;
	minirt->height = HEIGHT;
	// Init mlx with a canvas size of 256x256 and the ability to resize the window.
	minirt->mlx = mlx_init(minirt->width , minirt->height, "minirt", true);

	if (!minirt->mlx)
		exit(ERROR);
	minirt->img = mlx_new_image(minirt->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);

	// Run the main loop and terminate on quit.
	return (SUCCESS);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	dot(t_vector3 a, t_vector3 b)
{
	float product;

	product = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (product);
}

t_vector3 add_vector3(t_vector3 a, t_vector3 b)
{
	t_vector3 sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}

t_vector3 subtract_vector3(t_vector3 a, t_vector3 b)
{
	t_vector3 subtraction;

	subtraction.x = a.x - b.x;
	subtraction.y = a.y - b.y;
	subtraction.z = a.z - b.z;
	return (subtraction);
}

float min(float a, float b)
{
	if (a > b)
		return b;
	else
		return a;
}

float max(float a, float b)
{
	if (a < b)
		return b;
	else
		return a;
}

t_vector3 multiply_vector_scalar(t_vector3 a, float b)
{
	t_vector3 product;

	product.x = a.x * b;
	product.y = a.y * b;
	product.z = a.z * b;
	return product;
}

t_vector3 normalize(t_vector3 a)
{
	float length;
	t_vector3 normal;

	length = (float)sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
	normal.x = a.x / length;
	normal.y = a.y / length;
	normal.z = a.z / length;
	return (normal);
}

void	hook(void *param)
{
	t_minirt *minirt;
	int x;
	int y;
	t_vector3 ray_direction;
	t_vector3 ray_origin;
	float a, b, c;
	float discriminant;
	t_vector2 coordinate;
	t_sphere *sphere;
	t_vector2	hit_distance;
	t_vector3	hit_position;
	t_vector3	normal;
	t_vector3 	light_direction;
	float intensity;

	minirt = param;
	sphere = minirt->input_head->object;
	x = 0;
	ray_origin.x = 0;
	ray_origin.y = 0;
	ray_origin.z = -100;
	light_direction.x = 1;
	light_direction.y = 1;
	light_direction.z = 1;
	light_direction = normalize(light_direction);
	while (x < minirt->width)
	{
		y = 0;
		while (y < minirt->height)
		{
			coordinate.x = (float)x / (float)minirt->width;
			coordinate.y = (float)y / (float)minirt->height;
			coordinate.x = (coordinate.x * 2.0f) - 1.0f;
			coordinate.y = (coordinate.y * 2.0f) - 1.0f;
			ray_direction.x = coordinate.x;
			ray_direction.y = coordinate.y;
			ray_direction.z = 1;

			a = dot(ray_direction, ray_direction);
			b = 2 * dot(ray_origin, ray_direction);
			c = dot(ray_origin, ray_origin) - (sphere->radius * sphere->radius);

			discriminant = (b * b) - (4 * a * c);
			if (discriminant >= 0)
			{
				hit_distance.x = (-b - sqrt(discriminant)) / (2.0f * a);
				hit_position = multiply_vector_scalar(ray_direction, hit_distance.x);
				hit_position = add_vector3(ray_origin, hit_position);
				//printf("%f | %f | %f\n", hit_position.x, hit_position.y, hit_position.z);
				normal = subtract_vector3(hit_position, sphere->center);
				normal = normalize(normal);
				intensity = max(dot(normal, multiply_vector_scalar(light_direction, -1)), 0.0f);
				mlx_put_pixel(minirt->img, x, y, get_rgba((int)(3 * intensity),(int)(252 * intensity),(int)(252 * intensity), 255));
			}
			else
				mlx_put_pixel(minirt->img, x, y, get_rgba(189, 195, 199, 255));
			//printf("x: %d\ny: %d\n", x, y);
			y++;
		}
		x++;
	}

}

void close_function(void *param)
{
	t_minirt *minirt;

	minirt = param;

	mlx_delete_image(minirt->mlx, minirt->img);
	free(minirt->input_head->name);
	free(minirt->input_head->object);
}

void keyhook(mlx_key_data_t keydata, void *param)
{
	t_minirt *minirt;

	minirt = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_hook(minirt->mlx, &close_function, minirt);
		mlx_close_window(minirt->mlx);
	}

}

float to_radian(float angle)
{
	return (angle * (M_PI / 180));
}

int	is_all_space(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == ' ' || input[i] == '	')
			j++;
		i++;
	}
	if (i == j)
		return (1);
	return (0);
}

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

char *get_name(const char *line)
{
	int i;
	char *name;

	i = 0;
	name = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (line[i] == 'A' && line[i + 1] == ' ')
		name = ft_strdup("Ambient");
	if (line[i] == 'C' && line[i + 1] == ' ')
		name = ft_strdup("Camera");
	if (line[i] == 'L' && line[i + 1] == ' ')
		name = ft_strdup("Light");
	if (line[i + 1] == '\0' && name == 0)
		return (0);
	if (line[i] == 's' && line[i + 1] == 'p' && line[i + 2] == ' ')
		name = ft_strdup("Sphere");
	if (line[i] == 'p' && line[i + 1] == 'l' && line[i + 2] == ' ')
		name = ft_strdup("Plane");
	if (line[i] == 'c' && line[i + 1] == 'y' && line[i + 2] == ' ')
		name = ft_strdup("Cylinder");
	return (name);
}

int	jump_spaces(const char *line, int i)
{
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (-1);
	return (i);
}

int	jump_non_spaces(const char *line, int i)
{
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (-1);
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}

int split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		i++;
	return (i);
}

t_vector3 get_vector3(const char *line, int i, t_input_list *input)
{
	char **values;
	char *param;
	int j;
	t_vector3 output;

	j = i;

	while (line[j] != ' ' && line[j] != '\0')
		j++;
	param = ft_substr(line, i, j - i);
	values = ft_split(param, ',');
	if (split_size(values) != 3)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
	else
	{
		output.x = ft_atof(values[0]);
		output.y = ft_atof(values[1]);
		output.z = ft_atof(values[2]);
	}
	free_split(values);
	free(param);
	return (output);
}

int evaluator(t_input_list *input, int i)
{
	if (i < 0)
	{
		free(input->name);
		input->name = ft_strdup("inv");
		return (1);
	}
	else
		return (0);
}

int get_to_next_param(const char *line, int i, t_input_list *input)
{
	if (i == 0)
	{
		i = jump_spaces(line, i);
		if (evaluator(input, i) == 1)
			return (-1);
	}
	i = jump_non_spaces(line, i);
	if (evaluator(input, i) == 1)
		return (-1);
	i = jump_spaces(line, i);
	if (evaluator(input, i) == 1)
		return (-1);
	return (i);
}

t_ambient *init_ambient(const char *line, t_input_list *input)
{
	t_ambient *obj;
	int i;

	obj = (t_ambient *)malloc(sizeof(t_ambient));
	i = get_to_next_param(line, 0, input);
	if (i < 0)
		return (obj);
	obj->intensity = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->color = get_vector3(line, i, input);
	return (obj);
}

t_camera *init_camera(const char *line, t_input_list *input)
{
	t_camera	*obj;
	int i;

	obj = (t_camera *)malloc(sizeof(t_camera));
	i = get_to_next_param(line, 0, input);
	if (i < 0)
		return (obj);
	obj->position = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->orientation = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->fov = ft_atof(line + i);
	return (obj);
}

t_light *init_light(const char *line, t_input_list *input)
{
	t_light *obj;
	int i;

	obj = (t_light *)malloc(sizeof(t_light));
	i = get_to_next_param(line, 0, input);
	if (i < 0)
		return (obj);
	obj->position = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->brightness = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->color = get_vector3(line, i, input);
	return (obj);
}

t_sphere *init_sphere(const char *line, t_input_list *input)
{
	t_sphere *obj;
	int i;

	obj = (t_sphere *)malloc(sizeof(t_sphere));
	i = get_to_next_param(line, 0, input);
	if (i < 0)
		return (obj);
	obj->center = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->radius = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->color = get_vector3(line, i, input);
	return (obj);
}

t_plane *init_plane(const char *line, t_input_list *input)
{
	t_plane *obj;
	int i;

	obj = (t_plane *)malloc(sizeof(t_plane));
	i = get_to_next_param(line, 0, input);
	if (i < 0)
		return (obj);
	obj->point_on_plane = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->normal = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->color = get_vector3(line, i, input);
	return (obj);
}

t_cylinder *init_cylinder(const char *line, t_input_list *input)
{
	t_cylinder *obj;
	int i;

	obj = (t_cylinder *)malloc(sizeof(t_cylinder));
	i = get_to_next_param(line, 0, input);
	if (i < 0)
		return (obj);
	obj->centre = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->normal_axis = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->diameter = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->height = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	if (i < 0)
		return (obj);
	obj->color = get_vector3(line, i, input);
	return (obj);
}

void	*get_object(t_input_list *input, const char *line)
{
	//for each function here, add a new function that will first check the line acording to the object and then do the initilizing if valid, or skip if invalid.
	void *object;

	if (input->name == 0)
		return (0);
	if (ft_strncmp(input->name, "Ambient", 7) == 0)
		object = init_ambient(line, input);
	if (ft_strncmp(input->name, "Camera", 6) == 0)
		object = init_camera(line, input);
	if (ft_strncmp(input->name, "Light", 5) == 0)
		object = init_light(line, input);
	if (ft_strncmp(input->name, "Sphere", 6) == 0)
		object = init_sphere(line, input);
	if (ft_strncmp(input->name, "Plane", 5) == 0)
		object = init_plane(line, input);
	if (ft_strncmp(input->name, "Cylinder", 8) == 0)
		object = init_cylinder(line, input);
	return (object);
}

void print_input(t_minirt *minirt);


void get_input_list(t_minirt *minirt, int fd)
{
	t_input_list *head;
	t_input_list *temp;
	t_input_list *save;
	char *line;

	line = get_next_line(fd);
	temp = (t_input_list *)malloc(sizeof(t_input_list));
	head = temp;
	while (line != 0)
	{
		if (ft_strlen(line) > 1 && !is_all_space(line))
		{
			temp->name = get_name(line);
			temp->object = get_object(temp, line); // need to fix errored edge casees
			temp->next = (t_input_list *)malloc(sizeof(t_input_list));
			save = temp;
			temp = temp->next;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(save->next);
	save->next = 0;
	minirt->input_head = head;
	//print_input(minirt);
}

int check_file(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	len -= 3;
	if (ft_strncmp((file_name + len), ".rt", 3) != 0)
		return (1);
	len = open(file_name, O_RDONLY);
	if (len < 0)
	{
		perror(file_name);
		return (1);
	}
	close(len);
	return (0);
}
int vector3_checker(t_vector3 vector3, float range_min, float range_max)
{
	if (vector3.x < range_min || vector3.x > range_max)
		return (0);
	if (vector3.y < range_min || vector3.y > range_max)
		return (0);
	if (vector3.z < range_min || vector3.z > range_max)
		return (0);
	return (1);
}

void validate_values_ambient(t_input_list *input)
{
	t_ambient *obj;

	obj = input->object;
	if (obj->intensity < 0.0 || obj->intensity > 1.0)
	{
		printf("Ambient light intensity out of range\n");
		free(input->name);
		input->name = ft_strdup("inv");
		return ;
	}
	if (!vector3_checker(obj->color, 0.0, 255.0))
	{
		printf("Ambient light color out of range\n");
		free(input->name);
		input->name = ft_strdup("inv");
	}
}

void validate_values_camera(t_input_list *input)
{
	int failed;
	t_camera *obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->orientation, -1.0, 1.0))
	{
		printf("Camera orientation out of range\n");
		failed = 1;
	}
	if (obj->fov < 0 || obj->fov > 180)
	{
		printf("Camera FOV out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}

void validate_values_light(t_input_list *input)
{
	int failed;
	t_light *obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->color , 0.0, 255.0))
	{
		printf("light color out of range\n");
		failed = 1;
	}
	if (obj->brightness < 0 || obj->brightness > 1.0)
	{
		printf("Light brightness out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}

void validate_values_sphere(t_input_list *input)
{
	int failed;
	t_sphere *obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->color , 0.0, 255.0))
	{
		printf("Sphere color out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}

void validate_values_plane(t_input_list *input)
{
	int failed;
	t_plane *obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->color , 0.0, 255.0))
	{
		printf("plane color out of range\n");
		failed = 1;
	}
	if (!vector3_checker(obj->normal , -1.0, 1.0))
	{
		printf("plane normal out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}

void validate_values_cylinder(t_input_list *input)
{
	int failed;
	t_cylinder *obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->color , 0.0, 255.0))
	{
		printf("Cylinder color out of range\n");
		failed = 1;
	}
	if (!vector3_checker(obj->normal_axis , -1.0, 1.0))
	{
		printf("Cylinder normal axis out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}

int has_invalid_input(t_input_list *input)
{
	t_input_list *traverse;
	int is_invalid;

	traverse = input;
	is_invalid = 0;
	while (traverse != 0)
	{
		if (traverse->name == 0)
			is_invalid = 1;
		traverse = traverse->next;
	}
	return (is_invalid);
}

void check_esentials(t_minirt *minirt)
{
	t_input_list *traverse;
	int has_esentials;
	int has_an_object;

	has_esentials = 0;
	has_an_object = 0;
	traverse = minirt->input_head;
	while (traverse != 0)
	{
		if (ft_strncmp(traverse->name, "Ambient", 7) == 0)
			has_esentials++;
		else if (ft_strncmp(traverse->name, "Camera", 6) == 0)
			has_esentials++;
		else if (ft_strncmp(traverse->name, "Light", 5) == 0)
			has_esentials++;
		else
			has_an_object++;
		traverse = traverse->next;
	}
	if (has_esentials != 3 && has_an_object == 0)
	{
		printf("Error\nCritical error nothing will be rendered\n");
		minirt->input_validity = -1;
	}
	else
		minirt->input_validity = 1;
}

t_input_list *get_first_valid_node(t_input_list *lst)
{
	while (lst != 0)
	{
		if (lst != 0 && (lst->name == 0 || ft_strncmp(lst->name, "inv", 3) == 0))
			lst = lst->next;
		else
			return(lst);
	}
	return (0);
}

void	final_prepare_input(t_minirt *minirt)
{
	t_input_list *traverse;
	t_input_list *temp;
	t_input_list *last_valid;
	t_input_list *first_valid;

	traverse = minirt->input_head;
	last_valid = traverse;
	first_valid = get_first_valid_node(minirt->input_head);
	while (traverse != 0)
	{
		if (traverse != 0 && traverse->name == 0)
		{
			temp = traverse->next;
			if (last_valid != 0 && (last_valid->name == 0 || ft_strncmp(last_valid->name, "inv", 3) == 0))
				last_valid = last_valid->next;
			else
				last_valid->next = temp;
			free(traverse);
			traverse = temp;
		}
		else if (traverse != 0 && ft_strncmp(traverse->name, "inv", 3) == 0)
		{
			temp = traverse->next;
			if (last_valid != 0 && (last_valid->name == 0 || ft_strncmp(last_valid->name, "inv", 3) == 0))
				last_valid = last_valid->next;
			else
				last_valid->next = temp;
			free(traverse->name);
			free(traverse->object);
			free(traverse);
			traverse = temp;
		}
		else
		{
			if (traverse->next != 0 && traverse->next->name != 0 && ft_strncmp(traverse->next->name, "inv", 3 != 0))
				last_valid = traverse->next;
			else
				last_valid = traverse;
			traverse = traverse->next;
		}
	}
	print_input(minirt);
	minirt->input_head = first_valid;
	check_esentials(minirt);
}

void validate_input(t_minirt *minirt)
{
	t_input_list *input;

	input = minirt->input_head;
	while (input != 0)
	{
		if (input->name == 0 || ft_strncmp(input->name, "inv", 3) == 0)
		{
			printf("Invalid object description, object will not be rendered\n");
			input = input->next;
		}
		if (ft_strncmp(input->name, "Ambient", 7) == 0)
			validate_values_ambient(input);
		if (ft_strncmp(input->name, "Camera", 6) == 0)
			validate_values_camera(input);
		if (ft_strncmp(input->name, "Light", 5) == 0)
			validate_values_light(input);
		if (ft_strncmp(input->name, "Sphere", 6) == 0)
			validate_values_sphere(input);
		if (ft_strncmp(input->name, "Plane", 5) == 0)
			validate_values_plane(input);
		if (ft_strncmp(input->name, "Cylinder", 8) == 0)
			validate_values_cylinder(input);
		input = input->next;
	}
	final_prepare_input(minirt);
}

void print_input(t_minirt *minirt)
{
	t_input_list *input;

	input = minirt->input_head;
	while (input != 0)
	{
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("name: %s\n", input->name);
		if (ft_strncmp(input->name, "Ambient", 7) == 0)
		{
			t_ambient *amb = input->object;
			printf("intense: %f\ncolor: %f , %f, %f.\n", amb->intensity, amb->color.x, amb->color.y, amb->color.z);
		}
		if (ft_strncmp(input->name, "Camera", 6) == 0)
		{
			t_camera *cam = input->object;
			printf("fov: %f\ncoords: %f , %f, %f.\nnormal: %f , %f, %f.\n",cam->fov, cam->position.x, cam->position.y, cam->position.z, cam->orientation.x, cam->orientation.y, cam->orientation.z);
		}
		if (ft_strncmp(input->name, "Light", 5) == 0)
		{
			t_light *cam = input->object;
			printf("brightness: %f\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n",cam->brightness, cam->position.x, cam->position.y, cam->position.z, cam->color.x, cam->color.y, cam->color.z);
		}
		if (ft_strncmp(input->name, "Sphere", 6) == 0)
		{
			t_sphere *cam = input->object;
			printf("radious: %f\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n",cam->radius, cam->center.x, cam->center.y, cam->center.z, cam->color.x, cam->color.y, cam->color.z);
		}
		if (ft_strncmp(input->name, "Plane", 5) == 0)
		{
			t_plane *cam = input->object;
			printf("normal: %f , %f, %f.\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n",cam->normal.x, cam->normal.y, cam->normal.z, cam->point_on_plane.x, cam->point_on_plane.y, cam->point_on_plane.z, cam->color.x, cam->color.y, cam->color.z);
		}
		if (ft_strncmp(input->name, "Cylinder", 8) == 0)
		{
			t_cylinder *cam = input->object;
			printf("height: %f\ndiametre: %f\nnormal: %f , %f, %f.\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n",cam->height ,cam->diameter,cam->normal_axis.x, cam->normal_axis.y, cam->normal_axis.z, cam->centre.x, cam->centre.y, cam->centre.z, cam->color.x, cam->color.y, cam->color.z);
		}
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		input = input->next;
	}

}

int main(int argc, char *argv[])
{
	t_minirt minirt;
	int	fd;

	if ( argc == 2  && !check_file(argv[1]))
		fd = open(argv[1], O_RDONLY);
	else
		return (0);
	/*if (init_minirt(&minirt) == ERROR)
		return (ERROR);*/
	get_input_list(&minirt, fd);
	validate_input(&minirt);
	//mlx_loop_hook(minirt.mlx, &hook, &minirt);
	//mlx_key_hook(minirt.mlx, &keyhook, &minirt);
	//mlx_loop(minirt.mlx);
	//mlx_terminate(minirt.mlx);
	//print_input(&minirt);
	close(fd);
	return (SUCCESS);
}
