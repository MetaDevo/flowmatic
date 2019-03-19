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

        if(!n) {
            qDebug() << "node is still null";
        }

        n->setOwnsTexture(true);
        n->setFiltering(QSGTexture::Linear);
        m_imageNodeInitted = true;
    }
    n->setRect(0, 0, 180, 180);
    n->setSourceRect(0, 0, width(), height());

    QSGTexture* texture = nullptr;
    if (m_image.isNull()) {
        // dummy image as placeholder
        QImage img(180, 180, QImage::Format_RGB32);
        img.fill(200);
        setWidth(img.width());
        setHeight(img.height());
        texture = window()->createTextureFromImage(img, QQuickWindow::TextureIsOpaque);
    } else {
        setWidth(m_image.width());
        setHeight(m_image.height());
        texture = window()->createTextureFromImage(m_image, QQuickWindow::TextureIsOpaque);
    }

    if (!texture) {
        qDebug() << "GlimpseImage::updatePaintNode: null texture";
        return n;
    }

    n->setTexture(texture);
    //n->markDirty(QSGNode::DirtyGeometry);

    return n;
}
