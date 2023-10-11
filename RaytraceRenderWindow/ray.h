#ifndef RAY_H
#define RAY_H

#include "Cartesian3.h"

class Ray
{
public:
    Ray(Cartesian3 og, Cartesian3 dir);

    void SetDirection(const Cartesian3& dir) { direction = dir; }

    Cartesian3 GetRayOrigin() const { return origin;}
    Cartesian3 GetRayDirecion() const { return direction; }

private:
    Cartesian3 origin;
    Cartesian3 direction;
};

#endif // RAY_H
