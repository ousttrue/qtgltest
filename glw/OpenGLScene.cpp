#include "OpenGLScene.h"
#include <GL/gl.h>
#include <GL/glu.h>


class ICamera
{
public:
    virtual ~ICamera(){}
    virtual void apply()=0;
};


class Camera: public ICamera
{
    double m_projection[16];
    double m_view[16];
public:
    Camera()
    {
    }

    ~Camera()
    {
    }

    void apply()/*override*/
    {
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixd(m_projection);

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixd(m_view);
    }
};



class IDrawable
{
public:
    virtual ~IDrawable(){}
    virtual void draw()=0;
};


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

class Cube: public IDrawable
{
    unsigned int m_polyList;

public:
    Cube()
    : m_polyList(0)
    {
    }

    ~Cube()
    {
    }

    void draw()/*override*/
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
};


OpenGLScene::OpenGLScene()
    : m_camera(new Camera)
{
    m_drawables.push_back(std::make_shared<Cube>());
}

OpenGLScene::~OpenGLScene()
{
}

void OpenGLScene::update(int ms)
{
}


void OpenGLScene::render()
{
    m_camera->apply();
    for(auto it=m_drawables.begin(); it!=m_drawables.end(); ++it){
        (*it)->draw();
    }
}

