QT += widgets
TEMPLATE = app
TARGET = clockwork
CONFIG += c++14

QMAKE_CXXFLAGS += -Wextra

DESTDIR = ../build
OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/moc
RCC_DIR = $${DESTDIR}/rcc
UI_DIR = $${DESTDIR}/ui

INCLUDEPATH += . \
               include \
               include/system \
               include/ui \
               include/graphics \
               include/types/math \
               include/system/resource \
               include/ui/views \
               include/scene \
               include/system/subsystem \
               include/concurrency \
               include/graphics/filter \
               include/types \
               include/graphics/renderer \
               include/graphics/projection \
               include/graphics/line.algorithm \
               include/scene/property \
               include/io \
               include/ui/comboboxes \
               include/graphics/renderer/algorithm

# Input
HEADERS += include/system.hh \
           include/concurrency/task.hh \
           include/concurrency/task.render.hh \
           include/concurrency/task.update.hh \
           include/graphics/camera.hh \
           include/graphics/color.hh \
           include/graphics/face.hh \
           include/graphics/fragment.hh \
           include/graphics/framebuffer.hh \
           include/graphics/frustum.hh \
           include/graphics/material.hh \
           include/graphics/model3d.hh \
           include/graphics/primitive.mode.hh \
           include/graphics/texture.hh \
           include/graphics/vertex.hh \
           include/graphics/viewport.hh \
           include/io/file.reader.hh \
           include/io/tostring.hh \
           include/scene/predefs.hh \
           include/scene/scene.hh \
           include/scene/scene.object.hh \
           include/scene/scene.property.hh \
           include/scene/scene.viewer.hh \
           include/system/debug.hh \
           include/system/error.hh \
           include/system/execution.context.hh \
           include/system/services.hh \
           include/system/subsystem.hh \
           include/types/factory.hh \
           include/ui/ui.component.hh \
           include/ui/ui.display.hh \
           include/ui/ui.hh \
           include/ui/window.hh \
           include/graphics/filter/image.filter.hh \
           include/graphics/filter/texture.filter.hh \
           include/graphics/line.algorithm/line.algorithm.hh \
           include/graphics/projection/projection.factory.hh \
           include/graphics/projection/projection.hh \
           include/graphics/renderer/render.algorithm.hh \
           include/scene/property/property.appearance.hh \
           include/system/resource/resource.hh \
           include/system/resource/resource.manager.hh \
           include/system/subsystem/concurrency.subsystem.hh \
           include/system/subsystem/graphics.subsystem.hh \
           include/system/subsystem/physics.subsystem.hh \
           include/types/math/matrix4.hh \
           include/types/math/numerical.hh \
           include/types/math/point3.hh \
           include/types/math/point4.hh \
           include/types/math/quaternion.hh \
           include/types/math/vector3.hh \
           include/ui/comboboxes/ui.combobox.framebuffer.resolution.hh \
           include/ui/comboboxes/ui.combobox.hh \
           include/ui/comboboxes/ui.combobox.image.filter.hh \
           include/ui/comboboxes/ui.combobox.line.algorithm.hh \
           include/ui/comboboxes/ui.combobox.primitive.mode.hh \
           include/ui/comboboxes/ui.combobox.projection.hh \
           include/ui/comboboxes/ui.combobox.renderer.hh \
           include/ui/comboboxes/ui.combobox.texture.filter.hh \
           include/ui/views/ui.view.hh \
           include/ui/views/ui.view.scene.hh \
           include/graphics/line.algorithm/algorithm/bresenham.line.algorithm.hh \
           include/graphics/renderer/algorithm/bump.map.render.algorithm.hh \
           include/graphics/renderer/algorithm/cel.shading.render.algorithm.hh \
           include/graphics/renderer/algorithm/constant.shading.render.algorithm.hh \
           include/graphics/renderer/algorithm/deferred.render.algorithm.hh \
           include/graphics/renderer/algorithm/depth.map.render.algorithm.hh \
           include/graphics/renderer/algorithm/normal.map.render.algorithm.hh \
           include/graphics/renderer/algorithm/phong.shading.render.algorithm.hh \
           include/graphics/renderer/algorithm/point.render.algorithm.hh \
           include/graphics/renderer/algorithm/polygon.render.algorithm.hh \
           include/graphics/renderer/algorithm/random.shading.render.algorithm.hh \
           include/graphics/renderer/algorithm/texture.map.render.algorithm.hh \
           include/graphics/renderer/algorithm/wireframe.render.algorithm.hh
SOURCES += src/clockwork.cpp \
           src/system.cpp \
           src/concurrency/render.task.cpp \
           src/concurrency/task.cpp \
           src/concurrency/update.task.cpp \
           src/graphics/camera.cpp \
           src/graphics/color.cpp \
           src/graphics/face.cpp \
           src/graphics/fragment.cpp \
           src/graphics/framebuffer.cpp \
           src/graphics/frustum.cpp \
           src/graphics/material.cpp \
           src/graphics/model3d.cpp \
           src/graphics/texture.cpp \
           src/graphics/vertex.cpp \
           src/graphics/viewport.cpp \
           src/io/file.reader.obj.cpp \
           src/io/output.cpp \
           src/io/tostring.cpp \
           src/scene/object.cpp \
           src/scene/predefs.cpp \
           src/scene/property.cpp \
           src/scene/scene.cpp \
           src/scene/viewer.cpp \
           src/system/debug.cpp \
           src/system/services.cpp \
           src/system/subsystem.cpp \
           src/types/matrix4.cpp \
           src/types/numerical.cpp \
           src/types/point3.cpp \
           src/types/point4.cpp \
           src/types/quaternion.cpp \
           src/types/vector3.cpp \
           src/ui/ui.component.cpp \
           src/ui/ui.cpp \
           src/ui/ui.display.cpp \
           src/ui/window.cpp \
           src/graphics/filter/image.filter.cpp \
           src/graphics/filter/texture.filter.cpp \
           src/graphics/line.algorithm/line.algorithm.cpp \
           src/graphics/primitive.mode/primitive.mode.cpp \
           src/graphics/projection/projection.cpp \
           src/graphics/projection/projection.factory.cpp \
           src/graphics/renderer/render.algorithm.cpp \
           src/scene/property/appearance.cpp \
           src/system/resource/resource.cpp \
           src/system/resource/resource.manager.cpp \
           src/system/subsystem/concurrency.subsystem.cpp \
           src/system/subsystem/graphics.subsystem.cpp \
           src/system/subsystem/physics.subsystem.cpp \
           src/ui/comboboxes/ui.combobox.cpp \
           src/ui/comboboxes/ui.combobox.framebuffer.resolution.cpp \
           src/ui/comboboxes/ui.combobox.image.filter.cpp \
           src/ui/comboboxes/ui.combobox.line.algorithm.cpp \
           src/ui/comboboxes/ui.combobox.primitive.mode.cpp \
           src/ui/comboboxes/ui.combobox.projection.cpp \
           src/ui/comboboxes/ui.combobox.renderer.cpp \
           src/ui/comboboxes/ui.combobox.texture.filter.cpp \
           src/ui/views/ui.view.cpp \
           src/ui/views/ui.view.scene.cpp \
           src/graphics/line.algorithm/algorithm/bresenham.line.algorithm.cpp \
           src/graphics/renderer/algorithms/bump.map.render.algorithm.cpp \
           src/graphics/renderer/algorithms/cel.shading.render.algorithm.cpp \
           src/graphics/renderer/algorithms/constant.shading.render.algorithm.cpp \
           src/graphics/renderer/algorithms/deferred.render.algorithm.cpp \
           src/graphics/renderer/algorithms/depth.map.render.algorithm.cpp \
           src/graphics/renderer/algorithms/normal.map.render.algorithm.cpp \
           src/graphics/renderer/algorithms/phong.shading.render.algorithm.cpp \
           src/graphics/renderer/algorithms/point.render.algorithm.cpp \
           src/graphics/renderer/algorithms/polygon.render.algorithm.cpp \
           src/graphics/renderer/algorithms/random.shading.render.algorithm.cpp \
           src/graphics/renderer/algorithms/texture.map.render.algorithm.cpp \
           src/graphics/renderer/algorithms/wireframe.render.algorithm.cpp
RESOURCES += clockwork.qrc
