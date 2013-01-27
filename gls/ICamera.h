#pragma once
#include <GL/glew.h>


class ICamera
{
public:
    virtual ~ICamera(){}
    virtual void apply()=0;
    virtual float *getProjectionMatrix()=0;
    virtual float *getViewMatrix()=0;
};

