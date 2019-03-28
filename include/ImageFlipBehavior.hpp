/// @author Sam Kenyon <sam@metadevo.com>
#ifndef IMAGEFLIPBEHAVIOR_HPP
#define IMAGEFLIPBEHAVIOR_HPP

#include <memory>
#include <QDebug>
#include <QImage>
#include <QVariant>

#include "NodeBehavior.hpp"

/// A simple example behavior that flips image frames horizontally or vertically
class ImageFlipBehavior : public NodeBehavior
{
public:
    ImageFlipBehavior() {}
    virtual ~ImageFlipBehavior() {}

    virtual QVariant* run(const QHash<int, QVariant*>& inputs)
    {
        if (inputs.values()[0] != nullptr) {
            images[m_seqPos] = inputs.values()[0]->value<QImage>().mirrored();
            return &images[m_seqPos];
        } else {
            return nullptr;
        }
    }

    virtual QImage glimpse() const {
        qDebug() << __func__ << "glimpse img size: " << images[0].value<QImage>().size();
        return images[m_seqPos].value<QImage>();
    }

    virtual QString glimpseText() const { return QString("image flip"); }
    virtual QVariant result() const { return images[m_seqPos]; }
    virtual void setSeqPos(const int position) { m_seqPos = position; }

    static std::shared_ptr<NodeBehavior> makeBehavior() { return std::make_shared<ImageFlipBehavior>(); }

private:
    QHash<int, QVariant> images;
    int m_seqPos = 0;
};

#endif // IMAGEFLIPBEHAVIOR_HPP
