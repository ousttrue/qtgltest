#pragma once
#include <string>
#include <memory>
#include <list>


class IndexedVertexBuffer;
class ShaderProgram;
class SceneNode: public std::enable_shared_from_this<SceneNode>
{
    std::string m_name;
    std::weak_ptr<SceneNode> m_parent;
    typedef std::list<std::shared_ptr<SceneNode>> SceneNodeList;
    SceneNodeList m_children;

    std::shared_ptr<IndexedVertexBuffer> m_buffer;

public:
    SceneNode(const std::string &name);
    std::shared_ptr<SceneNode> addChild(const std::string &name, 
            std::shared_ptr<IndexedVertexBuffer> buffer);
    std::shared_ptr<IndexedVertexBuffer> getBuffer(){ return m_buffer; }
    void clear(){ m_children.clear(); }
    SceneNodeList::iterator begin(){ return m_children.begin(); }
    SceneNodeList::iterator end(){ return m_children.end(); }
};

