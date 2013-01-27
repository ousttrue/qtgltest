#pragma once
#include <GL/glew.h>


class Shader
{
    GLuint m_handle;

public:
    Shader();
    ~Shader();
    GLuint getHandle()const{ return m_handle; }
    bool loadFile(GLenum shader_type, const char *path);
};

