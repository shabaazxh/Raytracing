#include "triangle.h"
#include <cmath>

Triangle::Triangle()
{
    shared_material = nullptr;
}

// Implementation based on learnings from:
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/barycentric-coordinates.html#:~:text=Barycentric%20coordinates%20are%20also%20known,A%2C%20B%2C%20C).
// https://www.youtube.com/watch?v=ZVgf_W-X8eM&t=291s
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

    // Calculate line from each vertex point to intersection point
    // this will divide the triangle into 3 smaller ones
    auto a_to_point = intersection_point - A;
    auto b_to_point = intersection_point - B;
    auto c_to_point = intersection_point - C;

    // magnitude of cross product vector is equal to the area of the paralellogram formed
    // by the vectors. Divide by half to get area of triangle since triangle is half paralellogram
    float main_triangle_area = normal.length() / 2.0;

    // Calculate the area of each sub-triangle
    float triangle_a_area = (b_to_point.cross(c_to_point)).length() / 2.0;
    float triangle_b_area = (a_to_point.cross(c_to_point)).length() / 2.0;
    float triangle_c_area = (a_to_point.cross(b_to_point)).length() / 2.0;

    // barycentric coordinates
    auto alpha = triangle_a_area / main_triangle_area;
    auto beta = triangle_b_area / main_triangle_area;
    auto gamma = triangle_c_area / main_triangle_area;

    // store alpha, beta, gamma
    Cartesian3 bc = {alpha, beta, gamma};

    return bc;
}

float Triangle::intersect(Ray& r)
{
    auto p0 = Cartesian3(verts[0].x, verts[0].y, verts[0].z);
    auto p1 = Cartesian3(verts[1].x, verts[1].y, verts[1].z);
    auto p2 = Cartesian3(verts[2].x, verts[2].y, verts[2].z);

    // find edges of triangle to find normal of triangle
    auto edge_1 = p1 - p0;
    auto edge_2 = p2 - p0;

    auto n = edge_1.cross(edge_2);
    n = n.unit();

    auto pos = r.GetRayOrigin();
    auto dir = r.GetRayDirecion();

    // use any of the points of the triangle as a point in the plane
    // and the normal at that point as the normal of the plane

    auto triangle_normal = n;

    // we have a normal and a point to define a plane now
    auto planeNormal = triangle_normal;
    auto point_on_plane = p0;

    // calculate t value for ray where it hits plane
    // t = n * (p - s) / n * d

    auto denom = planeNormal.dot(dir); // denominator is n * d (n is normal, d is ray dir)
    // if dot product is 0, we did not hit the plane
    // use small epsilon value to handle floating point
    if(denom == 0.0001f) // maybe use 1e-6?
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
    // because the normal resulting from edge of triangle and vector from point to intersection point cross product
    // will be aligned with triangle's point normal if the point is within the triangle
    bool p0_test = p0_vector.dot(triangle_normal) > 0.0f;
    bool p1_test = p1_vector.dot(triangle_normal) > 0.0f;
    bool p2_test = p2_vector.dot(triangle_normal) > 0.0f;

    // if intersection is within the triangle, all dot products should be greater than 1, therefore all should be true
    auto result = p0_test && p1_test && p2_test;

    // if intersection is true, return t value
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
    auto point_to_light = lightpos - hitpoint;
    Cartesian3 lightDir = Cartesian3(point_to_light.x, point_to_light.y, point_to_light.z);
    lightDir = lightDir.unit();
    //lightDir = {-lightDir.x, -lightDir.y, -lightDir.z};

    // Ambient lighting
    Cartesian3 ambient = 0.8f * Cartesian3(shared_material->ambient);

//    Cartesian3 testDirection = Cartesian3(-1, -1, -1);
//    testDirection = testDirection.unit();
//    testDirection = {-testDirection.x, -testDirection.y, -testDirection.z};

    // Diffuse lighting
    float diff = std::max(normal.dot(lightDir), 0.0f);
    Cartesian3 diffuse = Cartesian3(diff, diff, diff);
    diffuse = Cartesian3(0.5f, 0.5f, 0.5f) * diffuse * Cartesian3(shared_material->diffuse);

    // specular lighting
    Cartesian3 specularAmount = Cartesian3(1.0f, 1.0f, 1.0f);
    Cartesian3 viewDirection = ray.GetRayOrigin() - vecHitPoint;
    viewDirection = viewDirection.unit();

    // reflect about the normal
    lightDir = Cartesian3(-lightDir.x, -lightDir.y, -lightDir.z);
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


    // atten formula: 1.0f / c  + l * d + q * d^2
    // quadratic atten formula = 1.0 / distance^2
    // creates a fall off for the light as the distance between point and light increases
    // https://developer.valvesoftware.com/wiki/Constant-Linear-Quadratic_Falloff#:~:text=Quadratic%20Attenuation,-This%20is%20a&text=Mathematically%2C%20the%20attenuation%20of%20a,very%20sharp%20drop%20in%20light.
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    float distance =
        (Cartesian3(lightpos.x, lightpos.y, lightpos.z) -
                     Cartesian3(hitpoint.x, hitpoint.y, hitpoint.z)).length();
    //float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
    float attenuation = 1.0f / (distance * distance);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular*= attenuation;


    auto c = (ambient + diffuse + specular) *  Cartesian3(shared_material->diffuse);

    return {c.x, c.y, c.z, 1.0};
}

