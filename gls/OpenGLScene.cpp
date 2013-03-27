#include "OpenGLScene.h"
#include <GL/glew.h>
#include "Camera.h"
#include "IndexedVertexBuffer.h"
#include "SceneNode.h"


OpenGLScene::OpenGLScene()
    : m_root(new SceneNode("__root__"))
{
    auto cameraNode=std::make_shared<SceneNode>("camera");
    m_root->addChild(cameraNode);
    m_camera=std::make_shared<Camera>(cameraNode);

    auto lightNode=std::make_shared<SceneNode>("light");
    m_root->addChild(lightNode);

    auto meshNode=std::make_shared<SceneNode>("triangle");
    auto mesh=IndexedVertexBuffer::CreateTriangle();
    meshNode->setMesh(mesh);
    m_root->addChild(meshNode);
}

OpenGLScene::~OpenGLScene()
{
}

void OpenGLScene::update(int ms)
{
}

