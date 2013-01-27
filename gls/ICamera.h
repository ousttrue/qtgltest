#pragma once


class ICamera
{
public:
    virtual ~ICamera(){}
    virtual void apply()=0;
};

