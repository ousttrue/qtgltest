#include "IndexedVertexBuffer.h"
#include <sstream>
#include <assert.h>


class FixedString
{
    const char *m_begin;
    const char *m_end;
public:
    FixedString(const char *begin, const char *end)
    : m_begin(begin), m_end(end)
    {
    }

    const char* begin()const{ return m_begin; }
    const char* end()const{ return m_end; }
    size_t size()const{ return m_end-m_begin; }
    char operator[](size_t index)const{ return m_begin[index]; }

    bool operator==(const char *rhs)const
    {
        for(auto it=m_begin; it!=m_end; ++it, ++rhs){
            if(*rhs=='\0'){
                return false;
            }
            if(*it!=*rhs){
                return false;
            }
        }
        return *rhs=='\0';
    }

    bool operator!=(const char *rhs)const
    {
        return !((*this)==rhs);
    }

    int toInt()
    {
        //return atoi(std::string(m_begin, m_end).c_str());
        int num=0;
        for(auto it=m_begin; it!=m_end; ++it){
            num=num*10+((*it)-'0');
        }
        return num;
    }

    float toFloat()
    {
        return atof(std::string(m_begin, m_end).c_str());
    }
};


class Line
{
    FixedString  m_line;
    unsigned int m_pos;
    std::vector<char> m_buffer;

public:
    Line(const char* begin, const char* end)
    : m_line(begin, end), m_pos(0)
    {
    }

    void assign(const char* begin, const char* end)
    {
        m_line=FixedString(begin, end);
        m_pos=0;
    }

    bool operator==(const char *rhs)const
    {
        for(auto it=m_line.begin(); it!=m_line.end(); ++it, ++rhs){
            if(*rhs=='\0'){
                return false;
            }
            if(*it!=*rhs){
                return false;
            }
        }
        return *rhs=='\0';
    }

    bool operator!=(const char *rhs)const
    {
        return !((*this)==rhs);
    }

    FixedString get()
    {
        m_buffer.clear();
        for(; m_pos<m_line.size(); ++m_pos){
            char c=m_line[m_pos];
            if(c==' '){
                ++m_pos;
                break;
            }
            m_buffer.push_back(c);
        }
        if(m_buffer.empty()){
            return FixedString(0, 0);
        }
        return FixedString(&m_buffer[0], &m_buffer[0]+m_buffer.size());
    }
};


class TextReader
{
    char *m_data;
    unsigned int m_size;
    unsigned int m_pos;
    std::vector<char> m_buffer;

public:
    TextReader(char* data, unsigned int size)
    : m_data(data), m_size(size), m_pos(0)
    {
    }

    Line &gets(Line &line)
    {
        m_buffer.clear();
        for(; m_pos<m_size; ++m_pos){
            char c=m_data[m_pos];
            if(c=='\n'){
                ++m_pos;
                break;
            }
            m_buffer.push_back(c);
        }
        if(m_buffer.empty()){
            line.assign(0, 0);
        }
        else{
            line.assign(&m_buffer[0], &m_buffer[0]+m_buffer.size());
        }
        return line;
    }

    bool eof()const
    {
        return m_pos>=m_size;
    }
};


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

