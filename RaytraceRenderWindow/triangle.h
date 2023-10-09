#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "Homogeneous4.h"
#include "Material.h"
#include "ray.h"

class Triangle
{
public:
    Triangle();

    Homogeneous4 verts[3];
    Homogeneous4 normals[3];
    Homogeneous4 colors[3];
    Cartesian3 uvs[3];

    Material* shared_material;

    float intersect(Ray& r);


};

#endif // TRIANGLE_H
