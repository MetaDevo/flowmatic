/// @author Sam Kenyon <sam@metadevo.com>

#include <QGuiApplication>

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

/// reimplement in subclass, or call setBehavior() first
void NodeData::run()
{
    m_isRunning = true;
    emit isRunningChanged(m_isRunning);

    for (int i = m_seqStart; i <= m_seqEnd; ++i)
    {
        QCoreApplication::processEvents(); // make sure gui updates while we run
        if (m_behavior) {
            m_result = m_behavior->run();
            emit glimpseChanged(m_schematicId, m_uniqueId, m_behavior->glimpse());
            emit resultChanged(); // this will cause downstream nodes to run
        }
    }

    m_isRunning = false;
    emit isRunningChanged(m_isRunning);
}

/// Goto a sequence position.
/// @position is a 0-based index global to the schematic
void NodeData::scrub(const int position)
{
    m_seqPos = m_seqStart + position;
    emit seqPosChanged(m_seqPos);
    if (m_behavior) {
        m_behavior->setSeqPos(m_seqPos);
    }
}

