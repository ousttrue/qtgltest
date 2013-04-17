#include "OpenGLScene.h"
#include <GL/glew.h>
#include "Camera.h"
#include "IndexedVertexBuffer.h"
#include "SceneNode.h"


OpenGLScene::OpenGLScene()
    : m_rootNode(new SceneNode("__root__"))
{
    m_cameraNode=std::make_shared<SceneNode>("camera");
    m_rootNode->addChild(m_cameraNode);
	auto camera=std::make_shared<Camera>(m_cameraNode);
	m_cameraNode->setCamera(camera);

    m_lightNode=std::make_shared<SceneNode>("light");
    m_rootNode->addChild(m_lightNode);
    m_lightNode->setPosition(1.0f, 2.0f, 3.0f);

    auto meshNode=std::make_shared<SceneNode>("triangle");
    auto mesh=IndexedVertexBuffer::CreateTriangle();
    meshNode->setMesh(mesh);
    m_rootNode->addChild(meshNode);
}

OpenGLScene::~OpenGLScene()
{
}

void OpenGLScene::update(int ms)
{
}

std::shared_ptr<Camera> OpenGLScene::getCamera()
{
	return m_cameraNode->getCamera();
}
