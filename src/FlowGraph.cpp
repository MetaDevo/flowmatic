/// @author Sam Kenyon <sam@metadevo.com>

#include "FlowGraph.hpp"
#include "NodeData.hpp"

QHash<int, QHash<int, const NodeData*>> FlowGraph::m_registry;

void FlowGraph::registerNode(const NodeData* node)
{
    m_registry[node->schematicId()][node->uniqueId()] = node;
}
