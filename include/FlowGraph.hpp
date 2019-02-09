/// @author Sam Kenyon <sam@metadevo.com>
#ifndef FLOWGRAPH_HPP
#define FLOWGRAPH_HPP

#include <memory>
#include <vector>

class NodeData;

/// Data pipeline base class
class FlowGraph
{
public:
    FlowGraph() {}
    virtual ~FlowGraph() {}

    static int assignId() {
        static int nextId = 0;
        return nextId++;
    }

private:
    std::vector<std::shared_ptr<NodeData>> m_nodes;
};

#endif // FLOWGRAPH_HPP
