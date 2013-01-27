#include "VBO.h"


VBO::VBO()
: m_handle(0)
{
}

VBO::~VBO()
{
    if(m_handle){

        m_handle=0;
    }
}

bool VBO::bufferData(size_t byte_size, float *data)
{
    glGenBuffers(1, &m_handle);
    if(!m_handle){
        return false;
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    glBufferData(GL_ARRAY_BUFFER, byte_size, data, GL_STATIC_DRAW);
    return true;
}

