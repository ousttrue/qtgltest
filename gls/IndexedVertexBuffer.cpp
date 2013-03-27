#include "IndexedVertexBuffer.h"
#include <sstream>
#include <assert.h>
#include "FixedString.h"
#include "Line.h"
#include "TextReader.h"
#include "BinaryReader.h"


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
    size_t cube_num_faces = 6;
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
                    0, 0, 0,
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

unsigned int IndexedVertexBuffer::getSubMeshCount()
{
    return 1;
}

unsigned int IndexedVertexBuffer::getIndexCount(unsigned int inex)
{
    return m_indices.size();
}

std::shared_ptr<IndexedVertexBuffer> IndexedVertexBuffer::CreateTriangle()
{
    auto buffer=std::make_shared<IndexedVertexBuffer>();
    buffer->pushVertex(Vertex(
                /*pos*/ -0.8f, -0.8f, 0.0f, 
                /*normal*/ 0, 0, 1.0f,
                /*color*/ 1.0f, 0.0f, 0.0f
                ));
    buffer->pushVertex(Vertex(
                /*pos*/ 0.8f, -0.8f, 0.0f, 
                /*normal*/ 0, 0, 1.0f,
                /*color*/ 0.0f, 1.0f, 0.0f
                ));
    buffer->pushVertex(Vertex(
                /*pos*/ 0.0f, 0.8f, 0.0f, 
                /*normal*/ 0, 0, 1.0f,
                /*color*/ 0.0f, 0.0f, 1.0f
                ));
    buffer->addTriangle(0, 1, 2);
    return buffer;
}

std::shared_ptr<IndexedVertexBuffer> IndexedVertexBuffer::CreateFromPMD(
        const std::string &utf8path,
        char *data, unsigned int size)
{
    auto buffer=std::make_shared<IndexedVertexBuffer>();

    BinaryReader reader(data, size);

    std::string sig=reader.getString(3); 
    if(sig!="Pmd"){
        return std::shared_ptr<IndexedVertexBuffer>();
    }

    float version=reader.get<float>();
    if(version!=1.0f){
        return std::shared_ptr<IndexedVertexBuffer>();
    }

    std::string name=reader.getString(20);
    std::string comment=reader.getString(256);

    unsigned int vertexCount=reader.get<unsigned int>();
    for(unsigned int i=0; i<vertexCount; ++i){
        float x=reader.get<float>();
        float y=reader.get<float>();
        float z=reader.get<float>();
        float nx=reader.get<float>();
        float ny=reader.get<float>();
        float nz=reader.get<float>();
        float u=reader.get<float>();
        float v=reader.get<float>();
        unsigned short b0=reader.get<unsigned short>();
        unsigned short b1=reader.get<unsigned short>();
        unsigned char w0=reader.get<unsigned char>();
        unsigned char flag=reader.get<unsigned char>();

        buffer->pushVertex(Vertex(
			x, y, z,
			nx, ny, nz,
			0, 0, 0));
    }

    unsigned int indexCount=reader.get<unsigned int>();
    for(unsigned int i=0; i<indexCount; ++i){
        unsigned short index=reader.get<unsigned short>();
        buffer->pushIndex(index);
    }

    return buffer;
}

std::shared_ptr<IndexedVertexBuffer> IndexedVertexBuffer::CreateFromPLY(
        const std::string &utf8path,
        char *data, unsigned int size)
{
    auto buffer=std::make_shared<IndexedVertexBuffer>();

    TextReader reader(data, size);

    Line line(0, 0);
    if(reader.gets(line)!="ply"){
        return std::shared_ptr<IndexedVertexBuffer>();
    }

    if(reader.gets(line)!="format ascii 1.0"){
        return std::shared_ptr<IndexedVertexBuffer>();
    }

    unsigned int vertexCount=0;
    unsigned int faceCount=0;

    while(!reader.eof()){
        reader.gets(line);
        if(line=="end_header"){
            break;
        }
        auto key=line.get();
        if(key=="element"){
            auto subkey=line.get();
            if(subkey=="vertex"){
                vertexCount=line.get().toInt();
            }
            else if(subkey=="face"){
                faceCount=line.get().toInt();
            }
            else{
                // unknown
            }
        }
    }

    for(unsigned int i=0; i<vertexCount; ++i){
        reader.gets(line);
        float x=line.get().toFloat();
        float y=line.get().toFloat();
        float z=line.get().toFloat();
        buffer->pushVertex(Vertex(x, y, z));
    }

    for(unsigned int i=0; i<faceCount; ++i){
        reader.gets(line);
        int faceIndexCount=line.get().toInt();
        assert(faceIndexCount==3);
        int i0=line.get().toInt();
        int i1=line.get().toInt();
        int i2=line.get().toInt();
        buffer->addTriangle(i0, i1, i2);
    }

    return buffer;
}

