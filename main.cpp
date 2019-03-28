/// @author Sam Kenyon <sam@metadevo.com>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSurfaceFormat>

#include "FlowGraph.hpp"
#include "GlimpseImage.hpp"
#include "ImageFlipBehavior.hpp"
#include "ImageSequenceBehavior.hpp"
#include "NodeData.hpp"
#include "PropertyAccess.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    FlowGraph::registerBehaviorMaker("imgseq", BehaviorMakeFunc(ImageSequenceBehavior::makeBehavior));
    FlowGraph::registerBehaviorMaker("imgflip", BehaviorMakeFunc(ImageFlipBehavior::makeBehavior));

    qmlRegisterType<NodeData>("flowmatic", 1, 0, "NodeData");
    qmlRegisterType<GlimpseImage>("flowmatic", 1, 0, "GlimpseImage");
    qmlRegisterType<NodeProperty>("flowmatic", 1, 0, "NodeProperty");

    PropertyAccess& nodeProperties = PropertyAccess::instance();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("nodeProperties", &nodeProperties);
    engine.load(QUrl(QStringLiteral("qrc:/gui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
