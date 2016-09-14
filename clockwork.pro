include(resources/theme/material/material.pri)

TEMPLATE = app
TARGET = clockwork
CONFIG += c++14
RESOURCES += clockwork.qrc

QMAKE_CXXFLAGS += -Wextra

DESTDIR = build
OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/moc
RCC_DIR = $${DESTDIR}/rcc
UI_DIR = $${DESTDIR}/ui

INCLUDEPATH += \
    src/graphics \
    src/graphics/renderer \
    src/io \
    src/math \
    src/scene \
    src/system \
    src/task \
    src/ui \
    src

HEADERS += \
    src/graphics/ColorARGB.hh \
    src/graphics/Framebuffer.hh \
    src/graphics/Frustum.hh \
    src/graphics/GraphicsEngine.hh \
    src/graphics/renderer/LineRenderer.hh \
    src/graphics/renderer/PointRenderer.hh \
    src/graphics/renderer/PolygonRenderer.hh \
    src/graphics/renderer/Renderer.hh \
    src/graphics/Viewport.hh \
    src/io/toString.hh \
    src/math/Matrix4.hh \
    src/math/Point3.hh \
    src/math/Quaternion.hh \
    src/math/Vector3.hh \
    src/scene/predefined/Suzanne.hh \
    src/scene/predefined/TexturedCube.hh \
    src/scene/SceneNode.hh \
    src/scene/SceneObject.hh \
    src/system/Application.hh \
    src/system/Error.hh \
    src/system/Service.hh \
    src/task/TaskManager.hh \
    src/ui/FramebufferProvider.hh \
    src/ui/UserInterface.hh \
    src/clockwork.hh

SOURCES += \
    src/graphics/ColorARGB.cc \
    src/graphics/Framebuffer.cc \
    src/graphics/Frustum.cc \
    src/graphics/GraphicsEngine.cc \
    src/graphics/renderer/LineRenderer.cc \
    src/graphics/renderer/PointRenderer.cc \
    src/graphics/renderer/PolygonRenderer.cc \
    src/graphics/renderer/Renderer.cc \
    src/graphics/Viewport.cc \
    src/io/toString.cc \
    src/math/Matrix4.cc \
    src/math/Point3.cc \
    src/math/Point4.cc \
    src/math/Quaternion.cc \
    src/math/Vector3.cc \
    src/scene/predefined/Suzanne.cc \
    src/scene/predefined/TexturedCube.cc \
    src/scene/SceneNode.cc \
    src/scene/SceneObject.cc \
    src/system/Application.cc \
    src/system/Service.cc \
    src/task/TaskManager.cc \
    src/ui/FramebufferProvider.cc \
    src/ui/UserInterface.cc \
    src/clockwork.cc
