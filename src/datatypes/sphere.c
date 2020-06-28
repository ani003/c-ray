//
//  sphere.c
//  C-ray
//
//  Created by Valtteri Koskivuori on 28/02/2015.
//  Copyright © 2015-2020 Valtteri Koskivuori. All rights reserved.
//

#include "../includes.h"
#include "sphere.h"

#include "../renderer/pathtrace.h"
#include "lightRay.h"

#include "../utils/platform/thread.h"

struct sphere newSphere(struct vector pos, float radius, struct material material) {
	return (struct sphere){pos, radius, material};
}

struct sphere defaultSphere() {
	return (struct sphere){vecZero(), 10.0f, defaultMaterial()};
}

//FIXME: dirty hack
struct sphere newLightSphere(struct vector pos, float radius, struct color color, float intensity) {
	struct sphere newSphere;
	newSphere.pos = pos;
	newSphere.radius = radius;
	newSphere.material = newMaterial(color, 0.0f);
	newSphere.material.emission = colorCoef(intensity, color);
	newSphere.material.type = emission;
	assignBSDF(&newSphere.material);
	return newSphere;
}

//Calculates intersection with a sphere and a light ray
bool intersect(const struct lightRay *ray, const struct sphere *sphere, float *t) {
	yieldThread();

	bool intersects = false;
	
	//Vector dot product of the direction
	float A = vecDot(ray->direction, ray->direction);
	
	//Distance between start of a lightRay and the sphere position
	struct vector distance = vecSub(ray->start, sphere->pos);
	
	float B = 2 * vecDot(ray->direction, distance);
	
	float C = vecDot(distance, distance) - (sphere->radius * sphere->radius);
	
	float trigDiscriminant = B * B - 4 * A * C;
	
	//If discriminant is negative, no real roots and the ray has missed the sphere
	if (trigDiscriminant < 0) {
		intersects = false;
	} else {
		float sqrtOfDiscriminant = sqrtf(trigDiscriminant);
		float t0 = (-B + sqrtOfDiscriminant)/(2);
		float t1 = (-B - sqrtOfDiscriminant)/(2);
		
		//Pick closest intersection
		if (t0 > t1) {
			t0 = t1;
		}
		
		//Verify intersection is larger than 0 and less than the original distance
		if ((t0 > 0.00001f) && (t0 < *t)) {
			*t = t0;
			intersects = true;
		} else {
			intersects = false;
		}
	}
	return intersects;
}

bool rayIntersectsWithSphere(const struct lightRay *ray, const struct sphere *sphere, struct hitRecord *isect) {
	//Pass the distance value to rayIntersectsWithSphere, where it's set
	yieldThread();

	if (intersect(ray, sphere, &isect->distance)) {
		isect->type = hitTypeSphere;
		//Compute normal and store it to isect
		struct vector scaled = vecScale(ray->direction, isect->distance);
		struct vector hitpoint = vecAdd(ray->start, scaled);
		struct vector surfaceNormal = vecSub(hitpoint, sphere->pos);
		float temp = vecDot(surfaceNormal, surfaceNormal);
		if (temp == 0.0) return false; //FIXME: Check this later
		temp = invsqrt(temp);
		isect->surfaceNormal = vecScale(surfaceNormal, temp);
		//Also store hitpoint
		isect->hitPoint = hitpoint;
		return true;
	} else {
		isect->type = hitTypeNone;
		return false;
	}
}
