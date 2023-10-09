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
        return false;
    }
    double t = ((p0 - pos).dot(n)) / (dir.dot(n));

    //auto intersectionPoint = pos + dir * multiplier;

    // from p0 to intersection point
    //auto f = p0 - intersectionPoint;

    return t;
}
