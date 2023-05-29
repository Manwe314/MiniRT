/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:52:20 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/05 17:52:20 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

extern t_minirt g_minirt;

t_vec3d multiplymatrixvector(t_vec3d i, t_matrix4x4 m)
{
	t_vec3d o;
	float w;
	o.x = i.x * m.matrix[0][0] + i.y * m.matrix[1][0] + i.z * m.matrix[2][0] + m.matrix[3][0];
	o.y = i.x * m.matrix[0][1] + i.y * m.matrix[1][1] + i.z * m.matrix[2][1] + m.matrix[3][1];
	o.z = i.x * m.matrix[0][2] + i.y * m.matrix[1][2] + i.z * m.matrix[2][2] + m.matrix[3][2];
	w = i.x * m.matrix[0][3] + i.y * m.matrix[1][3] + i.z * m.matrix[2][3] + m.matrix[3][3];
	if (w != 0.0f)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
	return (o);
}


t_matrix4x4 mult_mat4x4(t_matrix4x4 mat1, t_matrix4x4 mat2)
{
	t_matrix4x4 result;
	int i;
	int j;
	int k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			result.matrix[i][j] = 0;
			k = -1;
			while (++k < 4)
				result.matrix[i][j] += mat1.matrix[i][k] * mat2.matrix[k][j];
		}
	}
	return (result);
}

t_matrix4x4 createperspectivematrix(float fov, float aspect, float near, float far)
{
    t_matrix4x4 matrix;
	float tanHalfFov ;
    float zRange;
	int i;
	int j;

	tanHalfFov = tanf(fov / 2.0f);
	zRange = far - near;
	i = -1;
	matrix = init_mat_0();
    matrix.matrix[0][0] = 1.0f / (tanHalfFov * aspect);
	matrix.matrix[1][1] = 1.0f / tanHalfFov;
	matrix.matrix[2][2] = -(far + near) / zRange;
	matrix.matrix[2][3] = -1.0f;
	matrix.matrix[3][2] = -(2.0f * far * near) / zRange;
	return (matrix);
}



/*void calculate_view_matrix(t_camera *camera)
{
    t_vec3d forward = vec3d_sub(camera->target, camera->pos);
    forward = vec3d_normalize(forward);

    t_vec3d side = vec3d_cross(forward, camera->up);
    side = vec3d_normalize(side);

    t_vec3d newUp = vec3d_cross(side, forward);

    t_matrix4x4 orientation = { { side.x,   side.y,   side.z,   0 },
                                { newUp.x,  newUp.y,  newUp.z,  0 },
                                { -forward.x, -forward.y, -forward.z, 0 },
                                { 0,        0,        0,        1 } };

    t_matrix4x4 translation = create_translation_matrix(-camera->pos.x, -camera->pos.y, -camera->pos.z);

    camera->view_matrix = mult_mat4x4(orientation, translation);
}*/


float to_radian(float angle)
{
	return (angle * (M_PI / 180));
}
/*
void sortPoints(Point3D **points, int n)
{
    // Create an array of indices
    int *indices = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }

    // Sort the indices based on the y-coordinate of the points
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && (*points)[indices[j - 1]].y > (*points)[indices[j]].y) {
            int temp = indices[j];
            indices[j] = indices[j - 1];
            indices[j - 1] = temp;
            j--;
        }
    }

    // Sort the points of each row based on their x-coordinate
    for (int i = 0; i < n - 1; i++) {
        if ((*points)[indices[i]].y == (*points)[indices[i + 1]].y) {
            if ((*points)[indices[i]].x > (*points)[indices[i + 1]].x) {
                int temp = indices[i];
                indices[i] = indices[i + 1];
                indices[i + 1] = temp;
                if (i > 0) {
                    i -= 2;
                } else {
                    i--;
                }
            }
        }
    }
}
*/


t_vec3d vec3d_sub(t_vec3d v1, t_vec3d v2)
{
    t_vec3d result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

float vec3d_magnitude(t_vec3d v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3d vec3d_normalize(t_vec3d v)
{
    float mag = vec3d_magnitude(v);
    t_vec3d result;
    result.x = v.x / mag;
    result.y = v.y / mag;
    result.z = v.z / mag;
    return result;
}

t_vec3d vec3d_cross(t_vec3d v1, t_vec3d v2)
{
    t_vec3d result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}
