#pragma once
#include <memory>
#include <vector>


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
class ShaderProgram;
class VAO;
class IndexedVertexBuffer
{
    std::shared_ptr<ShaderProgram> m_program;
    std::shared_ptr<VAO> m_vao;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

public:
    IndexedVertexBuffer();
    ~IndexedVertexBuffer();
    void setShader(std::shared_ptr<ShaderProgram> shader)/*override*/;
    bool initialize()/*override*/;
    std::shared_ptr<ShaderProgram> getProgram()/*override*/{ return m_program; }
    std::shared_ptr<VAO> getVAO()/*override*/{ return m_vao; }
    unsigned int getIndexCount(unsigned int inex)/*override*/;
    unsigned int getSubMeshCount()/*override*/;

    void pushVertex(const Vertex &v){ m_vertices.push_back(v); }
    void addTriangle(unsigned int i0, unsigned int i1, unsigned int i2)
    {
        m_indices.push_back(i0);
        m_indices.push_back(i1);
        m_indices.push_back(i2);
    }

    static std::shared_ptr<IndexedVertexBuffer> CreateTriangle();
    static std::shared_ptr<IndexedVertexBuffer> CreateCube(float size);
};

