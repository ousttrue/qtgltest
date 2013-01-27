#pragma once
#include <memory>
#include <list>


class Camera;
class IndexedVertexBuffer;
class OpenGLScene
{
    std::shared_ptr<Camera> m_camera;

    typedef std::list<std::shared_ptr<IndexedVertexBuffer>> DrawableList;
    DrawableList m_drawables;

public:
    OpenGLScene();
    ~OpenGLScene();
    bool initialize();
    void update(int ms);
    void resize(int w, int h);
    std::shared_ptr<Camera> getCamera(){ return m_camera; }
    DrawableList::iterator begin(){ return m_drawables.begin(); }
    DrawableList::iterator end(){ return m_drawables.end(); }

    void clear(){ m_drawables.clear(); }
    void addBuffer(std::shared_ptr<IndexedVertexBuffer> buffer);
};

