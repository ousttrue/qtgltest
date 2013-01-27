#pragma once
#include <GL/glew.h>


class VBO
{
    GLuint m_handle;

public:
    VBO();
    ~VBO();
    GLuint getHandle()const{ return m_handle; }
    bool bufferData(size_t byte_size, void *data);
};

