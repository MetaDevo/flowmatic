/// @author Sam Kenyon <sam@metadevo.com>
#ifndef GLIMPSEIMAGE_HPP
#define GLIMPSEIMAGE_HPP

#include <QImage>
#include <QQuickItem>

/// QML item for showing a preview of the result of a node
class GlimpseImage : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int nodeId READ nodeId WRITE setNodeId)
    Q_PROPERTY(int schematicId READ schematicId WRITE setSchematicId)
    Q_PROPERTY(int zoom READ getZoom WRITE setZoom NOTIFY zoomChanged)

public:
    GlimpseImage();
    virtual ~GlimpseImage() override;

    int nodeId() const { return m_nodeId; }
    int schematicId() const { return m_schematicId; }
    int getZoom() const { return m_zoom; }

    void setNodeId(const int id) { m_nodeId = id; }
    void setSchematicId(const int id) { m_schematicId = id; }
    void setZoom(const int zoom) { m_zoom = zoom; }

signals:
    void zoomChanged();

public slots:
    void setGlimpse(const int schematicId, const int id, const QImage& image);

private:
    virtual QSGNode* updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData) override;
    void updateConnections();

    int m_nodeId = 0;
    int m_schematicId = 0;
    bool m_initted = false;
    int m_zoom = 100;
    QImage m_image;
};

#endif // GLIMPSEIMAGE_HPP
