/// @author Sam Kenyon <sam@metadevo.com>

#include "FlowGraph.hpp"
#include "NodeData.hpp"
#include "ExampleNodeBehavior.hpp"

NodeData::NodeData(const int schematicId) :
    m_schematicId(schematicId)
{
    m_uniqueId = FlowGraph::assignId();
    m_result.push_back(m_defaultValue);
    FlowGraph::registerNode(this);

    std::shared_ptr<NodeBehavior> behavior = std::make_shared<ExampleNodeBehavior>();
    setBehavior(behavior);
}

NodeData::NodeData(const QString& name, const QVariant value, const int schematicId) :
    m_name(name),
    m_schematicId(schematicId),
    m_defaultValue(value)
{
    m_uniqueId = FlowGraph::assignId();
    FlowGraph::registerNode(this);
}

NodeData::~NodeData()
{}

QImage NodeData::glimpse() const
{
    if (m_behavior) {
        return m_behavior->glimpse();
    } else {
        return QImage(); // this will be a real image in a subclass
    }
}

QString NodeData::glimpseText() const
{
    if (m_behavior) {
        return m_behavior->glimpseText();
    } else {
        return QString::number(m_defaultValue.toInt());
    }
}

/// A node can have 1 or many outputs
QVariant NodeData::result(const int index) const
{
    if (index < m_result.size()) {
        return m_result[index];
    } else {
        return defaultValue();
    }
}

void NodeData::run()
{
    if (m_behavior) {
        m_result = m_behavior->run();
        emit glimpseChanged(m_schematicId, m_uniqueId, m_behavior->glimpse());
        emit resultChanged();
    }
}
