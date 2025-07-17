import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Room Dashboard"
    
    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0"
        
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 20
            
            // Header
            Rectangle {
                Layout.fillWidth: true
                height: 60
                color: "#ffffff"
                radius: 10
                
                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    
                    Label {
                        text: "Room Environment Monitor"
                        font.pixelSize: 24
                        font.bold: true
                    }
                    
                    Item { Layout.fillWidth: true }
                    
                    Button {
                        text: sensorModel.recording ? "Stop Recording" : "Start Recording"
                        onClicked: sensorModel.recording = !sensorModel.recording
                    }
                }
            }
            
            // Sensor readings
            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: 3
                columnSpacing: 20
                rowSpacing: 20
                
                // Temperature card
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#ffffff"
                    radius: 10
                    
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 15
                        spacing: 10
                        
                        Label {
                            text: "Temperature"
                            font.pixelSize: 18
                            font.bold: true
                        }
                        
                        Label {
                            text: sensorModel.temperature.toFixed(1) + "°C"
                            font.pixelSize: 32
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                }
                
                // Humidity card
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#ffffff"
                    radius: 10
                    
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 15
                        spacing: 10
                        
                        Label {
                            text: "Humidity"
                            font.pixelSize: 18
                            font.bold: true
                        }
                        
                        Label {
                            text: sensorModel.humidity.toFixed(1) + "%"
                            font.pixelSize: 32
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                }
                
                // CO2 card
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#ffffff"
                    radius: 10
                    
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 15
                        spacing: 10
                        
                        Label {
                            text: "CO₂"
                            font.pixelSize: 18
                            font.bold: true
                        }
                        
                        Label {
                            text: sensorModel.co2.toFixed(0) + " ppm"
                            font.pixelSize: 32
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                }
            }
        }
    }
} 