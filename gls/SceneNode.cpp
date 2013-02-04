#include "SceneNode.h"

SceneNode::SceneNode(const std::string &name)
    : m_name(name)
{
}

std::shared_ptr<SceneNode> SceneNode::addChild(const std::string &name, 
        std::shared_ptr<IndexedVertexBuffer> buffer)
{
    auto child=std::make_shared<SceneNode>(name);
    child->m_parent=shared_from_this();
    child->m_buffer=buffer;
    return child;
}

