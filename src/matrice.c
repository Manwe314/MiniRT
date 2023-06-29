/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:21:05 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:21:05 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4x4	init_mat_0(void)
{
	t_matrix4x4	mat;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			mat.matrix[i][j] = 0.0f;
	}
	return (mat);
}

t_matrix4x4	rotation_x(float angle)
{
	t_matrix4x4		matrix;
	float			c;
	float			s;

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

t_matrix4x4	rotation_y(float angle)
{
	t_matrix4x4	matrix;
	float		c;
	float		s;

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

t_matrix4x4	rotation_z(float angle)
{
	t_matrix4x4	matrix;
	float		c;
	float		s;

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

t_matrix4x4	translation(t_vector3 vec)
{
	t_matrix4x4	matrix;

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

t_matrix4x4	scale(t_vector3 vec)
{
	t_matrix4x4	matrix;

	matrix = init_mat_0();
	matrix.matrix[0][0] = vec.x;
	matrix.matrix[1][1] = vec.y;
	matrix.matrix[2][2] = vec.z;
	matrix.matrix[3][3] = 1.0f;
	return (matrix);
}

/*
t_matrix4x4	createperspectivematrix(float fov, float aspect, float near,
		float far)
{
	t_matrix4x4 m;
	const float zRange = near - far;
	const float tanhalffov = tanf(to_radian(fov / 2.0));

	m = init_mat_0();
	m.matrix[0][0] = 1.0f / (tanhalffov * aspect);
	m.matrix[1][1] = 1.0f / tanhalffov;
	m.matrix[2][2] = far / zRange;
	m.matrix[2][3] = -2.0f * far * near / zRange;
	m.matrix[3][2] = -1.0f;
	return (m);
}

*/

t_matrix4x4	createperspectivematrix(float fov, float aspect, float near, \
		float far)
{
	t_matrix4x4	m;
	const float	zrange = near - far;
	const float	tanhalffov = tanf(to_radian(fov / 2.0));

	m = init_mat_0();
	m.matrix[0][0] = 1.0f / (tanhalffov * aspect);
	m.matrix[1][1] = 1.0f / tanhalffov;
	m.matrix[2][2] = (-near - far) / zrange;
	m.matrix[2][3] = 2.0f * far * near / zrange;
	m.matrix[3][2] = 1.0f;
	return (m);
}

t_matrix4x4	inverse_perspective_matrix(float fov, float aspect, float near,
		float far)
{
	t_matrix4x4 m;
	const float zrange = near - far;
	const float tanhalffov = tanf(to_radian(fov / 2.0));
	// 1/2
	// (2 aspect tanhalffov | 0 | 0 | 0
	// 0 | 2 tanhalffov | 0 | 0
	// 0 | 0 | 0 | 2
	// 0 | 0 | zrange/(far near) | (far + near)/(far near))
	m = init_mat_0();
	m.matrix[0][0] = aspect * tanhalffov;
	m.matrix[1][1] = tanhalffov;
	m.matrix[2][3] = 1.0f;
	m.matrix[3][2] = zrange / (2.0f * far * near);
	m.matrix[3][3] = (far + near) / (2.0f * far * near);
	return (m);
}

/*
t_matrix4x4	lookat(t_vector3 eye, t_vector3 target, t_vector3 up)
{
	t_vector3 forward;
	t_vector3 right;
	t_vector3 newup;
	t_matrix4x4 viewmatrix;

	forward = vector3_normalize(vector3_subtract(target, eye));
	right = vector3_normalize(vector3_cross(forward, up));
	newup = vector3_cross(right, forward);
	viewmatrix.matrix[0][0] = right.x;
	viewmatrix.matrix[0][1] = newup.x;
	viewmatrix.matrix[0][2] = -forward.x;

	viewmatrix.matrix[1][0] = right.y;
	viewmatrix.matrix[1][1] = newup.y;
	viewmatrix.matrix[1][2] = -forward.y;

	viewmatrix.matrix[2][0] = right.z;
	viewmatrix.matrix[2][1] = newup.z;
	viewmatrix.matrix[2][2] = forward.z;

	viewmatrix.matrix[3][0] = -vector3_dot(right, eye);
	viewmatrix.matrix[3][1] = -vector3_dot(newup, eye);
	viewmatrix.matrix[3][2] = vector3_dot(forward, eye);
	viewmatrix.matrix[3][3] = 1.0f;
	return (viewmatrix);
}*/

t_matrix4x4	lookat(t_vector3 eye, t_vector3 target, t_vector3 up)
{
	t_vector3	forward;
	t_vector3	right;
	t_vector3	newup;
	t_matrix4x4	viewmatrix;

	forward = vector3_normalize(vector3_subtract(target, eye));
	right = vector3_normalize(vector3_cross(forward, up));
	newup = vector3_cross(right, forward);
	viewmatrix = init_mat_0();
	viewmatrix.matrix[0][0] = right.x;
	viewmatrix.matrix[0][1] = newup.x;
	viewmatrix.matrix[0][2] = forward.x;
	viewmatrix.matrix[1][0] = right.y;
	viewmatrix.matrix[1][1] = newup.y;
	viewmatrix.matrix[1][2] = forward.y;
	viewmatrix.matrix[2][0] = right.z;
	viewmatrix.matrix[2][1] = newup.z;
	viewmatrix.matrix[2][2] = forward.z;
	viewmatrix.matrix[3][0] = -vector3_dot(right, eye);
	viewmatrix.matrix[3][1] = -vector3_dot(newup, eye);
	viewmatrix.matrix[3][2] = -vector3_dot(forward, eye);
	viewmatrix.matrix[3][3] = 1.0f;
	return (viewmatrix);
}

/*
((forwardz newupy - forwardy newupz)/(-forwardx newupy rightz
		+ forwardx newupz righty + forwardy newupx rightz
		- forwardy newupz rightx - forwardz newupx righty
		+ forwardz newupy rightx) |
 (forwardz newupx - forwardx newupz)/(forwardx newupy rightz
	- forwardx newupz righty - forwardy newupx rightz + forwardy newupz rightx
	+ forwardz newupx righty - forwardz newupy rightx) |
  (forwardy newupx - forwardx newupy)/(-forwardx newupy rightz
	+ forwardx newupz righty + forwardy newupx rightz - forwardy newupz rightx
	- forwardz newupx righty + forwardz newupy rightx) |
   0
(forwardz righty - forwardy rightz)/(forwardx newupy rightz
	- forwardx newupz righty - forwardy newupx rightz + forwardy newupz rightx
	+ forwardz newupx righty - forwardz newupy rightx) |
 (forwardz rightx - forwardx rightz)/(-forwardx newupy rightz
	+ forwardx newupz righty + forwardy newupx rightz - forwardy newupz rightx
	- forwardz newupx righty + forwardz newupy rightx) |
  (forwardy rightx - forwardx righty)/(forwardx newupy rightz
	- forwardx newupz righty - forwardy newupx rightz + forwardy newupz rightx
	+ forwardz newupx righty - forwardz newupy rightx) |
   0
(newupz righty - newupy rightz)/(-forwardx newupy rightz
	+ forwardx newupz righty + forwardy newupx rightz - forwardy newupz rightx
	- forwardz newupx righty + forwardz newupy rightx) |
 (newupz rightx - newupx rightz)/(forwardx newupy rightz
	- forwardx newupz righty - forwardy newupx rightz + forwardy newupz rightx
	+ forwardz newupx righty - forwardz newupy rightx) |
  (newupy rightx - newupx righty)/(-forwardx newupy rightz
	+ forwardx newupz righty + forwardy newupx rightz - forwardy newupz rightx
	- forwardz newupx righty + forwardz newupy rightx) |
   0
(-dotforward newupy rightz + dotforward newupz righty + dotnewup forwardy rightz
	- dotnewup forwardz righty - dotright forwardy newupz
	+ dotright forwardz newupy)/(-forwardx newupy rightz
	+ forwardx newupz righty + forwardy newupx rightz - forwardy newupz rightx
	- forwardz newupx righty + forwardz newupy rightx) |
 (-dotforward newupx rightz + dotforward newupz rightx
	+ dotnewup forwardx rightz - dotnewup forwardz rightx
	- dotright forwardx newupz
	+ dotright forwardz newupx)/(forwardx newupy rightz - forwardx newupz righty
	- forwardy newupx rightz + forwardy newupz rightx + forwardz newupx righty
	- forwardz newupy rightx) |
  (-dotforward newupx righty + dotforward newupy rightx
	+ dotnewup forwardx righty - dotnewup forwardy rightx
	- dotright forwardx newupy
	+ dotright forwardy newupx)/(-forwardx newupy rightz
	+ forwardx newupz righty + forwardy newupx rightz - forwardy newupz rightx
	- forwardz newupx righty + forwardz newupy rightx) |
   1)
*/
t_matrix4x4	inverse_lookat_matrix(t_vector3 eye, t_vector3 target,
		t_vector3 up)
{
	t_vector3	forward;
	t_vector3	right;
	t_vector3	newup;
	t_matrix4x4	viewmatrix;
	float		det;

	forward = vector3_normalize(vector3_subtract(target, eye));
	right = vector3_normalize(vector3_cross(forward, up));
	newup = vector3_cross(right, forward);
	det = forward.x * newup.y * right.z - forward.x * newup.z * right.y
		- forward.y * newup.x * right.z + forward.y * newup.z * right.x
		+ forward.z * newup.x * right.y - forward.z * newup.y * right.x;
	viewmatrix = init_mat_0();
	/*
	(forwardz newupy - forwardy newupz)/(-forwardx newupy rightz
		+ forwardx newupz righty + forwardy newupx rightz
		- forwardy newupz rightx - forwardz newupx righty
		+ forwardz newupy rightx) |
	(forwardz newupx - forwardx newupz)/(forwardx newupy rightz
		- forwardx newupz righty - forwardy newupx rightz
		+ forwardy newupz rightx + forwardz newupx righty
		- forwardz newupy rightx) |
	(forwardy newupx - forwardx newupy)/(-forwardx newupy rightz
		+ forwardx newupz righty + forwardy newupx rightz
		- forwardy newupz rightx - forwardz newupx righty
		+ forwardz newupy rightx) |
		0
	(forwardz righty - forwardy rightz)/(forwardx newupy rightz
		- forwardx newupz righty - forwardy newupx rightz
		+ forwardy newupz rightx + forwardz newupx righty
		- forwardz newupy rightx) |
	(forwardz rightx - forwardx rightz)/(-forwardx newupy rightz
		+ forwardx newupz righty + forwardy newupx rightz
		- forwardy newupz rightx - forwardz newupx righty
		+ forwardz newupy rightx) |
	(forwardy rightx - forwardx righty)/(forwardx newupy rightz
		- forwardx newupz righty - forwardy newupx rightz
		+ forwardy newupz rightx + forwardz newupx righty
		- forwardz newupy rightx) |
		0
	(newupz righty - newupy rightz)/(-forwardx newupy rightz
		+ forwardx newupz righty + forwardy newupx rightz
		- forwardy newupz rightx - forwardz newupx righty
		+ forwardz newupy rightx) |
	(newupz rightx - newupx rightz)/(forwardx newupy rightz
		- forwardx newupz righty - forwardy newupx rightz
		+ forwardy newupz rightx + forwardz newupx righty
		- forwardz newupy rightx) |
	(newupy rightx - newupx righty)/(-forwardx newupy rightz
		+ forwardx newupz righty + forwardy newupx rightz
		- forwardy newupz rightx - forwardz newupx righty
		+ forwardz newupy rightx) |
		0
	(-dotforward newupy rightz + dotforward newupz righty
		+ dotnewup forwardy rightz - dotnewup forwardz righty
		- dotright forwardy newupz
		+ dotright forwardz newupy)/(-forwardx newupy rightz
		+ forwardx newupz righty + forwardy newupx rightz
		- forwardy newupz rightx - forwardz newupx righty
		+ forwardz newupy rightx) |
	(-dotforward newupx rightz + dotforward newupz rightx
		+ dotnewup forwardx rightz - dotnewup forwardz rightx
		- dotright forwardx newupz
		+ dotright forwardz newupx)/(forwardx newupy rightz
		- forwardx newupz righty - forwardy newupx rightz
		+ forwardy newupz rightx + forwardz newupx righty
		- forwardz newupy rightx) |
	(-dotforward newupx righty + dotforward newupy rightx
		+ dotnewup forwardx righty - dotnewup forwardy rightx
		- dotright forwardx newupy
		+ dotright forwardy newupx)/(-forwardx newupy rightz
		+ forwardx newupz righty + forwardy newupx rightz
		- forwardy newupz rightx - forwardz newupx righty
		+ forwardz newupy rightx) |
		1)
	*/
	viewmatrix.matrix[0][0] = (forward.z * newup.y - forward.y * newup.z)
		/ (-det);
	viewmatrix.matrix[0][1] = (forward.z * newup.x - forward.x * newup.z)
		/ (det);
	viewmatrix.matrix[0][2] = (forward.y * newup.x - forward.x * newup.y)
		/ (-det);
	viewmatrix.matrix[1][0] = (forward.z * right.y - forward.y * right.z)
		/ (det);
	viewmatrix.matrix[1][1] = (forward.z * right.x - forward.x * right.z)
		/ (-det);
	viewmatrix.matrix[1][2] = (forward.y * right.x - forward.x * right.y)
		/ (det);
	viewmatrix.matrix[2][0] = (newup.z * right.y - newup.y * right.z) / (-det);
	viewmatrix.matrix[2][1] = (newup.z * right.x - newup.x * right.z) / (det);
	viewmatrix.matrix[2][2] = (newup.y * right.x - newup.x * right.y) / (-det);
	viewmatrix.matrix[3][0] = (-vector3_dot(forward, eye) * newup.y * right.z
		+ vector3_dot(forward, eye) * newup.z * right.y + vector3_dot(newup,
			eye) * forward.y * right.z - vector3_dot(newup, eye) * forward.z
		* right.y - vector3_dot(right, eye) * forward.y * newup.z
		+ vector3_dot(right, eye) * forward.z * newup.y) / (-det);
	viewmatrix.matrix[3][1] = (-vector3_dot(forward, eye) * newup.x * right.z
		+ vector3_dot(forward, eye) * newup.z * right.x + vector3_dot(newup,
			eye) * forward.x * right.z - vector3_dot(newup, eye) * forward.z
		* right.x - vector3_dot(right, eye) * forward.x * newup.z
		+ vector3_dot(right, eye) * forward.z * newup.x) / (det);
	viewmatrix.matrix[3][2] = (-vector3_dot(forward, eye) * newup.x * right.y
		+ vector3_dot(forward, eye) * newup.y * right.x + vector3_dot(newup,
			eye) * forward.x * right.y - vector3_dot(newup, eye) * forward.y
		* right.x - vector3_dot(right, eye) * forward.x * newup.y
		+ vector3_dot(right, eye) * forward.y * newup.x) / (-det);
	viewmatrix.matrix[3][3] = 1.0f;
	return (viewmatrix);
}

t_matrix4x4	FPSViewRH(t_vector3 eye, float pitch, float yaw)
{
	// I assume the values are already converted to radians.
	float cosPitch = cos(pitch);
	float sinPitch = sin(pitch);
	float cosYaw = cos(yaw);
	float sinYaw = sin(yaw);

	t_vector3 xaxis = {cosYaw, 0, -sinYaw};
	t_vector3 yaxis = {sinYaw * sinPitch, cosPitch, cosYaw * sinPitch};
	t_vector3 zaxis = {-sinYaw * cosPitch, sinPitch, -cosPitch * cosYaw};

	// Create a 4x4 view matrix from the right, up,	forward and eye position vectors
	t_matrix4x4 viewmatrix;
	viewmatrix.matrix[0][0] = xaxis.x;
	viewmatrix.matrix[0][1] = yaxis.x;
	viewmatrix.matrix[0][2] = -zaxis.x;
	viewmatrix.matrix[0][3] = 0.0f;
	viewmatrix.matrix[1][0] = xaxis.y;
	viewmatrix.matrix[1][1] = yaxis.y;
	viewmatrix.matrix[1][2] = -zaxis.y;
	viewmatrix.matrix[1][3] = 0.0f;
	viewmatrix.matrix[2][0] = xaxis.z;
	viewmatrix.matrix[2][1] = yaxis.z;
	viewmatrix.matrix[2][2] = -zaxis.z;
	viewmatrix.matrix[2][3] = 0.0f;
	viewmatrix.matrix[3][0] = vector3_dot(xaxis, eye);
	viewmatrix.matrix[3][1] = vector3_dot(yaxis, eye);
	viewmatrix.matrix[3][2] = vector3_dot(zaxis, eye);
	viewmatrix.matrix[3][3] = 1.0f;
	return (viewmatrix);
}
