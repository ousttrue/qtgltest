#pragma once
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <array>
#include "Vec3.h"

class IndexedVertexBuffer;
class Camera;
class Light;
class SceneNode: public std::enable_shared_from_this<SceneNode>
{
    std::string m_name;

    // tree
    std::weak_ptr<SceneNode> m_parent;
    typedef std::vector<std::shared_ptr<SceneNode>> SceneNodeList;
    SceneNodeList m_children;

    // transformation
    std::array<float, 3> m_position;
    std::array<float, 4> m_quaternion;

    // reference
    std::shared_ptr<IndexedVertexBuffer> m_buffer;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Light> m_light;

public:
    SceneNode(const std::string &name);
    std::string name()const{ return m_name; }

    // tree
    std::shared_ptr<SceneNode> addChild(const std::shared_ptr<SceneNode> &node);
    SceneNodeList::iterator begin(){ return m_children.begin(); }
    SceneNodeList::iterator end(){ return m_children.end(); }
    size_t childCount()const{ return m_children.size(); }
    std::shared_ptr<SceneNode> childAt(size_t index){ return m_children[index]; }
    std::shared_ptr<SceneNode> parent(){ return m_parent.lock(); }
    size_t rowOfChild(std::shared_ptr<SceneNode> child);
    void removeChildren(size_t index, size_t count);

    // transformation
    void setPosition(float x, float y, float z){ 
        m_position[0]=x;
        m_position[1]=y;
        m_position[2]=z;
    }
    const std::array<float, 3> &position()const{ return m_position; }
    void setQuaternion(float x, float y, float z, float w){
        m_quaternion[0]=x;
        m_quaternion[1]=y;
        m_quaternion[2]=z;
        m_quaternion[3]=w;
    }
    const std::array<float, 4> &quaternion()const{ return m_quaternion; }
    Vec3 euler()const;

    // mesh
    void setMesh(const std::shared_ptr<IndexedVertexBuffer> &buffer){ m_buffer=buffer; }
    std::shared_ptr<IndexedVertexBuffer> getMesh()const{ return m_buffer; }

    // camera
    void setCamera(const std::shared_ptr<Camera> &camera){ m_camera=camera; }
    std::shared_ptr<Camera> getCamera()const{ return m_camera; }

    // light
    void setLight(const std::shared_ptr<Light> &light){ m_light=light; }
    std::shared_ptr<Light> getLight()const{ return m_light; }
};

