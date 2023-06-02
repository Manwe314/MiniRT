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

t_matrix4x4 createperspectivematrix(float fov, float aspect, float near, float far)
{
	t_matrix4x4 m;
	const float zRange = near - far;
	const float tanHalfFOV = tanf(to_radian(fov / 2.0));

	m = init_mat_0();
	m.matrix[0][0] = 1.0f / (tanHalfFOV * aspect);
	m.matrix[1][1] = 1.0f / tanHalfFOV;
	m.matrix[2][2] = (-near - far) / zRange;
	m.matrix[2][3] = 2.0f * far * near / zRange;
	m.matrix[3][2] = 1.0f;
	return (m);
}

t_matrix4x4 inverse_perspective_matrix(t_matrix4x4 matrice)
{
	t_matrix4x4 m;

	m = init_mat_0();
	m.matrix[0][0] = 1.0f / matrice.matrix[0][0];
	m.matrix[1][1] = 1.0f / matrice.matrix[1][1];
	m.matrix[2][3] = 1.0f / matrice.matrix[3][2];
	m.matrix[3][2] = 1.0f / matrice.matrix[2][3];
	m.matrix[3][3] = - (matrice.matrix[2][2] / (matrice.matrix[2][3] * matrice.matrix[3][2]));
	return (m);
}



t_matrix4x4 lookat(t_vec3 eye, t_vec3 target, t_vec3 up)
{
	t_vec3 forward;
	t_vec3 right;
	t_vec3 newUp;
	t_matrix4x4 viewMatrix;

	forward = vec3_normalize(vec3_sub(target, eye));
	right = vec3_normalize(vec3_cross(forward, up));
	newUp = vec3_cross(right, forward);
	viewMatrix = init_mat_0();
	viewMatrix.matrix[0][0] = right.x;
	viewMatrix.matrix[0][1] = newUp.x;
	viewMatrix.matrix[0][2] = -forward.x;
	viewMatrix.matrix[1][0] = right.y;
	viewMatrix.matrix[1][1] = newUp.y;
	viewMatrix.matrix[1][2] = -forward.y;
	viewMatrix.matrix[2][0] = right.z;
	viewMatrix.matrix[2][1] = newUp.z;
	viewMatrix.matrix[2][2] = -forward.z;
	viewMatrix.matrix[3][0] = -dot_product(right, eye);
	viewMatrix.matrix[3][1] = -dot_product(newUp, eye);
	viewMatrix.matrix[3][2] = dot_product(forward, eye);
	viewMatrix.matrix[3][3] = 1.0f;
	return viewMatrix;
}

t_inverse return_inv(t_matrix4x4 m)
{
	t_inverse v;

	v.a = m.matrix[3][2];
	v.p = m.matrix[3][1];
	v.q = m.matrix[3][0];
	v.r = m.matrix[2][2];
	v.s = m.matrix[2][1];
	v.t = m.matrix[2][0];
	v.u = m.matrix[1][2];
	v.v = m.matrix[1][1];
	v.w = m.matrix[1][0];
	v.x = m.matrix[0][2];
	v.y = m.matrix[0][1];
	v.z = m.matrix[0][0];
	return (v);
}

t_matrix4x4 inverse_lookat_matrix(t_matrix4x4 m)
{
	float divider;
	t_matrix4x4 mat;
	t_inverse v;

	v = return_inv(m);
	mat = init_mat_0();
	divider = (-v.r * v.v * v.z + v.r * v.w * v.y + v.s * v.u * v.z - \
	v.s * v.w * v.x - v.t * v.u * v.y + v.t * v.v * v.x);
	if (divider == 0.0f)
		return (mat);
	mat.matrix[0][0] = (v.s * v.u - v.r * v.v) / divider;
	mat.matrix[0][1] = (v.s * v.x - v.r * v.y) / (-divider);
	mat.matrix[0][2] = (v.v * v.x - v.u * v.y) / divider;
	mat.matrix[1][0] = (v.t * v.u - v.r * v.w) / (-divider);
	mat.matrix[1][1] = (v.t * v.x - v.r * v.z) / divider;
	mat.matrix[1][2] = (v.w * v.x - v.u * v.z) / (-divider);
	mat.matrix[2][0] = (v.t * v.v - v.s * v.w) / divider;
	mat.matrix[2][1] = (v.t * v.y - v.s * v.z) / (-divider);
	mat.matrix[2][2] = (v.w * v.y - v.v * v.z) / divider;
	mat.matrix[3][0] = (-v.a * v.s * v.w + v.a * v.t * v.v + v.p * v.r * v.w - \
	v.p * v.t * v.u - v.q * v.r * v.v + v.q * v.s * v.u) / (-divider);
	mat.matrix[3][1] = (-v.a * v.s * v.z + v.a * v.t * v.y + v.p * v.r * v.z - \
	v.p * v.t * v.x - v.q * v.r * v.y + v.q * v.s * v.x) / divider;
	mat.matrix[3][2] = (-v.a * v.v * v.z + v.a * v.w * v.y + v.p * v.u * v.z - \
	v.p * v.w * v.x - v.q * v.u * v.y + v.q * v.v * v.x) / (-divider);
	mat.matrix[3][3] = 1.0f;
}


t_matrix4x4 FPSViewRH( t_vec3 eye, float pitch, float yaw )
{
    // I assume the values are already converted to radians.
    float cosPitch = cos(pitch);
    float sinPitch = sin(pitch);
    float cosYaw = cos(yaw);
    float sinYaw = sin(yaw);

    t_vec3 xaxis = { cosYaw, 0, -sinYaw };
    t_vec3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
    t_vec3 zaxis = { -sinYaw * cosPitch, sinPitch, -cosPitch * cosYaw };

    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    t_matrix4x4 viewMatrix;
	viewMatrix.matrix[0][0] = xaxis.x;
	viewMatrix.matrix[0][1] = yaxis.x;
	viewMatrix.matrix[0][2] = -zaxis.x;
	viewMatrix.matrix[0][3] = 0.0f;
	viewMatrix.matrix[1][0] = xaxis.y;
	viewMatrix.matrix[1][1] = yaxis.y;
	viewMatrix.matrix[1][2] = -zaxis.y;
	viewMatrix.matrix[1][3] = 0.0f;
	viewMatrix.matrix[2][0] = xaxis.z;
	viewMatrix.matrix[2][1] = yaxis.z;
	viewMatrix.matrix[2][2] = -zaxis.z;
	viewMatrix.matrix[2][3] = 0.0f;
	viewMatrix.matrix[3][0] = dot_product(xaxis, eye);
	viewMatrix.matrix[3][1] = dot_product(yaxis, eye);
	viewMatrix.matrix[3][2] = dot_product(zaxis, eye);
	viewMatrix.matrix[3][3] = 1.0f;
    return viewMatrix;
}
