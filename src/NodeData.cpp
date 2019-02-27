/// @author Sam Kenyon <sam@metadevo.com>
#include "NodeData.hpp"

NodeData::NodeData()
{
    m_uniqueId = FlowGraph::assignId();
    m_inputId.push_back(-1);
    m_result.push_back(m_defaultValue);
}

NodeData::NodeData(QString name, QVariant value) :
    m_name(name),
    m_defaultValue(value)
{
    m_uniqueId = FlowGraph::assignId();
}

NodeData::~NodeData()
{}
