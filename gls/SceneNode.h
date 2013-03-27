#pragma once
#include <string>
#include <memory>
#include <list>
#include <vector>


class IndexedVertexBuffer;
class Camera;
class Light;
class SceneNode: public std::enable_shared_from_this<SceneNode>
{
    std::string m_name;
    std::weak_ptr<SceneNode> m_parent;
    typedef std::vector<std::shared_ptr<SceneNode>> SceneNodeList;
    SceneNodeList m_children;

    std::shared_ptr<IndexedVertexBuffer> m_buffer;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Light> m_light;

public:
    SceneNode(const std::string &name);
    std::string name()const{ return m_name; }
    std::shared_ptr<SceneNode> addChild(const std::shared_ptr<SceneNode> &node);

    // mesh
    void setMesh(const std::shared_ptr<IndexedVertexBuffer> &buffer){ m_buffer=buffer; }
    std::shared_ptr<IndexedVertexBuffer> getMesh()const{ return m_buffer; }

    // camera
    void setCamera(const std::shared_ptr<Camera> &camera){ m_camera=camera; }
    std::shared_ptr<Camera> getCamera()const{ return m_camera; }

    // light
    void setLight(const std::shared_ptr<Light> &light){ m_light=light; }
    std::shared_ptr<Light> getLight()const{ return m_light; }

    SceneNodeList::iterator begin(){ return m_children.begin(); }
    SceneNodeList::iterator end(){ return m_children.end(); }
    size_t childCount()const{ return m_children.size(); }
    std::shared_ptr<SceneNode> childAt(size_t index){ return m_children[index]; }
    std::shared_ptr<SceneNode> parent(){ return m_parent.lock(); }
    size_t rowOfChild(std::shared_ptr<SceneNode> child);
    void removeChildren(size_t index, size_t count);
};

