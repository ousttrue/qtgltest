#include "OpenGLScene.h"
#include <GL/gl.h>
#include "Camera.h"
#include "Cube.h"


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

