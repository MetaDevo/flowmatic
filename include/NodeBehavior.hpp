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

    virtual QHash<int, QVariant> run() = 0;

    /// Reimplement if you need the "run" to do something beyond "preview"
    /// e.g. changing application objects, saving out to files, a slow high-res rending, etc.
    virtual QHash<int, QVariant> preview() { return run(); }

    virtual QImage glimpse() const { return QImage(); }
    virtual QString glimpseText() const { return QString(); }

    virtual void setSeqPos(const int position) {}
};

#endif // NODEBEHAVIOR_HPP
