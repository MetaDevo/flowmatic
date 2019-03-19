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

    virtual std::vector<QVariant> run() {
        QImage img("example.jpg");
        //QImage img(180, 180, QImage::Format_RGB32);
        //img.fill(200);
        images.push_back(img);
        qDebug() << "Ran!";
        return images;
    }

    virtual QImage glimpse() const {
        qDebug() << "glimpse img size: " << images[0].value<QImage>().size();
        return images[0].value<QImage>();
    }
    QString glimpseText() const { return QString("example behavior"); }

private:
    std::vector<QVariant> images;
};

#endif // EXAMPLENODEBEHAVIOR_HPP
