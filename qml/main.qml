import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.1
import com.ass.plot 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 560
    minimumWidth: 320
    minimumHeight: 240
    title: qsTr("plot")

    Shortcut { sequence: StandardKey.Quit; onActivated: {
            close()
        }
    }

    Shortcut { sequence: "Alt+F4"; onActivated: {
            Qt.quit()
        }
    }

    Vm{
        id: dotsModel
    }

    Timer
    {
        id: trackTimer
        interval: 100; running: true; repeat: true

        onTriggered:
        {
            if(canvas.available)
                canvas.requestPaint()
        }
    }

    Canvas
    {
        id: canvas
        anchors.fill: parent
        width: parent.width
        height: parent.height

        property real coeffWidth: 100 / width
        property real coeffHeight: 100 / height

        onPaint:
        {
            axes()
            falseDots()
        }

        function falseDots()
        {
            var ctx = getContext("2d");
            ctx.save()
            ctx.strokeStyle = "red";
            ctx.beginPath();

            var d_arr = []
            d_arr = dotsModel.dots();
            for(var i = 0; i < d_arr.length; i += 3)
                if(d_arr[i + 0] !== 0.0 && d_arr[i + 1] !== 0.0)
                    ctx.lineTo(d_arr[i + 0] + width / 2, d_arr[i + 1] + height / 2);

            ctx.stroke();
            ctx.restore();
        }

        function axes()
        {
            var ctx = getContext("2d");
            ctx.reset();
            ctx.lineWidth = 1;
            ctx.strokeStyle = "black";
            ctx.beginPath()

            ctx.moveTo(width / 2, 0)
            ctx.lineTo(width / 2, height)

            ctx.moveTo(0, height / 2)
            ctx.lineTo(width, height / 2)

            ctx.stroke();
        }
    }
}
