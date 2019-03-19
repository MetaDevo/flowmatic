/// @author Sam Kenyon <sam@metadevo.com>
#ifndef FLOWGRAPH_HPP
#define FLOWGRAPH_HPP

#include <memory>
#include <vector>

#include <QHash>

class NodeData;
class NodeBehavior;

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

    static const NodeData* nodeAt(const int schematicId, const int nodeId) {
        return m_registry[schematicId][nodeId];
    }

    static std::shared_ptr<NodeBehavior> behaviorFactory(const QString& behaviorType);

private:
    static QHash<int, QHash<int, const NodeData*>> m_registry;
};

#endif // FLOWGRAPH_HPP
