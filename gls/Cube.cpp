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

    // create vbo
    {
        auto positionBuffer=std::make_shared<VBO>();
        float positionData[]={
            -0.8f, -0.8f, 0.0f,
            0.8f, -0.8f, 0.0f,
            0.0f, 0.8f, 0.0f,
        };
        if(!positionBuffer->bufferData(9*sizeof(float), positionData)){
            // fatal
            return false;
        }
        if(!m_vao->bind(0, positionBuffer)){
            // fatal
            return false;
        }
    }

    {
        auto colorBuffer=std::make_shared<VBO>();
        float colorData[]={
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
        };
        if(!colorBuffer->bufferData(9*sizeof(float), colorData)){
            // fatal
            return false;
        }
        if(!m_vao->bind(1, colorBuffer)){
            // fatal
            return false;
        }
    }


std::cout << "initialized !" << std::endl;

    return true;
}

void Cube::draw()
{
    if (!m_polyList) {
        m_polyList=initPolyList();
    }

    glPushMatrix(); // Save world coordinate system.
    glTranslatef(0.0, 0.0, 0.5); // Place base of cube on marker surface.
    //glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
    glDisable(GL_LIGHTING);	// Just use colours.
    glCallList(m_polyList);	// Draw the cube.
    glPopMatrix();	// Restore world coordinate system.
}

int Cube::getTriangleCount()
{
    return 3;
}
