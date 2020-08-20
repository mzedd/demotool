cmake_minimum_required(VERSION 3.8)
project(demotool)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:\\Qt\\5.15.0\\msvc2019_64\\")

find_package(Qt5 COMPONENTS Core Gui Widgets)

# QMidi
set(QMIDI_SOURCES 
    thirdparty/QMidi/src/QMidiOut.cpp 
	thirdparty/QMidi/src/QMidiFile.cpp 
	thirdparty/QMidi/src/QMidiIn.cpp
)

if(WIN32)
    add_library(QMidi ${QMIDI_SOURCES} thirdparty/QMidi/src/OS/QMidi_Win32.cpp)
    target_link_libraries(QMidi winmm Qt5::Core)
    elseif(UNIX)
    add_library(QMidi ${QMIDI_SOURCES} thirdparty/QMidi/src/OS/QMidi_ALSA.cpp)
    target_link_libraries(QMidi asound Qt5::Core)
endif()
target_include_directories(QMidi PRIVATE
    "${CMAKE_SOURCE_DIR}/thirdparty/QMidi/src"
    "${CMAKE_SOURCE_DIR}/thirdparty/QMidi/src/OS"
    "${CMAKE_SOURCE_DIR}/src/midi"
)

# Demotool
set(SOURCES
# C++ sources
    ClipArrangement.cpp 
    openglwindow.cpp 
    #src/demo/Timeline.cpp 
    src/demo/Clip.cpp 
    src/demo/timelineitem.cpp 
    src/demo/timelinemodel.cpp 
    src/demo/timelineview.cpp 
    src/scene/Scene.cpp 
    src/scene/Camera.cpp 
    src/scene/SceneObject.cpp 
    src/scene/light/ILightSource.cpp 
    src/scene/light/PointLight.cpp 
    src/scene/light/DirectionalLight.cpp 
    src/modelling/Geometry.cpp 
    #src/modelling/Sphere.cpp 
    src/modelling/Plane.cpp 
    #src/modelling/Cylinder.cpp 
    #src/modelling/Tetraeder.cpp 
    src/Material.cpp 
    demo.cpp 
    main.cpp
    mainwindow.cpp
# Midi System Sources
    src/midi/MidiController.cpp
    src/midi/ValueControl.cpp
    src/midi/AkaiAPC40MkII.cpp
# Ui Sources
    cliparrangement.ui
    mainwindow.ui
# Resources
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE 
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/thirdparty/QMidi/src"
    "${CMAKE_SOURCE_DIR}/thirdparty/QMidi/src/OS"
    "${CMAKE_SOURCE_DIR}/src/midi"
)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets QMidi)

if(WIN32)
    get_filename_component(_qt_bin_dir "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt.exe HINTS "${_qt_bin_dir}")
    message("Found windeployqt executable: ${WINDEPLOYQT_EXECUTABLE}")
    message("Binary is in: $<TARGET_FILE_DIR:${PROJECT_NAME}>")
    add_custom_command(TARGET ${PROJECT_NAME} COMMAND ${WINDEPLOYQT_EXECUTABLE} "$<TARGET_FILE:${PROJECT_NAME}>")
endif()

add_custom_command(TARGET ${PROJECT_NAME} COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/data")


