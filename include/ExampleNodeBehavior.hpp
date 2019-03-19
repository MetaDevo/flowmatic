/// @author Sam Kenyon <sam@metadevo.com>
#ifndef EXAMPLENODEBEHAVIOR_HPP
#define EXAMPLENODEBEHAVIOR_HPP

#include <QDebug>
#include <QImage>
#include <QVariant>

#include "NodeBehavior.hpp"

class ExampleNodeBehavior : public NodeBehavior
{
public:
    ExampleNodeBehavior() {}
    virtual ~ExampleNodeBehavior() {}

    virtual QHash<int, QVariant> run()
    {
        QString fileName = "example" + QString::number(m_seqPos) + ".jpg";
        QImage img(fileName);
        images[m_seqPos] = img;
        qDebug() << "filename: " << fileName;
        return images;
    }

    virtual QImage glimpse() const {
        qDebug() << "glimpse img size: " << images[0].value<QImage>().size();
        return images[m_seqPos].value<QImage>();
    }
    virtual QString glimpseText() const { return QString("example behavior"); }
    virtual void setSeqPos(const int position) { m_seqPos = position; }

private:
    QHash<int, QVariant> images;
    int m_seqPos = 0;
};

#endif // EXAMPLENODEBEHAVIOR_HPP
