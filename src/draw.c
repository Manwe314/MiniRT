/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:18:50 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/05 17:18:50 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
void draw_line(int x1, int y1, int x2, int y2)
{
	// Calculer les différences entre les coordonnées x et y des deux points
	if (x1 == x2 && y1 == y2)
        return ;
    int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	// Déterminer l'incrémentation pour chaque coordonnée
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;

	// Calculer l'erreur initiale
	int err = dx - dy;

	// Boucler sur chaque pixel le long de la ligne
	while (x1 != x2 || y1 != y2)
	{
		// Tracer un pixel à la position actuelle
		if (x1 >= 0 && x1 < g_minirt.width && y1 >= 0 && y1 < g_minirt.height)
			mlx_put_pixel(g_minirt.img, x1, y1,255);

		// Calculer l'erreur et la position suivante
		int e2 = 2 * err;
		if (e2 > -dy)
		{
		 	err -= dy;
		 	x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}


void draw_triangle(t_triangle triangle)
{
    // Définir les sommets du triangle en 3D
    t_matrix4x4 perspMatrix, viewMatrix;
    t_vec3d eye = {g_minirt.world.coord_world.x, g_minirt.world.coord_world.y, g_minirt.world.coord_world.z};
    float yaw = (int)g_minirt.world.angle_world.y;
    yaw = to_radian(yaw);
    float pitch = (int)g_minirt.world.angle_world.x;
    perspMatrix = createperspectivematrix(90.0f, (float)g_minirt.width / (float)g_minirt.height, 0.1f, 1000.0f);

    pitch = to_radian(pitch);
    viewMatrix = FPSViewRH(eye, pitch, yaw);
    triangle.p[0] = multiplymatrixvector(triangle.p[0], viewMatrix);
    triangle.p[1] = multiplymatrixvector(triangle.p[1], viewMatrix);
    triangle.p[2] = multiplymatrixvector(triangle.p[2], viewMatrix);
    triangle.p[0] = multiplymatrixvector(triangle.p[0], perspMatrix);
    triangle.p[1] = multiplymatrixvector(triangle.p[1], perspMatrix);
    triangle.p[2] = multiplymatrixvector(triangle.p[2], perspMatrix);
    t_vec3d v0 = triangle.p[0];
    t_vec3d v1 = triangle.p[1];
    t_vec3d v2 = triangle.p[2];
    perspMatrix = mult_mat4x4(perspMatrix, viewMatrix);

    //perspMatrix = mult_mat4x4(perspMatrix, rotation_x(g_minirt.world.angle_world.x));
    // Appliquer la matrice de perspective aux sommets du triangle
    t_vec3d p0 = multiplymatrixvector(v0, perspMatrix);
    t_vec3d p1 = multiplymatrixvector(v1, perspMatrix);
    t_vec3d p2 = multiplymatrixvector(v2, perspMatrix);

    // Normaliser les sommets projetés par leur coordonnée w
    if (p0.z > 0.001f || p0.z < -0.001f) {
        if (p0.z < 0.0f)
            p0.z = -p0.z;
        p0.x /= p0.z;
        p0.y /= p0.z;
    }
    if (p1.z > 0.001f || p1.z < -0.001f) {
        if (p1.z < 0.0f)
            p1.z = -p1.z;
        p1.x /= p1.z;
        p1.y /= p1.z;
    }
    if (p2.z > 0.001f || p2.z < -0.001f) {
        if (p2.z < 0.0f)
            p2.z = -p2.z;
        p2.x /= p2.z;
        p2.y /= p2.z;
    }
    // Convertir les coordonnées normalisées en coordonnées de pixel
    int x0 = (int)((p0.x + 1.0f) * 0.5f * g_minirt.width);
    int y0 = (int)((1.0f - p0.y) * 0.5f * g_minirt.height);
    int x1 = (int)((p1.x + 1.0f) * 0.5f * g_minirt.width);
    int y1 = (int)((1.0f - p1.y) * 0.5f * g_minirt.height);
    int x2 = (int)((p2.x + 1.0f) * 0.5f * g_minirt.width);
    int y2 = (int)((1.0f - p2.y) * 0.5f * g_minirt.height);
    // Tracer les côtés du triangle
    //printf("x0 = %d, x1 = %d, x2 = %d, y0 = %d, y1 = %d, y2 = %d\n", x0, x1, x2, y0, y1, y2);
    draw_line(x0, y0, x1, y1);
    draw_line(x1, y1, x2, y2);
    draw_line(x2, y2, x0, y0);
}*/

/*
void draw_triangle(t_triangle triangle)
{
    // Appliquer les transformations des matrices de perspective et de vue FPS

    // Appliquer la matrice de vue FPS à chaque point du triangle
    t_vec3d transformedPoints[3];
    for (int i = 0; i < 3; i++) {
        transformedPoints[i] = multiply_matrix_vector(FPSViewMatrix, triangle.points[i]);
    }

    // Appliquer la matrice de perspective à chaque point du triangle
    for (int i = 0; i < 3; i++) {
        transformedPoints[i] = multiply_matrix_vector(PerspectiveMatrix, transformedPoints[i]);
    }

    // Convertir les coordonnées des points 3D en coordonnées 2D
    for (int i = 0; i < 3; i++) {
        transformedPoints[i].x /= transformedPoints[i].z;
        transformedPoints[i].y /= transformedPoints[i].z;
    }

    // Dessiner les arêtes du triangle
    for (int i = 0; i < 3; i++) {
        int x1 = (int)transformedPoints[i].x;
        int y1 = (int)transformedPoints[i].y;
        int x2 = (int)transformedPoints[(i + 1) % 3].x;
        int y2 = (int)transformedPoints[(i + 1) % 3].y;
        draw_line(x1, y1, x2, y2);
    }
}

*/





/*void draw_sphere(t_sphere sphere, int nbLong, int nbLat)
{
    t_vec3d vertices[nbLong * nbLat];

    // Création des vertices
    int i, j;
    for (i = 0; i < nbLong; i++) {
        for (j = 0; j < nbLat; j++) {
            float u = ((float)i / (float)(nbLong-1));
            float v = ((float)j / (float)(nbLat-1));

            float x = cos(u * 2 * M_PI) * sin(v * M_PI);
            float y = sin(u * 2 * M_PI) * sin(v * M_PI);
            float z = cos(v * M_PI);

            vertices[i * nbLat + j] = (t_vec3d) {x, y, z};
        }
    }

    // Création des triangles
    t_triangle triangles[(nbLong-1) * (nbLat-1) * 2];
    int triangleIndex = 0;
    for (i = 0; i < nbLong - 1; i++) {
        for (j = 0; j < nbLat - 1; j++) {
            t_vec3d p1 = vertices[i * nbLat + j];
            t_vec3d p2 = vertices[(i + 1) * nbLat + j];
            t_vec3d p3 = vertices[(i + 1) * nbLat + (j + 1)];
            t_vec3d p4 = vertices[i * nbLat + (j + 1)];

            triangles[triangleIndex++] = (t_triangle) {p1, p2, p3};
            triangles[triangleIndex++] = (t_triangle) {p1, p3, p4};
        }
    }

    // Affichage des triangles
    int nbTriangles = (nbLong - 1) * (nbLat - 1) * 2;
    for (i = 0; i < nbTriangles; i++) {
        drawtriangle(triangles[i]);
    }
}
*/


