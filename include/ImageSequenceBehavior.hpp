/// @author Sam Kenyon <sam@metadevo.com>
#ifndef IMAGESEQUENCEBEHAVIOR_HPP
#define IMAGESEQUENCEBEHAVIOR_HPP

#include <memory>
#include <QDebug>
#include <QImage>
#include <QVariant>

#include "NodeBehavior.hpp"

/// Loads a sequence of images
class ImageSequenceBehavior : public NodeBehavior
{
public:
    ImageSequenceBehavior() {}
    virtual ~ImageSequenceBehavior() {}

    virtual QVariant* run(const QHash<int, QVariant*>& inputs)
    {
        QString fileName = "example" + QString::number(m_seqPos) + ".jpg";
        QImage img(fileName);
        images[m_seqPos] = img;
        qDebug() << "filename: " << fileName;
        return &images[m_seqPos];
    }

    virtual QImage glimpse() const {
        qDebug() << "glimpse img size: " << images[0].value<QImage>().size();
        return images[m_seqPos].value<QImage>();
    }

    virtual QString glimpseText() const { return QString("image sequence"); }
    virtual QVariant result() const { return images[m_seqPos]; }
    virtual void setSeqPos(const int position) { m_seqPos = position; }

    static std::shared_ptr<NodeBehavior> makeBehavior() { return std::make_shared<ImageSequenceBehavior>(); }

private:
    QHash<int, QVariant> images;
    int m_seqPos = 0;
};

#endif // IMAGESEQUENCEBEHAVIOR_HPP
