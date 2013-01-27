#include "OpenGLRenderer.h"
#include "OpenGLScene.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
//#include <GL/gl.h>


OpenGLRenderer::OpenGLRenderer(std::shared_ptr<OpenGLScene> scene)
: m_scene(scene) 
{
}


OpenGLRenderer::~OpenGLRenderer()
{
}


void OpenGLRenderer::initialize()
{
	GLenum err=glewInit();
	if(err!=GLEW_OK){
		// fatal
        return;
	}

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

