#include "OpenGLScene.h"
#include <GL/glew.h>
#include "Camera.h"
#include "IndexedVertexBuffer.h"
#include "SceneNode.h"


OpenGLScene::OpenGLScene()
    : m_camera(new Camera), m_root(new SceneNode("__root__"))
{
    m_root->addChild("triangle", IndexedVertexBuffer::CreateTriangle());
    //m_drawables.push_back(IndexedVertexBuffer::CreateCube(0.5f));
}

OpenGLScene::~OpenGLScene()
{
}

void OpenGLScene::update(int ms)
{
}

void OpenGLScene::clear()
{
    m_root->clear();
}


