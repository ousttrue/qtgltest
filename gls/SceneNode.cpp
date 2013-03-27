#include "SceneNode.h"

SceneNode::SceneNode(const std::string &name)
    : m_name(name)
{
}

std::shared_ptr<SceneNode> SceneNode::addChild(const std::shared_ptr<SceneNode> &child)
{
    child->m_parent=shared_from_this();
    m_children.push_back(child);
    return child;
}

/*
std::shared_ptr<SceneNode> SceneNode::addChild(const std::string &name, 
        std::shared_ptr<IndexedVertexBuffer> buffer)
{
    auto child=std::make_shared<SceneNode>(name);
    child->m_buffer=buffer;
    return addChild(child);
}
*/

size_t SceneNode::rowOfChild(std::shared_ptr<SceneNode> child)
{
    for(size_t i=0; i<m_children.size(); ++i){
        if(m_children[i]==child){
            return i;
        }
    }
    return -1;
}

void SceneNode::removeChildren(size_t index, size_t count)
{
    auto start=m_children.begin();
    m_children.erase(start, start+count);
}

