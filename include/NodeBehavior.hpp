/// @author Sam Kenyon <sam@metadevo.com>
#ifndef NODEBEHAVIOR_HPP
#define NODEBEHAVIOR_HPP

#include <QHash>
#include <QImage>
#include <QVariant>

/// abstract base class for a behavior, i.e. what does this node do
class NodeBehavior
{
public:
    NodeBehavior() {}
    virtual ~NodeBehavior() {}

    virtual QVariant run() = 0;

    /// Reimplement if you need preview to do something different, e.g. less permanent
    virtual QVariant preview() { return run(); }

    virtual QImage glimpse() const { return QImage(); }
    virtual QString glimpseText() const { return QString(); }
    virtual QVariant result() const { return QImage(); }
    virtual void setSeqPos(const int position) {}
};

#endif // NODEBEHAVIOR_HPP
