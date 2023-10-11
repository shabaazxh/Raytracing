#include "triangle.h"
#include <cmath>

Triangle::Triangle()
{
    shared_material = nullptr;
}

Cartesian3 Triangle::baricentric(Cartesian3 intersection_point)
{

    Cartesian3 normalA = Cartesian3(normals[0].x, normals[0].y, normals[0].z);
    Cartesian3 normalB = Cartesian3(normals[1].x, normals[1].y, normals[1].z);
    Cartesian3 normalC = Cartesian3(normals[2].x, normals[2].y, normals[2].z);

    // input is said to be: intersection point between ray & triangle
    // can pass origin + direction * t which is point of intersection

    auto A = Cartesian3(verts[0].x, verts[0].y, verts[0].z);
    auto B = Cartesian3(verts[1].x, verts[1].y, verts[1].z);
    auto C = Cartesian3(verts[2].x, verts[2].y, verts[2].z);

    // Edges
    auto AB = B - A;
    auto BC = C - B;
    auto CA = A - C;

    auto normal = AB.cross(BC);

    auto AC = C - A;
    auto distanceAB = AB.length();
    auto distanceAC = AC.length();

    auto maxDistance = std::max(distanceAB, distanceAC);

    auto P = intersection_point;


    auto distanceBC = (P-A).cross(BC).length() / BC.length();
    auto distanceCA = (P-B).cross(CA).length() / CA.length();
    auto distance_AB = (P-C).cross(AB).length() / AB.length();

    auto alpha = 1 - distanceBC / maxDistance;
    auto beta  = 1 - distanceCA / maxDistance;
    auto gamma = 1 - distance_AB / maxDistance;

    auto sum = alpha + beta + gamma;
    alpha /= sum;
    beta  /= sum;
    gamma /= sum;

    // interp normal
    Cartesian3 interpNormal = alpha * normalA + beta * normalB + gamma * normalC;

    interpNormal = interpNormal.unit();

//    // distance from A to CB
//    auto cb_edge =  B - C;
//    auto ca_edge =  A - C;

//    auto normal = cb_edge.cross(ca_edge);
//    auto c = normal.dot(B);

//    auto numerator = normal.dot(A);
//    auto mag_squared = normal.dot(normal);
//    auto magnitude = std::sqrt(mag_squared);
//    auto distance = (numerator - c) / magnitude;

    // should be returnining alpha, beta, gamma and calc interp normal later
    Cartesian3 bc = {alpha, beta, gamma};
    //sbc.x = intersection_point.x;

    return bc;
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

//    // check if the ray is paralell to the normal to prevent division by 0 later
//    if(dir.dot(n) == 1e-6)
//    {
//        return -1;
//    }
//    double t = ((p0 - pos).dot(n)) / (dir.dot(n));

//    // calculate intersection point
//    auto intersectionPoint = pos + dir * t;


    /*
        p0 = left
        p1 = right
        p2 = top
    */
    // vectors from p0 to p1/p2/intersectionPoint
    //auto v0 = p1 - p0;
    //auto v1 = p2 - p0;
    //auto v2 = intersectionPoint - p0;

    // find edges of triangle to find normal of triangle
    // use any of the points of the triangle as a point in the plane
    // and the normal at that point as the normal of the plane
    auto edge_1 = p1 - p0;
    auto edge_2 = p2 - p0;
   // auto intersect_point = intersectionPoint - p0;
    auto triangle_normal = edge_1.cross(edge_2);

    // we have a normal and a point to define a plane now
    auto planeNormal = triangle_normal;
    auto point_on_plane = p0;

    // calculate t value for ray whe it hits plane
    // t = n * (p - s) / n * d

    auto denom = planeNormal.dot(dir); // denominator is n * d (n is normal, d is ray dir)
    // if dot product is 0, we did not hit the plane
    // use small epsilon value to handle floating point
    if(denom == 0.0001f)
    {
        return -1;
    }

    float numerator = planeNormal.dot((point_on_plane - pos));
    auto ray_t = numerator / denom;

    auto intersect_plane_point = pos + dir * ray_t;

    // is inside triangle?
    // define triangles edges
    auto e_1 = p1 - p0;
    auto e_2 = p2 - p1;
    auto e_3 = p0 - p2;

    // create vectors to the intersection point
    auto p0_to_point = intersect_plane_point - p0;
    auto p1_to_point = intersect_plane_point - p1;
    auto p2_to_point = intersect_plane_point - p2;

    // peform cross product

    auto p0_vector = e_1.cross(p0_to_point);
    auto p1_vector = e_2.cross(p1_to_point);
    auto p2_vector = e_3.cross(p2_to_point);

    // check if its inside triangle using dot product

    // dot products should return positive value if within tri
    bool p0_test = p0_vector.dot(triangle_normal) > 0.0f;
    bool p1_test = p1_vector.dot(triangle_normal) > 0.0f;
    bool p2_test = p2_vector.dot(triangle_normal) > 0.0f;


    auto result = p0_test && p1_test && p2_test;


    return result ? ray_t : -1;
}

Homogeneous4 Triangle::PhongShading(const Homogeneous4& lightpos, const Homogeneous4& lightcolour, const Ray& ray, const Homogeneous4& barycentricCoords, bool inShadow)
{

    Cartesian3 normalA = Cartesian3(normals[0].x, normals[0].y, normals[0].z);
    Cartesian3 normalB = Cartesian3(normals[1].x, normals[1].y, normals[1].z);
    Cartesian3 normalC = Cartesian3(normals[2].x, normals[2].y, normals[2].z);

    // Interpolated normals
    Cartesian3 normal = barycentricCoords.x * normalA + barycentricCoords.y * normalB +
                          barycentricCoords.z * normalC;

    // normalize normal since it's a direction
    normal = normal.unit();

    // Get hit point from barycentric coords
    Homogeneous4 hitpoint =
        barycentricCoords.x * verts[0] +
        barycentricCoords.y * verts[1] +
        barycentricCoords.z * verts[2];

    Cartesian3 vecHitPoint = {hitpoint.x, hitpoint.y, hitpoint.z};


    // To calculate diffuse, we need lightdir from light to hitpoint
    // negate lightdir because we need a direction vector from light to point
    auto point_to_light = lightpos - hitpoint;
    Cartesian3 lightDir = Cartesian3(point_to_light.x, point_to_light.y, point_to_light.z);
    lightDir = lightDir.unit();
    //lightDir = {-lightDir.x, -lightDir.y, -lightDir.z};

    // Ambient lighting
    Cartesian3 ambient = 0.2f * Cartesian3(lightcolour.x, lightcolour.y, lightcolour.z);

    // Diffuse lightingb
    float diff = std::max(0.0f, normal.dot(lightDir));
    Cartesian3 diffuse = Cartesian3(diff, diff, diff);
    diffuse = diffuse *  Cartesian3(lightcolour.x, lightcolour.y, lightcolour.z);

    // specular lighting
    Cartesian3 specularAmount = Cartesian3(0.5f, 0.5f, 0.5f);
    Cartesian3 viewDirection = ray.GetRayOrigin() - vecHitPoint;
    viewDirection = viewDirection.unit();

    // reflect about the normal
    //lightDir = Cartesian3(-lightDir.x, -lightDir.y, -lightDir.z);
    Cartesian3 reflectionDirection = lightDir.reflect(normal);
    float spec_calc = std::pow(std::max(viewDirection.dot(reflectionDirection), 0.0f), 32);
    Cartesian3 spec = {spec_calc, spec_calc, spec_calc};
    Cartesian3 specular = specularAmount * spec * Cartesian3(lightcolour.x, lightcolour.y, lightcolour.z);

    if(inShadow)
    {
        // means we hit something and we're in shadow
        //ambient = Cartesian3(0.0f, 0.0f, 0.0f);
        diffuse = Cartesian3(0.0f, 0.0f, 0.0f);
        specular = Cartesian3(0.0f, 0.0f, 0.0f);
    }

    auto c = (ambient + diffuse + specular) *  Cartesian3(shared_material->diffuse);


    return {c.x, c.y, c.z, 1.0};
}

