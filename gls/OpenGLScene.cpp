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

void OpenGLScene::addBuffer(std::shared_ptr<IndexedVertexBuffer> buffer)
{
    m_drawables.push_back(buffer);
}

bool OpenGLScene::onMouseLeftDown(int x, int y)
{
    return false;
}

bool OpenGLScene::onMouseMiddleDown(int x, int y)
{
    return false;
}

bool OpenGLScene::onMouseRightDown(int x, int y)
{
    return false;
}

bool OpenGLScene::onMouseLeftUp(int x, int y)
{
    return false;
}

bool OpenGLScene::onMouseMiddleUp(int x, int y)
{
    return false;
}

bool OpenGLScene::onMouseRightUp(int x, int y)
{
    return false;
}

bool OpenGLScene::onMouseMove(int x, int y)
{
    return false;
}

bool OpenGLScene::onMouseWheel(int d)
{
    return false;
}

