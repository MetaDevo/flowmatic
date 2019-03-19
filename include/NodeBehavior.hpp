/// @author Sam Kenyon <sam@metadevo.com>
#ifndef NODEBEHAVIOR_HPP
#define NODEBEHAVIOR_HPP

#include <QImage>
#include <QVariant>

/// abstract base class for a behavior, i.e. what does this node do
class NodeBehavior
{
public:
    NodeBehavior() {}
    virtual ~NodeBehavior() {}

    virtual std::vector<QVariant> run() = 0;
    virtual QImage glimpse() const { return QImage(); }
    virtual QString glimpseText() const { return QString(); }

    virtual void setSeqPos(const int position) {}
};

#endif // NODEBEHAVIOR_HPP
