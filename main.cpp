/// @author Sam Kenyon <sam@metadevo.com>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>

#include "FlowGraph.hpp"
#include "GlimpseImage.hpp"
#include "ImageSequenceBehavior.hpp"
#include "NodeData.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    FlowGraph::registerBehaviorMaker("imgseq", BehaviorMakeFunc(ImageSequenceBehavior::makeBehavior));

    qmlRegisterType<NodeData>("flowmatic", 1, 0, "NodeData");
    qmlRegisterType<GlimpseImage>("flowmatic", 1, 0, "GlimpseImage");

    QSurfaceFormat format;
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/gui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
