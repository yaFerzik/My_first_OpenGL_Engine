#ifndef MODELUTILS_H
#define MODELUTILS_h

#include "Model.h"

#define PI 3.14159265359

Mesh createFlatPanelMesh(float width, float height, int nodesW, int nodesH, Texture& tex);

Mesh createUVSphereMesh(float r, int numStacks, int numSlices, Texture& tex);

#endif
