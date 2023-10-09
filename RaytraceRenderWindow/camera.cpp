#include "camera.h"

Camera::Camera()
{
    m_cameraPosition = Homogeneous4(0.0f, 0.0f, 1.0, 0.0);
    m_cameraDirection = Homogeneous4(0.0f, 0.0f, -1.0f, 0.0);
    m_cameraUp = Homogeneous4(0.0f, 1.0f, 0.0, 0.0);
}
