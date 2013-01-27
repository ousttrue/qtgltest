#include "IndexedVertexBuffer.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VBO.h"
#include "VAO.h"
#include <iostream>



IndexedVertexBuffer::IndexedVertexBuffer()
{
}

IndexedVertexBuffer::~IndexedVertexBuffer()
{
}

void IndexedVertexBuffer::setShader(std::shared_ptr<ShaderProgram> shader)
{
    m_program=shader;
}

bool IndexedVertexBuffer::initialize()
{
    if(m_vertices.empty()){
        return false;
    }
    if(m_indices.empty()){
        return false;
    }

    // interleaved single vbo
    auto vbo=std::make_shared<VBO>();
    if(!vbo->bufferData(m_vertices.size()*sizeof(Vertex), &m_vertices[0])){
        // fatal
        return false;
    }

    // VAO
    m_vao=std::make_shared<VAO>();
    if(!m_vao->bind(0, vbo, 6*sizeof(float), 0)){
        // fatal
        return false;
    }
    if(!m_vao->bind(1, vbo, 6*sizeof(float), 3*sizeof(float))){
        // fatal
        return false;
    }

    // index buffer
    if(!m_vao->bufferData(m_indices.size()*sizeof(GLuint), &m_indices[0])){
        assert(false);
        // fatal
        return false;
    }

    return true;
}

unsigned int IndexedVertexBuffer::getSubMeshCount()
{
    return 1;
}

unsigned int IndexedVertexBuffer::getIndexCount(unsigned int inex)
{
    return m_indices.size();
}

std::shared_ptr<IndexedVertexBuffer> IndexedVertexBuffer::CreateCube(float fSize)
{
    auto buffer=std::make_shared<IndexedVertexBuffer>();
    const GLfloat cube_vertices [8][3] = {
        {1.0, 1.0, 1.0}, 
        {1.0, -1.0, 1.0}, 
        {-1.0, -1.0, 1.0}, 
        {-1.0, 1.0, 1.0},
        {1.0, 1.0, -1.0}, 
        {1.0, -1.0, -1.0}, 
        {-1.0, -1.0, -1.0}, 
        {-1.0, 1.0, -1.0} 
    };
    const GLfloat cube_vertex_colors [8][3] = {
        {1.0, 1.0, 1.0}, 
        {1.0, 1.0, 0.0}, 
        {0.0, 1.0, 0.0}, 
        {0.0, 1.0, 1.0},
        {1.0, 0.0, 1.0}, 
        {1.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0}, 
        {0.0, 0.0, 1.0} 
    };
    GLint cube_num_faces = 6;
    const short cube_faces [6][4] = {
        {3, 2, 1, 0}, 
        {2, 3, 7, 6}, 
        {0, 1, 5, 4}, 
        {3, 0, 4, 7}, 
        {1, 2, 6, 5}, 
        {4, 5, 6, 7} 
    };
    for(size_t i=0; i<8; ++i){
        buffer->pushVertex(Vertex(
                    cube_vertices[i][0] * fSize,
                    cube_vertices[i][1] * fSize,
                    cube_vertices[i][2] * fSize,
                    cube_vertex_colors[i][0],
                    cube_vertex_colors[i][1],
                    cube_vertex_colors[i][2]
                    ));
    }
    for(size_t i=0; i<cube_num_faces; ++i){
        buffer->addTriangle(
                cube_faces[i][0],
                cube_faces[i][1],
                cube_faces[i][2]);
        buffer->addTriangle(
                cube_faces[i][2],
                cube_faces[i][3],
                cube_faces[i][0]);
    }
    return buffer;
}

std::shared_ptr<IndexedVertexBuffer> IndexedVertexBuffer::CreateTriangle()
{
    auto buffer=std::make_shared<IndexedVertexBuffer>();
    buffer->pushVertex(Vertex(
                /*pos*/ -0.8f, -0.8f, 0.0f, /*color*/ 1.0f, 0.0f, 0.0f
                ));
    buffer->pushVertex(Vertex(
                /*pos*/ 0.8f, -0.8f, 0.0f, /*color*/ 0.0f, 1.0f, 0.0f
                ));
    buffer->pushVertex(Vertex(
                /*pos*/ 0.0f, 0.8f, 0.0f, /*color*/ 0.0f, 0.0f, 1.0f
                ));
    buffer->addTriangle(0, 1, 2);
    return buffer;
}

