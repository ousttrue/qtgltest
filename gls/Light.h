#pragma once
#include <memory>
#include "Vec3.h"

enum LIGHT_TYPE {
    LIGHT_DIRECTIONAL,
    LIGHT_POINT,
};

class Light
{
    LIGHT_TYPE m_type;
    Vec3 m_diffuse;

public:
    Light(LIGHT_TYPE type=LIGHT_DIRECTIONAL);
    ~Light();

    void setDiffuse(const Vec3 &diffuse){ m_diffuse=diffuse; }
    const Vec3 &getDiffuse()const{ return m_diffuse; }
};

