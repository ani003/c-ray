//
//  instance.c
//  C-Ray
//
//  Created by Valtteri on 19.10.2019.
//  Copyright © 2019 Valtteri Koskivuori. All rights reserved.
//

#include "../includes.h"
#include "instance.h"

struct instance newInstance() {
	struct instance new;
	new.composite = newTransform();
	return new;
}

//Add instance to scene
void addInstance(struct world *scene, struct instance instance) {
	if (scene->instanceCount == 0) {
		scene->instances = calloc(1, sizeof(struct instance));
	} else {
		scene->instances = realloc(scene->instances, (scene->instanceCount + 1) * sizeof(struct instance));
	}
	scene->instances[scene->instanceCount] = instance;
	scene->instanceCount++;
}

//Add transform to instance by multiplying it into the composite matrix
void addTransform(struct instance *instance, struct transform transform) {
	instance->composite = multiplyTransforms(instance->composite, transform);
}
