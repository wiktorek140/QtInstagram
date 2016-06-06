import QtQuick 2.0
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: simpleTextFeed

    property string placeholder
    property var echo: TextInput.Normal

    TextField{
        id: loginInput
        width: parent.width
        height: parent.height

        placeholderText: placeholder
        echoMode: echo

        anchors{
            verticalCenter: parent.verticalCenter
        }

        style: TextFieldStyle{
            background: Rectangle{}
        }
    }
}