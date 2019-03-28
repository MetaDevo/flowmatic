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

    virtual QVariant run()
    {
        qDebug() << "example run on seqPos " << m_seqPos;
        return QImage();
    }

    virtual QString glimpseText() const { return QString("example behavior"); }
    virtual void setSeqPos(const int position) { m_seqPos = position; }

private:
    int m_seqPos = 0;
};

#endif // EXAMPLENODEBEHAVIOR_HPP
