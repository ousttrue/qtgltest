#include "ShaderProgram.h"
#include "Shader.h"
#include <GL/glew.h>


ShaderProgram::ShaderProgram()
: m_handle(0)
{
}

ShaderProgram::~ShaderProgram()
{
    if(m_handle){
        glDeleteProgram(m_handle);
        m_handle=0;
    }
}

bool ShaderProgram::link(std::shared_ptr<Shader> vert, std::shared_ptr<Shader> frag)
{
    m_handle=glCreateProgram();
    if(!m_handle){
        return false;
    }

    glAttachShader(m_handle, vert->getHandle());
    m_vert=vert;
    glAttachShader(m_handle, frag->getHandle());
    m_frag=frag;

    glLinkProgram(m_handle);

    GLint status;
    glGetProgramiv(m_handle, GL_LINK_STATUS, &status);
    return status!=GL_FALSE;
}

bool ShaderProgram::setUniform(const char *key, const glm::dmat4 &m)
{
    GLuint location=glGetUniformLocation(m_handle, key);
    if(location<0){
        return false;
    }
    glUniformMatrix4dv(location, 1, GL_FALSE, &m[0][0]);
    return true;
}

bool ShaderProgram::setUniform(const char *key, const glm::mat4 &m)
{
    GLuint location=glGetUniformLocation(m_handle, key);
    if(location<0){
        return false;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
    return true;
}

bool ShaderProgram::setUniform(const char *key, const glm::mat3 &m)
{
    GLuint location=glGetUniformLocation(m_handle, key);
    if(location<0){
        return false;
    }
    glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
    return true;
}

bool ShaderProgram::setUniform(const char *key, const glm::vec3 &v)
{
    GLuint location=glGetUniformLocation(m_handle, key);
    if(location<0){
        return false;
    }
    glUniform3f(location, v[0], v[1], v[2]);
    return true;
}

bool ShaderProgram::setUniform(const char *key, const glm::vec4 &v)
{
    GLuint location=glGetUniformLocation(m_handle, key);
    if(location<0){
        return false;
    }
    glUniform4f(location, v[0], v[1], v[2], v[3]);
    return true;
}

