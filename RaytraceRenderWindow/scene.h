#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include "ThreeDModel.h"
#include "triangle.h"
#include "RenderParameters.h"
#include "Cartesian3.h"
#include "ray.h"
#include "camera.h"



class Scene
{
    struct CollisionInfo
    {
        Triangle tri;
        float t;
    };

public:
    Scene();
    ~Scene();

    std::vector<ThreeDModel>* objects;
    RenderParameters* rp;
    std::vector<Triangle> triangles;
    Material* default_mat;
    Scene(std::vector<ThreeDModel> *texobjs, RenderParameters* renderrp);
    void updateScene();
    Matrix4 GetModelView();

    CollisionInfo ClosestTriangle(Ray& r);

    //Camera* camera;
};

#endif // SCENE_H
