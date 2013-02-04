#pragma once
#include <string>
#include <memory>
#include <list>
#include <vector>


class IndexedVertexBuffer;
class ShaderProgram;
class SceneNode: public std::enable_shared_from_this<SceneNode>
{
    std::string m_name;
    std::weak_ptr<SceneNode> m_parent;
    typedef std::vector<std::shared_ptr<SceneNode>> SceneNodeList;
    SceneNodeList m_children;

    std::shared_ptr<IndexedVertexBuffer> m_buffer;

public:
    SceneNode(const std::string &name);
    std::string name()const{ return m_name; }
    std::shared_ptr<SceneNode> addChild(const std::string &name, 
            std::shared_ptr<IndexedVertexBuffer> buffer);
    std::shared_ptr<IndexedVertexBuffer> getBuffer(){ return m_buffer; }
    SceneNodeList::iterator begin(){ return m_children.begin(); }
    SceneNodeList::iterator end(){ return m_children.end(); }
    size_t childCount()const{ return m_children.size(); }
    std::shared_ptr<SceneNode> childAt(size_t index){ return m_children[index]; }
    std::shared_ptr<SceneNode> parent(){ return m_parent.lock(); }
    size_t rowOfChild(std::shared_ptr<SceneNode> child);
    void removeChildren(size_t index, size_t count);
};

