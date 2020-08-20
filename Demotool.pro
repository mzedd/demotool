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
    openglwindow.cpp \
    #src/demo/Timeline.cpp \
    src/demo/Clip.cpp \
    src/demo/timelineitem.cpp \
    src/demo/timelinemodel.cpp \
    src/demo/timelineview.cpp \
    src/scene/Scene.cpp \
    src/scene/Camera.cpp \
    src/scene/SceneObject.cpp \
    src/scene/light/ILightSource.cpp \
    src/scene/light/PointLight.cpp \
    src/scene/light/DirectionalLight.cpp \
    src/modelling/Geometry.cpp \
    #src/modelling/Sphere.cpp \
    src/modelling/Plane.cpp \
    #src/modelling/Cylinder.cpp \
    #src/modelling/Tetraeder.cpp \
    src/Material.cpp \
    demo.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ClipArrangement.h \
    openglwindow.h \
    #src/demo/Timeline.h \
    src/demo/Clip.h \
    src/demo/timelineitem.h \
    src/demo/timelinemodel.h \
    src/demo/timelineview.h \
    src/scene/Scene.h \
    src/scene/Camera.h \
    src/scene/SceneObject.h \
    src/scene/Scene.h \
    src/scene/light/ILightSource.h \
    src/scene/light/PointLight.h \
    src/scene/light/DirectionalLight.h \
    src/modelling/Geometry.h \
    #src/modelling/Sphere.h \
    src/modelling/Plane.h \
    #src/modelling/Cylinder.h \
    #src/modelling/Tetraeder.h \
    src/Material.h \
    demo.h \
    mainwindow.h

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
    data/shader/voronoi.frag
