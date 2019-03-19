/// @author Sam Kenyon <sam@metadevo.com>

#include "FlowGraph.hpp"
#include "NodeData.hpp"
#include "ExampleNodeBehavior.hpp"

QHash<int, QHash<int, const NodeData*>> FlowGraph::m_registry;

void FlowGraph::registerNode(const NodeData* node)
{
    m_registry[node->schematicId()][node->uniqueId()] = node;
}

/// Optional. Reimplement if you want to use it.
std::shared_ptr<NodeBehavior> behaviorFactory(const QString& behaviorType)
{
    std::shared_ptr<NodeBehavior> behavior = std::make_shared<ExampleNodeBehavior>();
    return behavior;
}
