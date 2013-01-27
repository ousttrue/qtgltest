#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>


class Shader;
class ShaderProgram
{
    GLuint m_handle;
    std::shared_ptr<Shader> m_vert;
    std::shared_ptr<Shader> m_frag;
public:

    ShaderProgram();
    ~ShaderProgram();
    GLuint getHandle()const{ return m_handle; }
    bool link(std::shared_ptr<Shader> vert, std::shared_ptr<Shader> frag);
    bool setUniform(const char *key, const glm::dmat4 &m);
    bool setUniform(const char *key, const glm::mat4 &m);
};

