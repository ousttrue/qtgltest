#pragma once
#include <map>
#include <GL/glew.h>
#include <memory>


class VBO;
class VAO
{
    GLuint m_handle;

    // interleaved
    std::shared_ptr<VBO> m_vbo;

    GLuint m_indexHandle;

public:
    VAO();
    ~VAO();
    GLuint getHandle()const{ return m_handle; }
    bool bind(int channel, std::shared_ptr<VBO> vbo,
            unsigned int stride, unsigned int offset);

    bool bufferData(unsigned int byte_size, GLuint *data);
    GLuint getIndexHandle()const{ return m_indexHandle; }
};

