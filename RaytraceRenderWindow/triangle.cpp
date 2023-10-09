#include "triangle.h"

Triangle::Triangle()
{
    shared_material = nullptr;
}

float Triangle::intersect(Ray& r)
{
    // Calculate normal for the plane the triangle sits on
    auto p0 = Cartesian3(verts[0].x, verts[0].y, verts[0].z);
    auto p1 = Cartesian3(verts[1].x, verts[1].y, verts[1].z);
    auto p2 = Cartesian3(verts[2].x, verts[2].y, verts[2].z);

    auto a = (p1 - p0);
    auto b = (p2 - p0);

    auto n = a.cross(b);
    n = n.unit();

    auto pos = r.GetRayOrigin();
    auto dir = r.GetRayDirecion();

    // check if the ray is paralell to the normal to prevent division by 0 later
    if(dir.dot(n) == 0)
    {
        return -1;
    }
    double t = ((p0 - pos).dot(n)) / (dir.dot(n));

    // calculate intersection point
    auto intersectionPoint = pos + dir * t;

    // vectors from p0 to p1/p2/intersectionPoint
    auto v0 = p1 - p0;
    auto v1 = p2 - p0;
    auto v2 = intersectionPoint - p0;

    // calculate dot products
    double dot00 = v0.dot(v0);
    double dot01 = v0.dot(v1);
    double dot02 = v0.dot(v2);
    double dot11 = v1.dot(v1);
    double dot12 = v1.dot(v2);

    // calculate barycentric coordinates
    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // check if point is in triangle
    if ((u >= 0) && (v >= 0) && (u + v < 1))
        return t;

    return -1;
}
