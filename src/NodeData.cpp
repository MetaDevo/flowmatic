/// @author Sam Kenyon <sam@metadevo.com>
#include "NodeData.hpp"

NodeData::NodeData()
{
    m_id = FlowGraph::assignId();
}

NodeData::NodeData(QString name, QVariant value) :
    m_name(name), m_value(value)
{
    m_id = FlowGraph::assignId();
}

NodeData::~NodeData() {}
