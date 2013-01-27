#include "OpenGLRenderer.h"
#include "OpenGLScene.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>



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

