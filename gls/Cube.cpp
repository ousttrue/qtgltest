#include "Cube.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VBO.h"
#include "VAO.h"
#include <iostream>


static GLuint initPolyList()
{
    // Colour cube data.
    float fSize = 0.5f;
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

    GLuint polyList = glGenLists (1);
    glNewList(polyList, GL_COMPILE);
    glBegin (GL_QUADS);
    for (long f = 0; f < cube_num_faces; f++){
        for (long i = 0; i < 4; i++) {
            glColor3f (
                    cube_vertex_colors[cube_faces[f][i]][0], 
                    cube_vertex_colors[cube_faces[f][i]][1], 
                    cube_vertex_colors[cube_faces[f][i]][2]);
            glVertex3f(
                    cube_vertices[cube_faces[f][i]][0] * fSize, 
                    cube_vertices[cube_faces[f][i]][1] * fSize, 
                    cube_vertices[cube_faces[f][i]][2] * fSize);
        }
    }
    glEnd ();
    glColor3f (0.0, 0.0, 0.0);
    for (long f = 0; f < cube_num_faces; f++) {
        glBegin (GL_LINE_LOOP);
        for (long i = 0; i < 4; i++){
            glVertex3f(
                    cube_vertices[cube_faces[f][i]][0] * fSize, 
                    cube_vertices[cube_faces[f][i]][1] * fSize, 
                    cube_vertices[cube_faces[f][i]][2] * fSize);
        }
        glEnd ();
    }
    glEndList ();

    return polyList;
}


Cube::Cube()
: m_polyList(0)
{
}

Cube::~Cube()
{
}

static std::shared_ptr<Shader> loadShader(GLenum shader_type, const char *path)
{
    auto shader=std::make_shared<Shader>();
    if(!shader->loadFile(shader_type, path)){
        return std::shared_ptr<Shader>();
    }
    return shader;
}

bool Cube::initialize()
{
    auto vert=loadShader(GL_VERTEX_SHADER, "basic.vert");
    if(!vert){
        // fatal
        return false;
    }

    auto frag=loadShader(GL_FRAGMENT_SHADER, "basic.frag");
    if(!frag){
        // fatal
        return false;
    }

    m_program=std::make_shared<ShaderProgram>();
    if(!m_program->link(vert, frag)){
        // fatal
        return false;
    }

    // VAO
    m_vao=std::make_shared<VAO>();

    // interleaved
    // pos, color
    float interleavedData[]={
        /*pos*/ -0.8f, -0.8f, 0.0f, /*color*/ 1.0f, 0.0f, 0.0f,
        /*pos*/ 0.8f, -0.8f, 0.0f, /*color*/ 0.0f, 1.0f, 0.0f,
        /*pos*/ 0.0f, 0.8f, 0.0f, /*color*/ 0.0f, 0.0f, 1.0f,
    };

    // interleaved single vbo
    auto interleavedBuffer=std::make_shared<VBO>();
    if(!interleavedBuffer->bufferData(sizeof(interleavedData), interleavedData)){
        // fatal
        return false;
    }

    if(!m_vao->bind(0, interleavedBuffer, 6*sizeof(float), 0)){
        // fatal
        return false;
    }
    if(!m_vao->bind(1, interleavedBuffer, 6*sizeof(float), 3*sizeof(float))){
        // fatal
        return false;
    }

    // index buffer
    GLuint indexData[]={
        0, 1, 2,
    };
    if(!m_vao->bufferData(3*sizeof(GLuint), indexData)){
        assert(false);
        // fatal
        return false;
    }

    return true;
}

unsigned int Cube::getSubMeshCount()
{
    return 1;
}

unsigned int Cube::getTriangleCount(unsigned int inex)
{
    return 1;
}

