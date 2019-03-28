/// @author Sam Kenyon <sam@metadevo.com>

#include "FlowGraph.hpp"
#include "NodeData.hpp"
#include "ExampleNodeBehavior.hpp"

QHash<int, QHash<int, NodeData*>> FlowGraph::m_registry;
QHash<QString, BehaviorMakeFunc> FlowGraph::m_behaviorFactory;

void FlowGraph::registerNode(NodeData* node)
{
    m_registry[node->schematicId()][node->uniqueId()] = node;
}

void FlowGraph::registerBehaviorMaker(const QString& behaviorType, BehaviorMakeFunc makeFunc)
{
    m_behaviorFactory[behaviorType] = makeFunc;
}

std::shared_ptr<NodeBehavior> FlowGraph::makeBehavior(const QString& behaviorType)
{
    std::shared_ptr<NodeBehavior> behavior = m_behaviorFactory[behaviorType]();
    return behavior;
}
