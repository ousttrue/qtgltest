#include "Drawable.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "Shader.h"
#include "VBO.h"
#include "IndexedVertexBuffer.h"


bool Drawable::initialize(std::shared_ptr<IndexedVertexBuffer> buffer)
{
    // interleaved single vbo
    auto vbo=std::make_shared<VBO>();
    if(!vbo->bufferData(buffer->getVerticesByteSize(), buffer->getVertexPointer())){
        // fatal
        return false;
    }

    // VAO
    m_vao=std::make_shared<VAO>();
    // pos
    if(!m_vao->bind(0, vbo, sizeof(Vertex), 0*sizeof(float))){
        // fatal
        return false;
    }
    // normal
    if(!m_vao->bind(1, vbo, sizeof(Vertex), 3*sizeof(float))){
        // fatal
        return false;
    }
    // rgb
    if(!m_vao->bind(2, vbo, sizeof(Vertex), 6*sizeof(float))){
        // fatal
        return false;
    }

    // index buffer
    if(!m_vao->bufferData(buffer->getIndicesByteSize(), buffer->getIndexPointer())){
        assert(false);
        // fatal
        return false;
    }

    return true;
}

