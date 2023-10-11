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

    Cartesian3 baricentric(Cartesian3 intersection_point);
    Homogeneous4 PhongShading(const Homogeneous4& lightpos, const Homogeneous4& lightcolour, const Ray& ray, const Homogeneous4& barycentricCoords, bool inShadow);


};

#endif // TRIANGLE_H
