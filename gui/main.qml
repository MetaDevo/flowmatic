/// @author Sam Kenyon <sam@metadevo.com>
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.11

ApplicationWindow {
    id: main
    visible: true
    width: 900
    height: 700
    title: qsTr("Flowmatic Demo")

    Schematic {
        x: 10
        y: 10
    }
    GlimpseScrollView
    {
        x: 10
        y: 410
    }

}
