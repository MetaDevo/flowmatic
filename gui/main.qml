/// @author Sam Kenyon <sam@metadevo.com>
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.11

ApplicationWindow {
    id: main
    visible: true
    width: 1200
    height: 700
    title: qsTr("Flowmatic Demo")

    FlowmaticWorkspace {
        width: 900
        height: 700
        x: 0
    }

}
