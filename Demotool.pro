QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ClipArrangement.cpp \
    Timeline.cpp \
    openglwindow.cpp \
    #src/demo/Timeline.cpp \
    src/demo/Clip.cpp \
    src/demo/timelineitem.cpp \
    src/demo/timelinemodel.cpp \
    src/demo/timelineview.cpp \
    demo.cpp \
    main.cpp \
    mainwindow.cpp \
    src/scene/Camera.cpp \
    src/scene/ShaderOnlyScene.cpp

HEADERS += \
    ClipArrangement.h \
    Timeline.h \
    openglwindow.h \
    #src/demo/Timeline.h \
    src/demo/Clip.h \
    src/demo/timelineitem.h \
    src/demo/timelinemodel.h \
    src/demo/timelineview.h \
    src/scene/Camera.h \
    src/scene/Scene.h \
    demo.h \
    mainwindow.h \
    src/scene/ShaderOnlyScene.h

FORMS += \
    cliparrangement.ui \
    mainwindow.ui

INCLUDEPATH += \
    src/

OTHER_FILES += \
    data/shader/shader.vert \
    data/shader/shader.frag \
    data/shader/PBRShader.frag

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(thirdparty/QMidi/src/QMidi.pri)

DISTFILES += \
    data/shader/loading.frag \
    data/shader/quad.vert \
    data/shader/voronoi.frag
