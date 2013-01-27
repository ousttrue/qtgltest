#include "ICamera.h"


class Camera: public ICamera
{
    float m_projection[16];
    float m_view[16];
public:
    Camera();
    ~Camera();
    void apply()/*override*/;
    float *getProjectionMatrix()/*override*/{ return m_projection; }
    float *getViewMatrix()/*override*/{ return m_view; }
};

