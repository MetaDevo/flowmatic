/// @author Sam Kenyon <sam@metadevo.com>
#include <QDebug>
#include <QObject>
#include <QSGNode>
#include <QSGImageNode>
#include <QSGSimpleRectNode>
#include <QString>
#include <QQuickWindow>

#include "GlimpseImage.hpp"

GlimpseImage::GlimpseImage()
{
    try
    {
        setFlag(QQuickItem::ItemHasContents);

        //QObject::connect
    }
    catch (const std::exception &e)
    {
        qDebug() << "ERROR: " << e.what();
    }
    catch (...)
    {
        qDebug() << "Unknown exception";
    }
}

GlimpseImage::~GlimpseImage()
{
}

QSGNode* GlimpseImage::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{
    Q_UNUSED(updatePaintNodeData)
    QSGImageNode* n = static_cast<QSGImageNode*>(oldNode);

    if (!n) {
        n = window()->createImageNode();
        n->setOwnsTexture(true);
        n->setFiltering(QSGTexture::Linear);
        //setWidth();
        //setHeight();
    }

    QImage image;

    ///@todo get image
    ///image = m_stack->imageBuffer();

    if (image.isNull()) {
        qDebug() << "ERROR: image is null!";
        return n;
    }

    QSGTexture* texture = window()->createTextureFromImage(image, QQuickWindow::TextureIsOpaque);

    if (!texture)
    {
        return n;
    }
    n->setTexture(texture);
    n->setRect(0, 0, width(), height());
    //n->setSourceRect(0, 0, width(), height());
    return n;
}
