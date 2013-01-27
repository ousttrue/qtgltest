#include "OpenGLRenderer.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>


class OpenGLScene
{
    unsigned int m_polyList;
    double m_projection[16];
    double m_view[16];

public:
    OpenGLScene();
    ~OpenGLScene();
    void update(int ms);
    void render();

private:
    void drawCube();
};


OpenGLScene::OpenGLScene()
    : m_polyList(0)
{
}

OpenGLScene::~OpenGLScene()
{
}

void OpenGLScene::update(int ms)
{
}

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


// Something to look at, draw a rotating colour cube.
void OpenGLScene::drawCube()
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

void OpenGLScene::render()
{
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(m_projection);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(m_view);

    drawCube();
}


//////////////////////////////////////////////////////////////////////////////
OpenGLRenderer::OpenGLRenderer()
: m_scene(new OpenGLScene) 
{
}


OpenGLRenderer::~OpenGLRenderer()
{
}


void OpenGLRenderer::initialize()
{
    glEnable(GL_DEPTH_TEST);
}


void OpenGLRenderer::resize(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}


void OpenGLRenderer::clear()
{
    glDrawBuffer(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}


void OpenGLRenderer::render()
{
    m_scene->render();
}
