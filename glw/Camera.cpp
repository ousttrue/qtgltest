#include "Camera.h"
#include <GL/gl.h>


Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::apply()/*override*/
{
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(m_projection);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(m_view);
}

