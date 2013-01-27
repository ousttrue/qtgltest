#include "OpenGLScene.h"
#include <GL/glew.h>
#include "Camera.h"
#include "IndexedVertexBuffer.h"


OpenGLScene::OpenGLScene()
    : m_camera(new Camera)
{
    m_drawables.push_back(IndexedVertexBuffer::CreateTriangle());
    //m_drawables.push_back(IndexedVertexBuffer::CreateCube(0.5f));
}

OpenGLScene::~OpenGLScene()
{
}

void OpenGLScene::update(int ms)
{
}

void OpenGLScene::resize(int w, int h)
{
}

