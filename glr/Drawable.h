#pragma once
#include <memory>


class ShaderProgram;
class VAO;
class IndexedVertexBuffer;
class Drawable
{
    std::shared_ptr<ShaderProgram> m_program;
    std::shared_ptr<VAO> m_vao;
public:
    bool initialize(std::shared_ptr<IndexedVertexBuffer> buffer);
    void setShader(std::shared_ptr<ShaderProgram> shader){ m_program=shader; }
    std::shared_ptr<ShaderProgram> getProgram(){ return m_program; }
    std::shared_ptr<VAO> getVAO(){ return m_vao; }
};

