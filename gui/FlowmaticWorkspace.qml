/// @author Sam Kenyon <sam@metadevo.com>
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.11

// A default generic editor with the various Flowmatic items
Rectangle {
    id: flowmaticWorkspace
    visible: true
    color: "#000000"
    property int selectedNode: -1

    Schematic {
        id: schematicView
        x: 10
        y: 10
    }
    GlimpseScrollView
    {
        //x: schematicView.x
        //y: schematicView.height
        anchors.left: schematicView.left
        anchors.top: schematicView.bottom
    }
    PropertiesView {
        //x: schematicView.width
        //y: schematicView.y
        anchors.left: schematicView.right
        anchors.top: schematicView.top
        width: 300
        height: 400
    }

    ///@todo horizontal slider (e.g. for frames dimension in img sequence)
    ///@todo vertical slider (e.g. for z dimension in img sequence)
}
