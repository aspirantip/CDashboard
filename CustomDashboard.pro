TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    reader.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    reader.h

DISTFILES += \
    content/back_audi.png \
    content/background2.png \
    content/BatteryAlertIcon.png \
    content/EngineWarningIcon.png \
    content/FogLampIcon.png \
    content/FuelLowIcon.png \
    content/needle.png \
    content/needle2.png \
    content/odo_audi.png \
    content/OilPressureIcon.png \
    content/Overlay.png \
    content/quit.png \
    content/speedometer.png \
    content/taho_audi.png \
    content/TractionControlIcon.png \
    content/ExitBtn.qml \
    content/Speedometer.qml \
    content/Taho.qml
