//
//  instance.h
//  C-Ray
//
//  Created by Valtteri on 19.10.2019.
//  Copyright © 2015-2019 Valtteri Koskivuori. All rights reserved.
//

#pragma once

#include "scene.h"

struct instance {
	struct transform composite;
	int meshIdx;
};

struct instance newInstance(void);
void addInstance(struct world *scene, struct instance instance);
void addTransform(struct instance *instance, struct transform transform);
