/// @author Sam Kenyon <sam@metadevo.com>
#include <QDebug>
#include <QObject>
#include <QSGNode>
#include <QSGImageNode>
#include <QSGSimpleRectNode>
#include <QString>
#include <QQuickWindow>

#include "FlowGraph.hpp"
#include "GlimpseImage.hpp"
#include "NodeData.hpp"

GlimpseImage::GlimpseImage()
{
    setFlag(QQuickItem::ItemHasContents);
}

GlimpseImage::~GlimpseImage()
{
}

void GlimpseImage::updateConnections()
{
    if (m_schematicId >=0 && m_nodeId >=0) {
        const NodeData* node = FlowGraph::nodeAt(m_schematicId, m_nodeId);
        if (node) {
            QObject::connect(node, &NodeData::glimpseChanged, this, &GlimpseImage::setGlimpse);
        }
    }
}

void GlimpseImage::setGlimpse(const int schematicId, const int nodeid, const QImage& image)
{
    if ((schematicId == m_schematicId) && (nodeid == m_nodeId)) {
        m_image = image;
        update();
    }
}

QSGNode* GlimpseImage::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{
    Q_UNUSED(updatePaintNodeData)
    QSGImageNode* n = static_cast<QSGImageNode*>(oldNode);

    if (!n) {
        n = window()->createImageNode();
        n->setOwnsTexture(true);
        n->setFiltering(QSGTexture::Linear);
    }

    if (m_image.isNull()) {
        return n;
    }

    QSGTexture* texture = window()->createTextureFromImage(m_image, QQuickWindow::TextureIsOpaque);

    if (!texture) {
        return n;
    }

    n->setTexture(texture);
    n->setRect(0, 0, width(), height());
    return n;
}
