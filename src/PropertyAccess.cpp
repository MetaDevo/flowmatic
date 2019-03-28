/// @author Sam Kenyon <sam@metadevo.com>

#include "FlowGraph.hpp"
#include "NodeData.hpp"
#include "PropertyAccess.hpp"

void PropertyAccess::setNode(const int schematicId, const int nodeId)
{
    m_nodeId = nodeId;
    m_schematicId = schematicId;
    m_node = FlowGraph::nodeAt(m_schematicId, m_nodeId);

    for (auto it : m_currentProperties) {
        delete it;
    }
    m_currentProperties.clear();
    QHash<QString, QVariant>::const_iterator i = m_node->properties().constBegin();
    while (i != m_node->properties().constEnd()) {
        m_currentProperties.push_back(new NodeProperty(i.key(), i.value()));
    }
}

QQmlListProperty<NodeProperty> PropertyAccess::getNodeProperties()
{
    return QQmlListProperty<NodeProperty>(this, this,
                                          &PropertyAccess::nodePropertiesCount,
                                          &PropertyAccess::nodePropertyAt);
}

int PropertyAccess::nodePropertiesCount() const
{
    return m_node->propertiesSize();
}

NodeProperty* PropertyAccess::nodePropertyAt(int index)
{
    if (index < m_node->propertiesSize()) {
        return m_currentProperties[index];
    } else {
        return nullptr;
    }
}

int PropertyAccess::nodePropertiesCount(QQmlListProperty<NodeProperty>* list)
{
    return reinterpret_cast<PropertyAccess*>(list->data)->nodePropertiesCount();
}

NodeProperty* PropertyAccess::nodePropertyAt(QQmlListProperty<NodeProperty>* list, int i)
{
    return reinterpret_cast<PropertyAccess*>(list->data)->nodePropertyAt(i);
}

