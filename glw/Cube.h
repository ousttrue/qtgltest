#pragma once
#include "IDrawable.h"


class Cube: public IDrawable
{
    unsigned int m_polyList;

public:
    Cube();
    ~Cube();
    void draw()/*override*/;
};

