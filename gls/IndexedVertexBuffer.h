#pragma once
#include <memory>
#include <vector>
#include <string>


struct Vertex
{
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;

    Vertex(){}
    Vertex(float _x, float _y, float _z, float _r, float _g, float _b)
        : x(_x), y(_y), z(_z), r(_r), g(_g), b(_b)
    {
    }
};
class IndexedVertexBuffer
{
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    std::string m_utf8path;

public:
    IndexedVertexBuffer();
    ~IndexedVertexBuffer();

    void pushVertex(const Vertex &v){ m_vertices.push_back(v); }
    void addTriangle(unsigned int i0, unsigned int i1, unsigned int i2)
    {
        m_indices.push_back(i0);
        m_indices.push_back(i1);
        m_indices.push_back(i2);
    }

    unsigned int getIndexCount(unsigned int inex);
    unsigned int getSubMeshCount();

    unsigned int getVerticesByteSize()const
    { 
        return m_vertices.size()*sizeof(Vertex);
    }
    Vertex* getVertexPointer(){
        if(m_vertices.empty()){
            return 0;
        }
        else{
            return &m_vertices[0];
        }
    }

    unsigned int getIndicesByteSize()const
    {
        return m_indices.size()*sizeof(unsigned int);
    }
    unsigned int *getIndexPointer()
    {
        if(m_indices.empty()){
            return 0;
        }
        else{
            return &m_indices[0];
        }
    }

    static std::shared_ptr<IndexedVertexBuffer> CreateTriangle();
    static std::shared_ptr<IndexedVertexBuffer> CreateCube(float size);

    static std::shared_ptr<IndexedVertexBuffer> CreateFromPLY(
            const std::string &utf8path,
            unsigned char *data, unsigned int size);
};

