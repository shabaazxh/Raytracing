#include "scene.h"
#include <limits>
Scene::Scene()
{
}

Scene::~Scene()
{
    delete default_mat;
}

float CheckIntersection(Triangle& triangle, Ray& ray)
{
    return triangle.intersect(ray);
}

Scene::CollisionInfo Scene::ClosestTriangle(Ray& r)
{
    Scene::CollisionInfo ci;
    ci.t = std::numeric_limits<float>::max();

    for(unsigned int i = 0; i < triangles.size(); i++)
    {
        auto intersect = CheckIntersection(triangles[i], r);
        if(ci.t > intersect && intersect >= 0)
        {
            ci.t = intersect;
            ci.tri = triangles[i];
        }
    }
    return ci;
}

Matrix4 Scene::GetModelView()
{
    Matrix4 modelViewMatrix;
    modelViewMatrix.SetIdentity();

    auto pos = ray->GetRayOrigin();
    auto dir = ray->GetRayDirecion();
    auto up = Cartesian3(0.0f, 1.0f, 0.0);

    auto right = dir.cross(up);
    auto rightNormalized = right.unit();

    dir = dir.unit();
    // recalculate true up direction
    up = right.cross(dir);

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
    modelViewMatrix[3][2] = -pos.z;

    // Define the model matrix. This will move the world around
    Matrix4 modelMatrix;
    modelMatrix.SetIdentity();
    modelMatrix.SetTranslation({0.0f, 0.0f, 0.0f});

    return modelViewMatrix * modelMatrix;

}

Scene::Scene(std::vector<ThreeDModel> *texobjs, RenderParameters* renderrp, Ray* ray)
{
    this->ray = ray;
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
    // Transform lights to view-space
    for(unsigned int i = 0; i < rp->lights.size(); i++)
    {
        auto currentPos = rp->lights[i]->GetPositionCenter();
        auto modelView = GetModelView();
        auto newpos = modelView * currentPos;
        rp->lights[i]->SetPosition( newpos );
    }

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
                                                  obj.vertices[obj.faceVertices[face][faceVertex]].z, 1.0f);

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

                if(obj.material == nullptr)
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
