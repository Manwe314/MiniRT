/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:15:54 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/06 13:15:54 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*t_vector4 PerPixel(t_ray ray, t_scene scene)

{
	t_vector4 color;
	t_sphere* closestsphere = 0;
	float closest = FLT_MAX;


	color = vector4(0.0f, 0.0f, 0.0f, 1.0f);
	t_sphere sphere[10];
	int nb_sphere = 6;
	int i = -1;
	sphere[0] = add_sphere(vector3(1.0f, 0.0f, 0.0f),  0.3f, vector3(1.0f, 0.0f, 0.0f));
	sphere[1] = add_sphere(vector3(0.0f, 1.0f, 0.0f),  0.3f, vector3(0.0f, 1.0f, 0.0f));
	sphere[2] = add_sphere(vector3(0.0f, 0.0f, 1.0f),  0.3f, vector3(0.0f, 0.0f, 1.0f));
	sphere[3] = add_sphere(vector3(-1.0f, 0.0f, 0.0f), 0.3f, vector3(1.0f, 1.0f, 0.0f));
	sphere[4] = add_sphere(vector3(0.0f, -1.0f, 0.0f), 0.3f, vector3(1.0f, 0.0f, 1.0f));
	sphere[5] = add_sphere(vector3(0.0f, 0.0f, -1.0f), 0.3f, vector3(1.0f, 1.0f, 1.0f));

	//t_vector3 oc = ray.origin;

	while (++i < nb_sphere)
	{
		t_vector3 oc = vector3_subtract(ray.origin, sphere[i].center);

		float a = vector3_dot(ray.direction, ray.direction);
		float b = 2.0f * vector3_dot(oc, ray.direction);
		float c = vector3_dot(oc, oc) - sphere[i].radius * sphere[i].radius;

		float det = b * b - 4 * a * c;
		if (det < 0)
			continue;
		float t = (-b - sqrtf(det)) / (2.0f * a);
		if (t < 0)
			continue;
			//t = (-b - sqrtf(det)) / (2.0f * a);
		if (closest > t)
		{
			closest = t;
			closestsphere = &sphere[i];
		}
	}
	if (closestsphere == 0)
		return (color);

	t_vector3 oc = vector3_subtract(ray.origin, closestsphere->center);
	t_vector3 hit = vector3_add(oc, vector3_multiply_float(ray.direction, closest));
	t_vector3 normal = vector3_normalize(hit);
	t_vector3 light_dir = vector3_normalize(vector3(1.0f, 1.0f, 1.0f));
	float diffuse = vector3_dot(light_dir, normal);
	diffuse = max(diffuse, 0.0f);

	// sphere[i].color = normal;
	// sphere[i].color = vector3_multiply(sphere[i].color, normal);
	// sphere[i].color = vector3_normalize(sphere[i].color);
	// sphere[i].color = vector3_multiply_float(sphere[i].color, 0.5f);
	// sphere[i].color = vector3_add_float(sphere[i].color, 0.5f);

	closestsphere->color = vector3_multiply_float(closestsphere->color, diffuse);
	color = vector4(closestsphere->color.x, closestsphere->color.y, closestsphere->color.z, 1.0f);
	return (color);
}
*/

t_vector3 vector3_normal(t_vector3 a,t_vector3 b)
{
    t_vector3 normal;
    normal.x = a.y * b.z - a.z * b.y;
    normal.y = a.z * b.x - a.x * b.z;
    normal.z = a.x * b.y - a.y * b.x;
    return normal;
}

t_vector4 pointintriangle(t_vector2 A, t_vector2 B, t_vector2 C, t_vector2 P)
{
		double s1 = C.y - A.y;
		double s2 = C.x - A.x;
		double s3 = B.y - A.y;
		double s4 = P.y - A.y;
		double w1 = (A.x * s1 + s4 * s2 - P.x * s1) / (s3 * s2 - (B.x-A.x) * s1);
		double w2 = (s4- w1 * s3) / s1;
		if (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1)
			return (vector4(w1, w2, 1.0f - w1 - w2, 1.0f));
		return (vector4(0.0f, 0.0f, 0.0f, 1.0f));
}

/*t_vector4 renderer(t_vector2 coord, t_minirt *minirt)
{
	t_vector3 u,v,normal, t[3];
	t_vector2 x, y, z, a,b;
	t_vector4 color;
	//float x,y,z;
	int i = -1;

	while (++i < 3)
	{
		t[0] = minirt->model.triangles[i].p[0];
		t[1] = minirt->model.triangles[i].p[1];
		t[2] = minirt->model.triangles[i].p[2];
		// u = vector3_subtract(minirt->model.triangles[i].p[0], minirt->model.triangles[i].p[1]);
		// v = vector3_subtract(minirt->model.triangles[i].p[0], minirt->model.triangles[i].p[2]);
		// normal = vector3_normal(u,v);
		// c = vector3_subtract(minirt->model.triangles[i].pos1, minirt->camera.pos);
		x = vector2(t[0].x / t[0].z, t[0].y / t[0].z);
		y = vector2(t[1].x / t[1].z, t[1].y / t[1].z);
		z = vector2(t[2].x / t[2].z, t[2].y / t[2].z);
		color = pointintriangle(y, x, z, coord);
		if (color.x != 0.0f || color.y != 0.0f || color.z != 0.0f)
			return (color);
	}
	return (vector4(0.0f, 0.0f, 0.0f, 1.0f));
}

t_vector4 renderer(t_ray ray, t_minirt *minirt)
{
	t_vector4 color;
	t_sphere* closestsphere = 0;
	float closest = FLT_MAX;


	color = vector4(0.0f, 0.0f, 0.0f, 1.0f);
	t_sphere sphere[2];
	int nb_sphere = 2;
	int i = -1;
	sphere[0] = add_sphere(vector3(0.5f, 0.5f, 0.0f), 1.0f, vector3(1.0f, 0.0f, 0.0f));
	sphere[1] = add_sphere(vector3(0.0f, 0.0f, 0.0f), 1.0f, vector3(0.0f, 1.0f, 0.0f));
	//t_vector3 oc = ray.origin;

	while (++i < nb_sphere)
	{
		t_vector3 oc = vector3_subtract(ray.origin, sphere[i].center);

		float a = vector3_dot(ray.direction, ray.direction);
		float b = 2.0f * vector3_dot(oc, ray.direction);
		float c = vector3_dot(oc, oc) - sphere[i].radius * sphere[i].radius;

		float det = b * b - 4 * a * c;
		if (det < 0)
			continue;
		float t = (-b - sqrtf(det)) / (2.0f * a);
		if (t < 0)
			continue;
			//t = (-b - sqrtf(det)) / (2.0f * a);
		if (closest > t)
		{
			closest = t;
			closestsphere = &sphere[i];
		}
	}
	if (closestsphere == 0)
		return (color);

	t_vector3 oc = vector3_subtract(ray.origin, closestsphere->center);
	t_vector3 hit = vector3_add(oc, vector3_multiply_float(ray.direction, closest));
	t_vector3 normal = vector3_normalize(hit);
	t_vector3 light_dir = vector3_normalize(vector3(1.0f, 1.0f, 1.0f));
	float diffuse = vector3_dot(light_dir, normal);
	diffuse = max(diffuse, 0.0f);

	// sphere[i].color = normal;
	// sphere[i].color = vector3_multiply(sphere[i].color, normal);
	// sphere[i].color = vector3_normalize(sphere[i].color);
	// sphere[i].color = vector3_multiply_float(sphere[i].color, 0.5f);
	// sphere[i].color = vector3_add_float(sphere[i].color, 0.5f);

	closestsphere->color = vector3_multiply_float(closestsphere->color, diffuse);
	color = vector4(closestsphere->color.x, closestsphere->color.y, closestsphere->color.z, 1.0f);
	return (color);
}

*/


/*
t_hitpayload closesthit(t_ray ray, float hitdistance, int index, t_scene scene)
{
	t_hitpayload payload;
	t_sphere closestsphere;

	closestsphere = scene.sphere[index];
	payload.hitdistance = hitdistance;
	payload.objectindex = index;

	t_vector3 origin = vector3_subtract(ray.origin, closestsphere.center);
	payload.worldposition = vector3_multiply_float(ray.direction, payload.hitdistance);
	payload.worldposition = vector3_add(origin, payload.worldposition);

	payload.worldnormal = vector3_normalize(payload.worldposition);
	payload.worldposition = vector3_add(closestsphere.center, payload.worldposition);
	return (payload);
}

t_hitpayload miss(t_ray ray)
{
	t_hitpayload payload;
	payload.hitdistance = -1.0f;
	return payload;
}

t_hitpayload traceray(const t_ray ray, t_scene scene)
{
	int closestsphere = -1;
	int i = -1;
	float closest = FLT_MAX;

	while (++i < scene.nb_sphere)
	{
		t_vector3 oc = vector3_subtract(ray.origin, scene.sphere[i].center);

		float a = vector3_dot(ray.direction, ray.direction);
		float b = 2.0f * vector3_dot(oc, ray.direction);
		float c = vector3_dot(oc, oc) - scene.sphere[i].radius * scene.sphere[i].radius;

		float det = b * b - 4 * a * c;
		if (det < 0)
			continue;

		float t = (-b - sqrtf(det)) / (2.0f * a);
		//t = (-b + sqrtf(det)) / (2.0f * a);
		if (closest > t && t > 0)
		{
			closest = t;
			closestsphere = i;
		}
	}
	if (closestsphere < 0)
		return (miss(ray));
	return (closesthit(ray, closest, closestsphere, scene));
}

t_vector4 renderer(t_ray ray, t_minirt *minirt)
{
	t_vector3 color;
	t_hitpayload payload;
	t_sphere closestsphere;
	float closest = FLT_MAX;
	float multiplier = 0.7f;



	color = vector3(0.0f, 0.0f, 0.0f);
	minirt->scene.sphere[0] = add_sphere(vector3(0.5f, 0.0f, 0.0f), 1.0f, vector3(1.0f, 0.0f, 0.0f));
	minirt->scene.sphere[1] = add_sphere(vector3(0.0f, 0.0f, 0.0f), 1.0f, vector3(0.0f, 1.0f, 0.0f));
	minirt->scene.nb_sphere = 2;
	int bounces = 1;
	int i = -1;
	while (++i < bounces)
	{
		payload = traceray(ray, minirt->scene);
		if (payload.hitdistance < 0)
		{
			t_vector3 skycolor = vector3(0.0f, 0.0f , 0.0f);
			skycolor = vector3_multiply_float(skycolor, multiplier);
			color = vector3_add(color, skycolor);
			break;
		}

		t_vector3 light_dir = vector3_normalize(vector3(1.0f, 1.0f, 1.0f));
		float lightintensity  = vector3_dot(light_dir, payload.worldnormal);
		lightintensity  = max(lightintensity , 0.0f);

		closestsphere = minirt->scene.sphere[payload.objectindex];
		t_vector3 sphere_color = closestsphere.color;
		sphere_color = vector3_multiply_float(color, lightintensity);
		sphere_color = vector3_multiply_float(color, multiplier);
		color = vector3_add(color, sphere_color);

		multiplier *= 0.7f;

		//ray.origin = payload.worldposition + payload.worldnormal * 0.0001f;
		ray.origin = vector3_add(payload.worldposition, vector3_multiply_float(payload.worldnormal, 0.0001f));
		ray.direction = vector3_reflect(ray.direction, payload.worldnormal);
	}
	return (vector4(color.x, color.y, color.z, 1.0f));



	// 	t_vector3 oc = vector3_subtract(ray.origin, sphere[i].center);

	// 	float a = vector3_dot(ray.direction, ray.direction);
	// 	float b = 2.0f * vector3_dot(oc, ray.direction);
	// 	float c = vector3_dot(oc, oc) - sphere[i].radius * sphere[i].radius;

	// 	float det = b * b - 4 * a * c;
	// 	if (det < 0)
	// 		continue;
	// 	float t = (-b - sqrtf(det)) / (2.0f * a);
	// 	if (t < 0)
	// 		continue;
	// 		//t = (-b - sqrtf(det)) / (2.0f * a);
	// 	if (closest > t)
	// 	{
	// 		closest = t;
	// 		closestsphere = &sphere[i];
	// 	}
	// }
	// if (closestsphere == 0)
	// 	return (color);

	// t_vector3 oc = vector3_subtract(ray.origin, closestsphere->center);
	// t_vector3 hit = vector3_add(oc, vector3_multiply_float(ray.direction, closest));
	// t_vector3 normal = vector3_normalize(hit);

	// sphere[i].color = normal;
	// sphere[i].color = vector3_multiply(sphere[i].color, normal);
	// sphere[i].color = vector3_normalize(sphere[i].color);
	// sphere[i].color = vector3_multiply_float(sphere[i].color, 0.5f);
	// sphere[i].color = vector3_add_float(sphere[i].color, 0.5f);

	// closestsphere->color = vector3_multiply_float(closestsphere->color, diffuse);
	// color = vector4(closestsphere->color.x, closestsphere->color.y, closestsphere->color.z, 1.0f);
	// return (color);
}

*/






t_hitpayload ClosestHit(t_ray ray, float hitDistance, int objectIndex, t_scene scene)
{
	t_hitpayload payload;
	payload.HitDistance = hitDistance;
	payload.ObjectIndex = objectIndex;

	const t_sphere closestSphere = scene.sphere[objectIndex];

	t_vector3 origin = vector3_subtract(ray.origin, closestSphere.center);
	payload.WorldPosition = vector3_multiply_float(ray.direction, hitDistance);
	payload.WorldPosition = vector3_add(origin, payload.WorldPosition);
	payload.WorldNormal = vector3_normalize(payload.WorldPosition);
	payload.WorldPosition = vector3_add(payload.WorldPosition, closestSphere.center);

	return payload;
}

t_hitpayload Miss(t_ray ray)
{
	t_hitpayload payload;
	payload.HitDistance = -1.0f;
	return payload;
}

t_hitpayload TraceRay(t_ray ray, t_scene scene)
{
	// (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
	// where
	// a = ray origin
	// b = ray direction
	// r = radius
	// t = hit distance

	int i = -1;


	int closestSphere = -1;
	float hitDistance = FLT_MAX;
	while (++i < scene.nb_sphere)
	{
		const t_sphere sphere = scene.sphere[i];
		//t_vector3 origin = ray.origin - sphere.center;
		t_vector3 origin = vector3_subtract(ray.origin, sphere.center);

		float a = vector3_dot(ray.direction, ray.direction);
		float b = 2.0f * vector3_dot(origin, ray.direction);
		float c = vector3_dot(origin, origin) - sphere.radius * sphere.radius;

		// Quadratic forumula discriminant:
		// b^2 - 4ac

		float discriminant = b * b - 4.0f * a * c;
		if (discriminant < 0.0f)
			continue;

		float closestT = (-b - sqrtf(discriminant)) / (2.0f * a);
		if (closestT > 0.0f && closestT < hitDistance)
		{
			hitDistance = closestT;
			closestSphere = (int)i;
		}
	}

	if (closestSphere < 0)
		return Miss(ray);

	return ClosestHit(ray, hitDistance, closestSphere, scene);
}

t_vector3 RandomInUnitSphere() {
    t_vector3 result;
    float radius, theta, phi;

    radius = (float)rand() / RAND_MAX; // Génère un nombre aléatoire entre 0 et 1
    theta = 2 * M_PI * ((float)rand() / RAND_MAX); // Génère un angle aléatoire entre 0 et 2pi
    phi = acos(2 * ((float)rand() / RAND_MAX) - 1); // Génère un angle aléatoire entre 0 et pi

    result.x = radius * sin(phi) * cos(theta);
    result.y = radius * sin(phi) * sin(theta);
    result.z = radius * cos(phi);

    return result;
}

t_vector4 PerPixel(t_ray ray, t_scene scene)
{
	t_vector3 light;
	t_vector3 contribution = vector3 (1.0f, 1.0f, 1.0f);

	light = vector3(0.0f, 0.0f, 0.0f);
	int bounces = 3;
	while(bounces--)
	{
		t_hitpayload payload = TraceRay(ray, scene);
		if (payload.HitDistance < 0.0f)
		{
			t_vector3 skyColor = vector3(0.6f, 0.7f, 0.9f);
			// t_vector3 skyColor = vector3(0.0f, 0.0f , 0.0f);
			//light = vector3_add(light, vector3_multiply(skyColor, contribution));
			break;
		}
		const t_sphere sphere = scene.sphere[payload.ObjectIndex];


		contribution = vector3_multiply(contribution, sphere.color);
		light = vector3_add(light, scene.material[sphere.material_index].emission);
		// light = vector3_multiply(light, contribution);

		ray.origin = vector3_add(payload.WorldPosition, vector3_multiply_float(payload.WorldNormal, 1.0001f));
		ray.direction = vector3_normalize(vector3_add(payload.WorldNormal, RandomInUnitSphere()));
	}

	return (vector4(light.x, light.y, light.z, 1.0f));
}

/*
t_info touch_sphere(t_ray ray, t_scene scene)
{
	int i;
	float det;
	t_info info;

	i = -1;
	info.did_hit = FALSE;
	info.dst = FLT_MAX;
	while (++i < scene.nb_sphere)
	{
		t_vector3 offset_origin = vector3_subtract(ray.origin, scene.sphere[i].center);

		float a = vector3_dot(ray.direction, ray.direction);
		float b = 2 * vector3_dot( offset_origin, ray.direction);
		float c = vector3_dot(offset_origin, offset_origin) - scene.sphere[i].radius * scene.sphere[i].radius;

		det = b * b - 4 * a * c;
		if (det < 0)
			continue;
		float t = (-b - sqrt(det)) / (2 * a);
		if (t >= 0 && t < info.dst)
		{
			info.dst = t;
			info.index_sphere = i;
			info.did_hit = TRUE;
		}
	}
	if (info.did_hit == TRUE)
	{
		info.hitpoint = vector3_add(ray.origin, vector3_multiply_float(ray.direction, info.dst));
		info.normal = vector3_normalize(vector3_subtract(info.hitpoint, scene.sphere[info.index_sphere].center));
		info.index_material = scene.sphere[info.index_sphere].material_index;
	}
	return (info);


}

t_vector4 PerPixel(t_ray ray, t_scene scene)
{
	t_vector3 light = vector3(0.0f, 0.0f, 0.0f);
	t_vector3 color = vector3(1.0f, 1.0f, 1.0f);
	t_material material[2];

	material[0].color = vector3(1.0f, 1.0f, 0.0f);
	material[0].emission = vector3(0.0f, 1.0f, 1.0f);
	material[1].color = vector3(1.0f, 0.0f, 1.0f);
	material[1].emission = vector3(0.0f, 0.0f, 0.0f);

	t_info info;
	light = vector3(0.0f, 0.0f, 0.0f);
	int bounces = 3;
	while(bounces--)
	{
		info = touch_sphere(ray, scene);
		if (info.did_hit == FALSE)
		{
			// has miss
			//add_sky_color(light, contribution);
			break;
		}
		ray.origin = vector3_multiply_float(info.hitpoint, 1.001f);
		ray.direction = randomspheredirection(info.normal);

		//t_vector3 emitted_light = scene.material[info.index_material].emission;
		t_vector3 emitted_light = material[info.index_material].emission;
		light =	vector3_add(light, vector3_multiply(color, emitted_light));
		//color = vector3_multiply(color, scene.material[info.index_material].color);
		color = vector3_multiply(color, material[info.index_material].color);
	}
	return (vector4(light.x, light.y, light.z, 1.0f));

}*/

/*

t_hitpayload TraceRay(t_ray ray, t_scene scene)
{

}

t_vector4 PerPixel(t_ray ray, t_scene scene)
{
	t_vector3 light;
	t_vector3 contribution = vector3 (1.0f, 1.0f, 1.0f);
	t_payload info;
	light = vector3(0.0f, 0.0f, 0.0f);
	int bounces = 3;
	while(bounces--)
	{
		info = TraceRay(ray, scene);
		if (info.hitdistance < 0.0f)
		{
			// has miss
			add_sky_color(light, contribution);
			break;
		}


}

#define MAX_RAY_DEPTH 3

color Trace(const Ray &ray, int depth)
{
    Object *object = NULL;
    float minDist = INFINITY;
    Point pHit;
    Normal nHit;
    for (int k = 0; k < objects.size(); ++k) {
        if (Intersect(objects[k], ray, &pHit, &nHit)) {
            // ray origin = eye position of the prim ray
            float distance = Distance(ray.origin, pHit);
            if (distance < minDistance) {
                object = objects[i];
                minDistance = distance;
            }
        }
    }
    if (object == NULL)
        return 0;
    // if the object material is glass, split the ray into a reflection
    // and a refraction ray.
    if (object->isGlass && depth < MAX_RAY_DEPTH) {
        // compute the reflection
        Ray reflectionRay;
        reflectionRay = computeReflectionRay(ray.direction, nHit);
        // recurse
        color reflectionColor = Trace(reflectionRay, depth + 1);
        Ray refractioRay;
        refractionRay = computeRefractionRay(
            object->indexOfRefraction,
            ray.direction,
            nHit);
        // recurse
        color refractionColor = Trace(refractionRay, depth + 1);
        float Kr, Kt;
        fresnel(
            object->indexOfRefraction,
            nHit,
            ray.direction,
            &Kr,
            &Kt);
        return reflectionColor * Kr + refractionColor * (1-Kr);
    }
    // object is a diffuse opaque object
    // compute illumination
    Ray shadowRay;
    shadowRay.direction = lightPosition - pHit;
    bool isShadow = false;
    for (int k = 0; k < objects.size(); ++k) {
        if (Intersect(objects[k], shadowRay)) {
            // hit point is in shadow so return
            return 0;
        }
    }
    // point is illuminated
    return object->color * light.brightness;
}

// for each pixel of the image
for (int j = 0; j < imageHeight; ++j) {
    for (int i = 0; i < imageWidth; ++i) {
        // compute primary ray direction
        Ray primRay;
        computePrimRay(i, j, &primRay);
        pixels[i][j] = Trace(primRay, 0);
    }
}
*/

/*
t_vector4 PerPixel(t_ray ray, t_scene scene)
{
	t_vector4 color = vector4(0.0f, 0.0f, 0.0f, 1.0f);
	int bounce = 1;

	while (bounce--)
	{

	}

	return (color);
}*/

/*int checkIntersection(t_vector3 point, t_vector3 direction, t_triangle triangle) {
	t_vector3 edge1, edge2, h, s, q;
	double a, f, u, v;
	edge1 = vector3_subtract(triangle.p[1], triangle.p[0]);
	edge2 = vector3_subtract(triangle.p[2], triangle.p[0]);
	h = vector3_cross(direction, edge2);
	a = edge1.x * h.x + edge1.y * h.y + edge1.z * h.z;
	if (a > -0.00001 && a < 0.00001)
		return 0; // Le vecteur est parallèle au triangle ou se trouve dans le plan du triangle
	f = 1.0 / a;
	s =  vector3_subtract(point, triangle.p[0]);
	u = f * (s.x * h.x + s.y * h.y + s.z * h.z);
	if (u < 0.0 || u > 1.0)
		return 0; // Le vecteur ne traverse pas le triangle
	q = vector3_cross(s, edge1);
	v = f * (direction.x * q.x + direction.y * q.y + direction.z * q.z);
	if (v < 0.0 || u + v > 1.0)
		return 0; // Le vecteur ne traverse pas le triangle
	// Vérification de l'orientation du triangle par rapport au vecteur
	t_vector3 normal = vector3_cross(edge1, edge2);
	t_vector3 vectorToTriangle = vector3_subtract(triangle.p[0], point);
	double dotProduct = normal.x * vectorToTriangle.x + normal.y * vectorToTriangle.y + normal.z * vectorToTriangle.z;
	if (dotProduct < 0)
		return 0;
	// Le vecteur traverse le triangle
	return 1;
}*/
