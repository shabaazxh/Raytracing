#include "scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    delete default_mat;
}

bool CheckIntersection(Triangle& triangle, Ray& ray)
{
    // Calculate normal for the plane the triangle sits on
    auto p0 = Cartesian3(triangle.verts[0].x, triangle.verts[0].y, triangle.verts[0].z);
    auto p1 = Cartesian3(triangle.verts[1].x, triangle.verts[1].y, triangle.verts[1].z);;
    auto p2 = Cartesian3(triangle.verts[2].x, triangle.verts[2].y, triangle.verts[2].z);;

    auto a = (p1 - p0);
    auto b = (p2 - p0);

    auto n = a.cross(b);
    n = n.unit();



    return false;
}

Scene::CollisionInfo Scene::ClosestTriangle(Ray& r)
{
    Scene::CollisionInfo ci;
    ci.t = r.GetRayOrigin().x;

    for(unsigned int i = 0; i < triangles.size(); i++)
    {
        auto intersect = CheckIntersection(triangles[i], r);
    }
    return ci;
}

Matrix4 Scene::GetModelView()
{
    Matrix4 modelViewMatrix;
    modelViewMatrix.SetIdentity();

    auto pos = Cartesian3(0.0, 0.0, 1.0);
    auto dir = Cartesian3(0.0f, 0.0f, -10.0f);
    auto up = Cartesian3(0.0f, 1.0f, 0.0);

    auto right = dir.cross(up);
    auto rightNormalized = right.unit();
    dir = dir.unit();
    up = up.unit();

    // Set the rotation part of the matrix
    modelViewMatrix[0][0] = rightNormalized.x;
    modelViewMatrix[1][0] = rightNormalized.y;
    modelViewMatrix[2][0] = rightNormalized.z;

    modelViewMatrix[0][1] = up.x;
    modelViewMatrix[1][1] = up.y;
    modelViewMatrix[2][1] = up.z;

    modelViewMatrix[0][2] = -dir.x;
    modelViewMatrix[1][2] = -dir.y;
    modelViewMatrix[2][2] = -dir.z;

    // Set the translation part of the matrix
    modelViewMatrix[3][0] = -pos.x;
    modelViewMatrix[3][1] = -pos.y;
    modelViewMatrix[3][2] = pos.z;

    return modelViewMatrix;

}

Scene::Scene(std::vector<ThreeDModel> *texobjs, RenderParameters* renderrp)
{
    objects = texobjs;
    rp = renderrp;
    Cartesian3 ambient = Cartesian3(0.5f, 0.5f, 0.5f);
    Cartesian3 diffuse = Cartesian3(0.5f, 0.5f, 0.5f);
    Cartesian3 specular = Cartesian3(0.5f, 0.5f, 0.5f);
    Cartesian3 emissive = Cartesian3(0,0,0);
    float shininess = 1.0f;
    default_mat = new Material(ambient, diffuse, specular, emissive, shininess);
}

void Scene::updateScene()
{
    triangles.clear();
    for(int i = 0; i < int(objects->size()); i++)
    {
        typedef unsigned int uint;
        ThreeDModel obj = objects->at(uint(i));
        for(uint face = 0; face < obj.faceVertices.size(); face++)
        {
            for(uint triangle = 0; triangle < obj.faceVertices[face].size()-2; triangle++)
            {
                Triangle t;
                for(uint vertex = 0; vertex < 3; vertex++)
                {
                    uint faceVertex = 0;
                    if(vertex != 0)
                    {
                        faceVertex = triangle + vertex;
                    }

                    Homogeneous4 v = Homogeneous4(obj.vertices[obj.faceVertices[face][faceVertex]].x,
                                                  obj.vertices[obj.faceVertices[face][faceVertex]].y,
                                                  obj.vertices[obj.faceVertices[face][faceVertex]].z, 0.0f);

                    auto modelView = GetModelView();
                    v = modelView * v;
                    t.verts[vertex] = v;

                    Homogeneous4 n = Homogeneous4(obj.normals[obj.faceNormals[face][faceVertex]].x,
                                                  obj.normals[obj.faceNormals[face][faceVertex]].y,
                                                  obj.normals[obj.faceNormals[face][faceVertex]].z, 0.0f);
                    t.normals[vertex] = n;

                    Cartesian3 tex = Cartesian3(obj.textureCoords[obj.faceTexCoords[face][faceVertex]].x,
                                                obj.textureCoords[obj.faceTexCoords[face][faceVertex]].y, 0.0f);

                    t.uvs[vertex] = tex;
                    t.colors[vertex] = Cartesian3(0.7f, 0.7f, 0.7f);

                }

                if(obj.material = nullptr)
                {
                    t.shared_material = default_mat;
                } else {
                    t.shared_material = obj.material;
                }

                triangles.push_back(t);
            }


        }

    }
}
