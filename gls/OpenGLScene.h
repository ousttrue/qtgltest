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

    // backbuffer
    int m_w;
    int m_h;

    // mouse
    bool m_mouseLeft;
    bool m_mouseMiddle;
    bool m_mouseRight;
    int m_mouseX;
    int m_mouseY;

public:
    OpenGLScene();
    ~OpenGLScene();
    void update(int ms);
    void resize(int w, int h);
    std::shared_ptr<Camera> getCamera(){ return m_camera; }
    std::shared_ptr<SceneNode> getRootNode(){ return m_root; }

    void clear();
    void addBuffer(std::shared_ptr<IndexedVertexBuffer> buffer);

    // mouse event
    bool onMouseLeftDown(int x, int y);
    bool onMouseMiddleDown(int x, int y);
    bool onMouseRightDown(int x, int y);
    bool onMouseLeftUp(int x, int y);
    bool onMouseMiddleUp(int x, int y);
    bool onMouseRightUp(int x, int y);
    bool onMouseMove(int x, int y);
    bool onMouseWheel(int d);
};

