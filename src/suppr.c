/*

float	random_float()
{
	uint result;
	static int seed;

	seed++;
	int state = seed;
	state = state * 747796405 + 2891336453;
	result = (state >> ((state >> 28) + 4)) ^ state * 277803737;
	result = (result >> 22) ^ result;
	return ((result / 4294967295.0) - 0.5f);
}

Floa randomvaluenormaldistribution(int state)
{
	theta = 2 * PI * randomvalue(state)
	r = sqrt(-2 * log(1 - randomvalue(state)))
	return r * cos(theta)
}
float randomspheredirection(vector3 normal, rngstate)
{
	dir = Randomdirection(rngstate)
	return dir * sign(dot(normal, dir))
}

closest hit
{



	normar = random sphere direction

}


while (number of ray per pixel)
{
while number of bounce
{
	find closest hit
	if no hit
	{
		return sky color

	}
	origin = hitpoint
	normal = hitnormal

}
}

Fonction intersection(rayon, sphère)
    // Code d'intersection inchangé
    ...
Fin Fonction
*/

/*
Fonction rayTracing(rayon, scene)
    couleurPixel = couleur de fond

    rebonds = REBONDS_MAX
    tant que rebonds > 0
        réel tPlusProche = infini
        sphèrePlusProche = null

        Pour chaque sphère dans scenes
            réel t = intersection(rayon, sphère)

            Si t > 0 et t < tPlusProche
                tPlusProche = t
                sphèrePlusProche = sphère

        Si sphèrePlusProche est null
            sortie de la boucle  // Pas d'intersection avec les sphères

        pointIntersection = rayon.origine + tPlusProche * rayon.direction
        vecteurNormale = normalize(pointIntersection - sphèrePlusProche.origine)
        couleurPixelSphère = calculerCouleur(pointIntersection, sphèrePlusProche, vecteurNormale)

        Si sphèrePlusProche.emetDeLaLumiere est vrai
            couleurPixel += couleurPixelSphère  // Ajout de la couleur de l'objet émettant de la lumière
            sortie de la boucle  // Sortie après avoir touché un objet émettant de la lumière

        couleurPixel += couleurPixelSphère * sphèrePlusProche.coefficientReflexion  // Ajout de la couleur réfléchie

        rayon.origine = pointIntersection
        rayon.direction = réfléchir(rayon.direction, vecteurNormale)  // Calcul de la réflexion

        intensite = pow(sphèrePlusProche.attenuation, rebonds)  // Diminution d'intensité à chaque rebond
        couleurPixel *= intensite

        rebonds -= 1
    Fin tant que

    retourner couleurPixel
Fin Fonction
*/

/*t_vector3 raytracing(t_ray ray, t_scene scene)
{
    t_vector3 color;
    t_vector3 intersection;
    t_vector3 color_sphere;
    t_sphere *sphere;
    t_sphere sphere_closest;
    int bounce = -1;
    float t_closest = FLT_MAX;
    float t;
    int i = -1;

    color = vector3(0, 0, 0);
    while(++bounce < BOUNCE_MAX)
    {
        while (++i < scene.sphere_count)
        {
            if (sphere[i].intersect(ray, &t) == TRUE && t > 0 && t < t_closest)
            {

                t_closest = t;
                sphere_closest = sphere[i];

            }
        }
        if (sphere_closest == NULL)
            break;

    }
    return (color);

}
*/
