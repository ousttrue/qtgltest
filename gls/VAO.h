#pragma once
#include <map>
#include <GL/glew.h>
#include <memory>


class VBO;
class VAO
{
    GLuint m_handle;
    std::map<int, std::shared_ptr<VBO>> m_map;

    GLuint m_indexHandle;

public:
    VAO();
    ~VAO();
    GLuint getHandle()const{ return m_handle; }
    bool bind(int channel, std::shared_ptr<VBO> vbo);

    bool bufferData(size_t byte_size, GLuint *data);
    GLuint getIndexHandle()const{ return m_indexHandle; }
};

