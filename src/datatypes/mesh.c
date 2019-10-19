//
//  mesh.c
//  C-ray
//
//  Created by Valtteri Koskivuori on 27/04/2017.
//  Copyright © 2015-2019 Valtteri Koskivuori. All rights reserved.
//

#include "../includes.h"
#include "mesh.h"

#include "../acceleration/kdtree.h"
#include "../datatypes/vertexbuffer.h"

void freeMesh(struct mesh *mesh) {
	if (mesh->name) {
		free(mesh->name);
	}
	if (mesh->tree) {
		freeTree(mesh->tree);
		free(mesh->tree);
	}
	if (mesh->materials) {
		for (int i = 0; i < mesh->materialCount; i++) {
			freeMaterial(&mesh->materials[i]);
		}
		free(mesh->materials);
	}
}
