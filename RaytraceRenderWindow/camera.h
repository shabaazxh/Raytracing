#ifndef CAMERA_H
#define CAMERA_H

#include "Cartesian3.h"
#include "Homogeneous4.h"
class Camera
{
public:
    Camera();

    Homogeneous4 GetCameraPosition() const { return m_cameraPosition; }
    Homogeneous4 GetCameraDirection() const { return m_cameraDirection; }
    Homogeneous4 GetCameraUp() const { return m_cameraUp; }


private:
    Homogeneous4 m_cameraPosition;
    Homogeneous4 m_cameraDirection;
    Homogeneous4 m_cameraUp;
};

#endif // CAMERA_H
