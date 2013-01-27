#pragma once


class Camera
{
    float m_projection[16];
    float m_view[16];
public:
    Camera();
    ~Camera();
    float *getProjectionMatrix()/*override*/{ return m_projection; }
    float *getViewMatrix()/*override*/{ return m_view; }
};

