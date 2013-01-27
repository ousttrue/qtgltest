#pragma once
#include "IDrawable.h"
#include <memory>


class ShaderProgram;
class VAO;
class Cube: public IDrawable
{
    unsigned int m_polyList;

    std::shared_ptr<ShaderProgram> m_program;
    std::shared_ptr<VAO> m_vao;

public:
    Cube();
    ~Cube();
    bool initialize()/*override*/;
    std::shared_ptr<ShaderProgram> getProgram()/*override*/{ return m_program; }
    std::shared_ptr<VAO> getVAO()/*override*/{ return m_vao; }
    unsigned int getTriangleCount(unsigned int inex)/*override*/;
    unsigned int getSubMeshCount()/*override*/;
};

