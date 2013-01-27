#include "IndexedVertexBuffer.h"


IndexedVertexBuffer::IndexedVertexBuffer()
{
}

IndexedVertexBuffer::~IndexedVertexBuffer()
{
}

std::shared_ptr<IndexedVertexBuffer> IndexedVertexBuffer::CreateCube(float fSize)
{
    auto buffer=std::make_shared<IndexedVertexBuffer>();
    const float cube_vertices [8][3] = {
        {1.0, 1.0, 1.0}, 
        {1.0, -1.0, 1.0}, 
        {-1.0, -1.0, 1.0}, 
        {-1.0, 1.0, 1.0},
        {1.0, 1.0, -1.0}, 
        {1.0, -1.0, -1.0}, 
        {-1.0, -1.0, -1.0}, 
        {-1.0, 1.0, -1.0} 
    };
    const float cube_vertex_colors [8][3] = {
        {1.0, 1.0, 1.0}, 
        {1.0, 1.0, 0.0}, 
        {0.0, 1.0, 0.0}, 
        {0.0, 1.0, 1.0},
        {1.0, 0.0, 1.0}, 
        {1.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0}, 
        {0.0, 0.0, 1.0} 
    };
    int cube_num_faces = 6;
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

unsigned int IndexedVertexBuffer::getSubMeshCount()
{
    return 1;
}

unsigned int IndexedVertexBuffer::getIndexCount(unsigned int inex)
{
    return m_indices.size();
}

