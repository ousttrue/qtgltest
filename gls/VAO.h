#pragma once
#include <map>
#include <GL/glew.h>
#include <memory>


class VBO;
class VAO
{
    GLuint m_handle;
    std::map<int, std::shared_ptr<VBO>> m_map;

public:
    VAO();
    ~VAO();
    GLuint getHandle()const{ return m_handle; }
    bool bind(int channel, std::shared_ptr<VBO> vbo);
};

