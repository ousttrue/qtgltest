#include "VAO.h"
#include "VBO.h"


VAO::VAO()
: m_handle(0), m_indexHandle(0)
{
}

VAO::~VAO()
{
    if(m_handle){
        glDeleteVertexArrays(1, &m_handle);
        m_handle=0;
    }
    if(m_indexHandle){
        glDeleteVertexArrays(1, &m_indexHandle);
        m_indexHandle=0;
    }
}

bool VAO::bind(int channel, std::shared_ptr<VBO> vbo,
        unsigned int stride, unsigned int offset)
{
    if(!m_handle){
        glGenVertexArrays(1, &m_handle);
        if(!m_handle){
            return false;
        }
        m_vbo=vbo;
    }
    glBindVertexArray(m_handle);

    glEnableVertexAttribArray(channel);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->getHandle());
    glVertexAttribPointer(channel, 3, GL_FLOAT, GL_FALSE, 
            stride, (const GLvoid*)offset);

    return true;
}

bool VAO::bufferData(unsigned int byte_size, GLuint *data)
{
    glGenBuffers(1, &m_indexHandle);
    if(!m_indexHandle){
        return false;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_size, data, GL_STATIC_DRAW);
    return true;
}

