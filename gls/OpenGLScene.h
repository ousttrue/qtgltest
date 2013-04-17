#pragma once
#include <memory>
#include <list>


class IndexedVertexBuffer;
class SceneNode;
class Camera;
class OpenGLScene
{
    std::shared_ptr<SceneNode> m_cameraNode;
    std::shared_ptr<SceneNode> m_lightNode;
    std::shared_ptr<SceneNode> m_rootNode;

public:
    OpenGLScene();
    ~OpenGLScene();
    void update(int ms);
    std::shared_ptr<SceneNode> getCameraNode(){ return m_cameraNode; }
	std::shared_ptr<Camera> getCamera(); 
    std::shared_ptr<SceneNode> getLightNode(){ return m_lightNode; }
    std::shared_ptr<SceneNode> getRootNode(){ return m_rootNode; }
    //void addBuffer(std::shared_ptr<IndexedVertexBuffer> buffer);
};

