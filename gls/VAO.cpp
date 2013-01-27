#include "VAO.h"
#include "VBO.h"


VAO::VAO()
: m_handle(0)
{
}

VAO::~VAO()
{
    if(m_handle){
        glDeleteVertexArrays(1, &m_handle);
        m_handle=0;
    }
}

bool VAO::bind(int channel, std::shared_ptr<VBO> vbo)
{
    if(!m_handle){
        glGenVertexArrays(1, &m_handle);
        if(!m_handle){
            return false;
        }
    }
    glBindVertexArray(m_handle);

    glEnableVertexAttribArray(channel);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->getHandle());
    glVertexAttribPointer(channel, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    m_map.insert(std::make_pair(channel, vbo));
    return true;
}

