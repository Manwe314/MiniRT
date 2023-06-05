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

t_matrix4x4 translation(t_vec3 vec)
{
	t_matrix4x4 matrix;

	matrix = init_mat_0();
	matrix.matrix[0][0] = 1.0f;
	matrix.matrix[1][1] = 1.0f;
	matrix.matrix[2][2] = 1.0f;
	matrix.matrix[3][3] = 1.0f;
	matrix.matrix[3][0] = vec.x;
	matrix.matrix[3][1] = vec.y;
	matrix.matrix[3][2] = vec.z;
	return (matrix);
}

t_matrix4x4 scale(t_vec3 vec)
{
	t_matrix4x4 matrix;

	matrix = init_mat_0();
	matrix.matrix[0][0] = vec.x;
	matrix.matrix[1][1] = vec.y;
	matrix.matrix[2][2] = vec.z;
	matrix.matrix[3][3] = 1.0f;
	return (matrix);
}

/*
t_matrix4x4 createperspectivematrix(float fov, float aspect, float near, float far)
{
	t_matrix4x4 m;
	const float zRange = near - far;
	const float tanHalfFOV = tanf(to_radian(fov / 2.0));

	m = init_mat_0();
	m.matrix[0][0] = 1.0f / (tanHalfFOV * aspect);
	m.matrix[1][1] = 1.0f / tanHalfFOV;
	m.matrix[2][2] = far / zRange;
	m.matrix[2][3] = -2.0f * far * near / zRange;
	m.matrix[3][2] = -1.0f;
	return (m);
}

*/

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

t_matrix4x4 inverse_perspective_matrix(float fov, float aspect, float near, float far)
{
	t_matrix4x4 m;
	const float zRange = near - far;
	const float tanHalfFOV = tanf(to_radian(fov / 2.0));
// 1/2
// (2 aspect tanHalfFOV | 0 | 0 | 0
// 0 | 2 tanHalfFOV | 0 | 0
// 0 | 0 | 0 | 2
// 0 | 0 | zRange/(far near) | (far + near)/(far near))
	m = init_mat_0();
	m.matrix[0][0] = aspect * tanHalfFOV;
	m.matrix[1][1] = tanHalfFOV;
	m.matrix[2][3] = 1.0f;
	m.matrix[3][2] = zRange/( 2.0f * far * near);
	m.matrix[3][3] = (far + near)/(2.0f * far * near);
	return (m);
}

/*
t_matrix4x4 lookat(t_vec3 eye, t_vec3 target, t_vec3 up)
{
	t_vec3 forward;
	t_vec3 right;
	t_vec3 newUp;
	t_matrix4x4 viewMatrix;

	forward = vec3_normalize(vec3_sub(target, eye));
	right = vec3_normalize(vec3_cross(forward, up));
	newUp = vec3_cross(right, forward);
	viewMatrix.matrix[0][0] = right.x;
	viewMatrix.matrix[0][1] = newUp.x;
	viewMatrix.matrix[0][2] = -forward.x;

	viewMatrix.matrix[1][0] = right.y;
	viewMatrix.matrix[1][1] = newUp.y;
	viewMatrix.matrix[1][2] = -forward.y;

	viewMatrix.matrix[2][0] = right.z;
	viewMatrix.matrix[2][1] = newUp.z;
	viewMatrix.matrix[2][2] = forward.z;

	viewMatrix.matrix[3][0] = -dot_product(right, eye);
	viewMatrix.matrix[3][1] = -dot_product(newUp, eye);
	viewMatrix.matrix[3][2] = dot_product(forward, eye);
	viewMatrix.matrix[3][3] = 1.0f;
	return viewMatrix;
}*/


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
	viewMatrix.matrix[0][2] = forward.x;
	viewMatrix.matrix[1][0] = right.y;
	viewMatrix.matrix[1][1] = newUp.y;
	viewMatrix.matrix[1][2] = forward.y;
	viewMatrix.matrix[2][0] = right.z;
	viewMatrix.matrix[2][1] = newUp.z;
	viewMatrix.matrix[2][2] = forward.z;
	viewMatrix.matrix[3][0] = -dot_product(right, eye);
	viewMatrix.matrix[3][1] = -dot_product(newUp, eye);
	viewMatrix.matrix[3][2] = -dot_product(forward, eye);
	viewMatrix.matrix[3][3] = 1.0f;
	return viewMatrix;
}


/*
((forwardz newUpy - forwardy newUpz)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
 (forwardz newUpx - forwardx newUpz)/(forwardx newUpy rightz - forwardx newUpz righty - forwardy newUpx rightz + forwardy newUpz rightx + forwardz newUpx righty - forwardz newUpy rightx) |
  (forwardy newUpx - forwardx newUpy)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
   0
(forwardz righty - forwardy rightz)/(forwardx newUpy rightz - forwardx newUpz righty - forwardy newUpx rightz + forwardy newUpz rightx + forwardz newUpx righty - forwardz newUpy rightx) |
 (forwardz rightx - forwardx rightz)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
  (forwardy rightx - forwardx righty)/(forwardx newUpy rightz - forwardx newUpz righty - forwardy newUpx rightz + forwardy newUpz rightx + forwardz newUpx righty - forwardz newUpy rightx) |
   0
(newUpz righty - newUpy rightz)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
 (newUpz rightx - newUpx rightz)/(forwardx newUpy rightz - forwardx newUpz righty - forwardy newUpx rightz + forwardy newUpz rightx + forwardz newUpx righty - forwardz newUpy rightx) |
  (newUpy rightx - newUpx righty)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
   0
(-dotforward newUpy rightz + dotforward newUpz righty + dotnewUp forwardy rightz - dotnewUp forwardz righty - dotright forwardy newUpz + dotright forwardz newUpy)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
 (-dotforward newUpx rightz + dotforward newUpz rightx + dotnewUp forwardx rightz - dotnewUp forwardz rightx - dotright forwardx newUpz + dotright forwardz newUpx)/(forwardx newUpy rightz - forwardx newUpz righty - forwardy newUpx rightz + forwardy newUpz rightx + forwardz newUpx righty - forwardz newUpy rightx) |
  (-dotforward newUpx righty + dotforward newUpy rightx + dotnewUp forwardx righty - dotnewUp forwardy rightx - dotright forwardx newUpy + dotright forwardy newUpx)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
   1)
*/
t_matrix4x4 inverse_lookat_matrix(t_vec3 eye, t_vec3 target, t_vec3 up)
{
	t_vec3 forward;
	t_vec3 right;
	t_vec3 newUp;
	t_matrix4x4 viewMatrix;
	float det;

	forward = vec3_normalize(vec3_sub(target, eye));
	right = vec3_normalize(vec3_cross(forward, up));
	newUp = vec3_cross(right, forward);
	det = forward.x * newUp.y * right.z - forward.x * newUp.z * right.y - \
	forward.y * newUp.x * right.z + forward.y * newUp.z * right.x + \
	forward.z * newUp.x * right.y - forward.z * newUp.y * right.x;
	viewMatrix = init_mat_0();
/*
(forwardz newUpy - forwardy newUpz)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
(forwardz newUpx - forwardx newUpz)/(forwardx newUpy rightz - forwardx newUpz righty - forwardy newUpx rightz + forwardy newUpz rightx + forwardz newUpx righty - forwardz newUpy rightx) |
(forwardy newUpx - forwardx newUpy)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
   0
(forwardz righty - forwardy rightz)/(forwardx newUpy rightz - forwardx newUpz righty - forwardy newUpx rightz + forwardy newUpz rightx + forwardz newUpx righty - forwardz newUpy rightx) |
(forwardz rightx - forwardx rightz)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
(forwardy rightx - forwardx righty)/(forwardx newUpy rightz - forwardx newUpz righty - forwardy newUpx rightz + forwardy newUpz rightx + forwardz newUpx righty - forwardz newUpy rightx) |
   0
(newUpz righty - newUpy rightz)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
(newUpz rightx - newUpx rightz)/(forwardx newUpy rightz - forwardx newUpz righty - forwardy newUpx rightz + forwardy newUpz rightx + forwardz newUpx righty - forwardz newUpy rightx) |
(newUpy rightx - newUpx righty)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
   0
(-dotforward newUpy rightz + dotforward newUpz righty + dotnewUp forwardy rightz - dotnewUp forwardz righty - dotright forwardy newUpz + dotright forwardz newUpy)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
(-dotforward newUpx rightz + dotforward newUpz rightx + dotnewUp forwardx rightz - dotnewUp forwardz rightx - dotright forwardx newUpz + dotright forwardz newUpx)/(forwardx newUpy rightz - forwardx newUpz righty - forwardy newUpx rightz + forwardy newUpz rightx + forwardz newUpx righty - forwardz newUpy rightx) |
(-dotforward newUpx righty + dotforward newUpy rightx + dotnewUp forwardx righty - dotnewUp forwardy rightx - dotright forwardx newUpy + dotright forwardy newUpx)/(-forwardx newUpy rightz + forwardx newUpz righty + forwardy newUpx rightz - forwardy newUpz rightx - forwardz newUpx righty + forwardz newUpy rightx) |
   1)
*/
	viewMatrix.matrix[0][0] = (forward.z * newUp.y - forward.y * newUp.z) / (-det);
	viewMatrix.matrix[0][1] = (forward.z * newUp.x - forward.x * newUp.z) / (det);
	viewMatrix.matrix[0][2] = (forward.y * newUp.x - forward.x * newUp.y) / (-det);
	viewMatrix.matrix[1][0] = (forward.z * right.y - forward.y * right.z) / (det);
	viewMatrix.matrix[1][1] = (forward.z * right.x - forward.x * right.z) / (-det);
	viewMatrix.matrix[1][2] = (forward.y * right.x - forward.x * right.y) / (det);
	viewMatrix.matrix[2][0] = (newUp.z * right.y - newUp.y * right.z) / (-det);
	viewMatrix.matrix[2][1] = (newUp.z * right.x - newUp.x * right.z) / (det);
	viewMatrix.matrix[2][2] = (newUp.y * right.x - newUp.x * right.y) / (-det);
	viewMatrix.matrix[3][0] = (-dot_product(forward, eye) * newUp.y * right.z + dot_product(forward, eye) * newUp.z * right.y + dot_product(newUp, eye) * forward.y * right.z - dot_product(newUp, eye) * forward.z * right.y - dot_product(right, eye) * forward.y * newUp.z + dot_product(right, eye) * forward.z * newUp.y) / (-det);
	viewMatrix.matrix[3][1] = (-dot_product(forward, eye) * newUp.x * right.z + dot_product(forward, eye) * newUp.z * right.x + dot_product(newUp, eye) * forward.x * right.z - dot_product(newUp, eye) * forward.z * right.x - dot_product(right, eye) * forward.x * newUp.z + dot_product(right, eye) * forward.z * newUp.x) / (det);
	viewMatrix.matrix[3][2] = (-dot_product(forward, eye) * newUp.x * right.y + dot_product(forward, eye) * newUp.y * right.x + dot_product(newUp, eye) * forward.x * right.y - dot_product(newUp, eye) * forward.y * right.x - dot_product(right, eye) * forward.x * newUp.y + dot_product(right, eye) * forward.y * newUp.x) / (-det);
	viewMatrix.matrix[3][3] = 1.0f;
	return viewMatrix;
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
