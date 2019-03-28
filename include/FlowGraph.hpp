/// @author Sam Kenyon <sam@metadevo.com>
#ifndef FLOWGRAPH_HPP
#define FLOWGRAPH_HPP

#include <functional>
#include <memory>
#include <vector>
#include <QHash>

class NodeData;
class NodeBehavior;

using BehaviorMakeFunc = std::function<std::shared_ptr<NodeBehavior>()>;

/// Data pipeline management. The graph can be represented visually with the QML Schematic and FlowNode items.
class FlowGraph
{
public:
    FlowGraph() {}
    virtual ~FlowGraph() {}

    static int assignId() {
        static int nextId = 0;
        return nextId++;
    }

    static void registerNode(const NodeData* node);
    static void registerBehaviorMaker(const QString& behaviorType, BehaviorMakeFunc makeFunc);

    static const NodeData* nodeAt(const int schematicId, const int nodeId) {
        return m_registry[schematicId][nodeId];
    }

    static std::shared_ptr<NodeBehavior> makeBehavior(const QString& behaviorType);

private:
    static QHash<int, QHash<int, const NodeData*>> m_registry;
    static QHash<QString, BehaviorMakeFunc> m_behaviorFactory;
};

#endif // FLOWGRAPH_HPP
