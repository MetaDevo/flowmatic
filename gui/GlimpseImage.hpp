/// @author Sam Kenyon <sam@metadevo.com>
#ifndef GLIMPSEIMAGE_HPP
#define GLIMPSEIMAGE_HPP

#include <QQuickItem>

class GlimpseImage : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int zoomFactor READ getZoomFactor WRITE setZoomFactor NOTIFY zoomFactorChanged)

public:
    GlimpseImage();
    virtual ~GlimpseImage() override;

protected:
    virtual QSGNode* updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData) override;

signals:

public slots:

private:
};

#endif // GLIMPSEIMAGE_HPP
