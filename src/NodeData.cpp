/// @author Sam Kenyon <sam@metadevo.com>

#include <QGuiApplication>

#include "FlowGraph.hpp"
#include "NodeData.hpp"
#include "ExampleNodeBehavior.hpp"

NodeData::NodeData(const int schematicId) :
    m_schematicId(schematicId)
{
    m_uniqueId = FlowGraph::assignId();
    m_result[0] = m_defaultValue;
    FlowGraph::registerNode(this);

    // you can reset to a custom behavior with setBehavior()
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

/// Whatever the last result was
/// @todo a node can have 1 or many outputs
QVariant NodeData::result(const int outputIndex) const
{
    if (m_behavior) {
        return m_behavior->result();
    } else {
        return defaultValue();
    }
}

/// Reimplement in subclass or call setBehavior() first
void NodeData::preview()
{
    m_isRunning = true;
    emit isRunningChanged(m_isRunning);

    QCoreApplication::processEvents(); // make sure gui updates while we run
    if (m_behavior) {
        m_behavior->setSeqPos(m_seqPos);
        m_result[m_seqPos] = m_behavior->preview();
        emit glimpseChanged(m_schematicId, m_uniqueId, m_behavior->glimpse());
        emit previewResultChanged(m_seqPos, m_result[0]); // this will cause downstream nodes to run
    }

    m_isRunning = false;
    emit isRunningChanged(m_isRunning);
}

/// Reimplement in subclass or call subclass NodeBehavior and call setBehavior() first.
/// For either case, by default "run" is the same as "preview," but an application might
/// need "run" to do something beyond "preview" e.g. changing application objects, saving
/// out to files, slow high-res rendering, etc.
void NodeData::run()
{
    m_isRunning = true;
    emit isRunningChanged(m_isRunning);

    QCoreApplication::processEvents(); // make sure gui updates while we run
    if (m_behavior) {
        m_behavior->setSeqPos(m_seqPos);
        m_result[m_seqPos] = m_behavior->run();
        emit glimpseChanged(m_schematicId, m_uniqueId, m_behavior->glimpse());
        emit runResultChanged(m_seqPos, m_result[0]); // this will cause downstream nodes to run
    }
    m_isRunning = false;
    emit isRunningChanged(m_isRunning);
}

/// Typically just one node would drive it
/// @todo proper way to have other top-level (has no inputs) nodes update
void NodeData::previewAll()
{
    m_isRunning = true;
    emit isRunningChanged(m_isRunning);

    for (int i = m_seqStart; i <= m_seqEnd; ++i)
    {
        QCoreApplication::processEvents(); // make sure gui updates while we run
        if (m_behavior) {
            m_behavior->setSeqPos(i);
            m_result[m_seqPos] = m_behavior->preview();
            emit glimpseChanged(m_schematicId, m_uniqueId, m_behavior->glimpse());
            emit previewResultChanged(m_seqPos, m_result[0]); // this will cause downstream nodes to run
        }
    }

    m_isRunning = false;
    emit isRunningChanged(m_isRunning);
}

/// Typically just one node would drive it
/// @todo proper way to have other top-level (has no inputs) nodes update
void NodeData::runAll()
{
    m_isRunning = true;
    emit isRunningChanged(m_isRunning);

    for (int i = m_seqStart; i <= m_seqEnd; ++i)
    {
        QCoreApplication::processEvents(); // make sure gui updates while we run
        if (m_behavior) {
            m_behavior->setSeqPos(i);
            m_result[m_seqPos] = m_behavior->run();
            emit glimpseChanged(m_schematicId, m_uniqueId, m_behavior->glimpse());
            emit runResultChanged(m_seqPos, m_result[0]); // this will cause downstream nodes to run
        }
    }

    m_isRunning = false;
    emit isRunningChanged(m_isRunning);
}

/// Goto a sequence position.
/// @position is a 0-based index global to the schematic
bool NodeData::scrub(const int position)
{
    int newPos = m_seqStart + position;
    if ((m_seqPos != newPos) && (newPos >= m_seqStart) && (newPos <= m_seqEnd))
    {
        m_seqPos = newPos;
        emit seqPosChanged(m_seqPos);
        if (m_behavior) {
            m_behavior->setSeqPos(m_seqPos);
        }
        return true;
    } else {
        return false;
    }
}

void NodeData::setInputId(const int inputId, const int index)
{
    m_inputId[index] = inputId; emit inputIdChanged();
    for (auto nodeId : m_inputId) {
        const NodeData* node = FlowGraph::nodeAt(m_schematicId, nodeId);
        if (node) {
            QObject::connect(node, &NodeData::previewResultChanged, this, &NodeData::updatePreview);
            QObject::connect(node, &NodeData::runResultChanged, this, &NodeData::updateRun);
        }
    }
}

void NodeData::updatePreview(const int position, QVariant& result)
{
    scrub(position);
    preview();
}

void NodeData::updateRun(const int position, QVariant& result)
{
    scrub(position);
    run();
}

void NodeData::select(const int oldNodeId)
{
    const NodeData* node = FlowGraph::nodeAt(m_schematicId, oldNodeId);
    if (node) {
        node->unselect();
    }
    m_selected = true;
    emit isSelectedChanged(m_selected);
}

void NodeData::unselect() const
{
    m_selected = false;
    emit isSelectedChanged(m_selected);
}

void NodeData::setBehaviorByName(const QString& behaviorName)
{
    m_behavior = FlowGraph::makeBehavior(behaviorName);
    if (!m_behavior) {
        qDebug() << __func__ << "make behavior failed.";
    }
}
