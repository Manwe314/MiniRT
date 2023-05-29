/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:15:24 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/26 15:15:24 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4x4 init_mat_0(void)
{
	t_matrix4x4 mat;
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			mat.matrix[i][j] = 0.0f;
	}
	return (mat);
}

t_matrix4x4 rotation_x(float angle)
{
    t_matrix4x4 matrix;
    float c;
    float s;

    c = cos(angle);
    s = sin(angle);
    matrix = init_mat_0();
    matrix.matrix[0][0] = 1.0f;
    matrix.matrix[1][1] = c;
    matrix.matrix[1][2] = -s;
    matrix.matrix[2][1] = s;
    matrix.matrix[2][2] = c;
    matrix.matrix[3][3] = 1.0f;
    return (matrix);
}

t_matrix4x4 rotation_y(float angle)
{
	t_matrix4x4 matrix;
	float c;
	float s;

	c = cos(angle);
	s = sin(angle);
	matrix = init_mat_0();
	matrix.matrix[0][0] = c;
	matrix.matrix[0][2] = s;
	matrix.matrix[1][1] = 1.0f;
	matrix.matrix[2][0] = -s;
	matrix.matrix[2][2] = c;
	matrix.matrix[3][3] = 1.0f;
	return (matrix);
}

t_matrix4x4 rotation_z(float angle)
{
	t_matrix4x4 matrix;
	float c;
	float s;

	c = cos(angle);
	s = sin(angle);
	matrix = init_mat_0();
	matrix.matrix[0][0] = c;
	matrix.matrix[0][1] = -s;
	matrix.matrix[1][0] = s;
	matrix.matrix[1][1] = c;
	matrix.matrix[2][2] = 1.0f;
	matrix.matrix[3][3] = 1.0f;
	return (matrix);
}

t_matrix4x4 translation(float x, float y, float z)
{
	t_matrix4x4 matrix;

	matrix = init_mat_0();
	matrix.matrix[0][0] = 1.0f;
	matrix.matrix[1][1] = 1.0f;
	matrix.matrix[2][2] = 1.0f;
	matrix.matrix[3][3] = 1.0f;
	matrix.matrix[3][0] = x;
	matrix.matrix[3][1] = y;
	matrix.matrix[3][2] = z;
	return (matrix);
}

t_matrix4x4 scale(float x, float y, float z)
{
	t_matrix4x4 matrix;

	matrix = init_mat_0();
	matrix.matrix[0][0] = x;
	matrix.matrix[1][1] = y;
	matrix.matrix[2][2] = z;
	matrix.matrix[3][3] = 1.0f;
	return (matrix);
}

t_vec4d return4d(float x, float y, float z, float w)
{
	t_vec4d vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = w;
	return (vec);
}

t_matrix4x4 projection_transform(float fov, float aspect, float near, float far)
{
	t_matrix4x4 matrix;
	float fov_rad;
	float range;

	fov_rad = 1.0f / tan(fov * 0.5f / 180.0f * M_PI);
	range = 1.0f / (near - far);
	matrix = init_mat_0();
	matrix.matrix[0][0] = aspect * fov_rad;
	matrix.matrix[1][1] = fov_rad;
	matrix.matrix[2][2] = far * range;
	matrix.matrix[2][3] = -1.0f;
	matrix.matrix[3][2] = near * far * range * 2.0f;
	return (matrix);
}


t_matrix4x4 createperspectivematrix(float fov, float aspect, float near, float far)
{
    t_matrix4x4 matrix;
	float tanHalfFov ;
    float zRange;

	tanHalfFov = tanf(fov / 2.0f);
	zRange = far - near;
	matrix = init_mat_0();
    matrix.matrix[0][0] = 1.0f / (tanHalfFov * aspect);
	matrix.matrix[1][1] = 1.0f / tanHalfFov;
	matrix.matrix[2][2] = -(far + near) / zRange;
	matrix.matrix[2][3] = -1.0f;
	matrix.matrix[3][2] = -(2.0f * far * near) / zRange;
	return (matrix);
}
// Pitch must be in the range of [-90 ... 90] degrees and
// yaw must be in the range of [0 ... 360] degrees.
// Pitch and yaw variables must be expressed in radians.
mat4 FPSViewRH( vec3 eye, float pitch, float yaw )
{
    // I assume the values are already converted to radians.
    float cosPitch = cos(pitch);
    float sinPitch = sin(pitch);
    float cosYaw = cos(yaw);
    float sinYaw = sin(yaw);

    t_vec3d xaxis = { cosYaw, 0, -sinYaw };
    t_vec3d yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
    t_vec3d zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    t_matrix4x4 viewMatrix;
	viewMatrix.matrix[0] = return4d(xaxis.x, yaxis.x, zaxis.x, 0);
	viewMatrix.matrix[1] = return4d(xaxis.y, yaxis.y, zaxis.y, 0);
	viewMatrix.matrix[2] = return4d(xaxis.z, yaxis.z, zaxis.z, 0);
	viewMatrix.matrix[3] = return4d(-dot_product(xaxis, eye), -dot_product(yaxis, eye), -dot_product(zaxis, eye), 1);

    return viewMatrix;
}




