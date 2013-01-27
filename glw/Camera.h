#include "ICamera.h"


class Camera: public ICamera
{
    double m_projection[16];
    double m_view[16];
public:
    Camera();
    ~Camera();
    void apply()/*override*/;
};

