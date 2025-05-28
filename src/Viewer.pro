QT       += \
    core gui \
    opengl \
    opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Graphics/OpenGLWIdget.cpp \
    Graphics/SettingsManager.cpp \
    Graphics/Viewer.cpp \
    Logic/ObjReader.cpp \
    Logic/TransformCom.cpp \
    main.cpp

HEADERS += \
    Graphics/OpenGLWidget.h \
    Graphics/SettingsManager.h \
    Graphics/Viewer.h \
    Logic/ObjController.h \
    Logic/ObjFacade.h \
    Logic/ObjReader.h \
    Logic/TransformCom.h

FORMS += \
    Graphics/Viewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Graphics/Viewer.qrc
