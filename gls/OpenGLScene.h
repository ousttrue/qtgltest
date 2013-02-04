#pragma once
#include <memory>
#include <list>


class Camera;
class IndexedVertexBuffer;
class SceneNode;
class OpenGLScene
{
    std::shared_ptr<Camera> m_camera;

    std::shared_ptr<SceneNode> m_root;

public:
    OpenGLScene();
    ~OpenGLScene();
    void update(int ms);
    std::shared_ptr<Camera> getCamera(){ return m_camera; }
    std::shared_ptr<SceneNode> getRootNode(){ return m_root; }
    void addBuffer(std::shared_ptr<IndexedVertexBuffer> buffer);
};

