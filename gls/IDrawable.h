#pragma once
#include <memory>
#include <GL/glew.h>


class ShaderProgram;
class VAO;
class IDrawable
{
public:
    virtual ~IDrawable(){}
    virtual bool initialize()=0;
    //virtual void draw()=0;
    virtual std::shared_ptr<ShaderProgram> getProgram()=0;
    virtual std::shared_ptr<VAO> getVAO()=0;
    virtual unsigned int getSubMeshCount()=0;
    unsigned virtual int getTriangleCount(unsigned int index)=0;
};

