# This file is part of Clockwork.
#
# Copyright (c) 2014-2016 Jeremy Othieno.
#
# The MIT License (MIT)
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

# Make sure the project is being built against Qt 5.5 or later.
greaterThan(QT_MAJOR_VERSION, 4):greaterThan(QT_MINOR_VERSION, 4) {
	# Include third-party project setups.
	include(resources/theme/material/material.pri)

	# Setup the compiler arguments.
	TEMPLATE = app
	TARGET = clockwork
	CONFIG += c++14
	QMAKE_CXXFLAGS += -Wextra
	INCLUDEPATH += \
		src/graphics \
		src/graphics/filter \
		src/graphics/renderer \
		src/graphics/renderer/shader \
		src/math \
		src/scene \
		src/scene/predefined \
		src/scene/property \
		src/system \
		src/system/io \
		src/system/task \
		src/types \
		src/ui \
		src
	HEADERS += \
		src/graphics/Camera.hh \
		src/graphics/Color.hh \
		src/graphics/Framebuffer.hh \
		src/graphics/GraphicsEngine.hh \
		src/graphics/Material.hh \
		src/graphics/Mesh.hh \
		src/graphics/Projection.hh \
		src/graphics/Texture.hh \
		src/graphics/Viewport.hh \
		src/graphics/filter/ImageFilter.hh \
		src/graphics/filter/ImageFilterFactory.hh \
		src/graphics/filter/TextureFilter.hh \
		src/graphics/filter/TextureFilterFactory.hh \
		src/graphics/renderer/LineDrawingAlgorithm.hh \
		src/graphics/renderer/PointRenderer.hh \
		src/graphics/renderer/PolygonRenderer.hh \
		src/graphics/renderer/Primitive.hh \
		src/graphics/renderer/Renderer.hh \
		src/graphics/renderer/RenderingAlgorithm.hh \
		src/graphics/renderer/RenderingContext.hh \
		src/graphics/renderer/WireframeRenderer.hh \
		src/graphics/renderer/shader/Fragment.hh \
		src/graphics/renderer/shader/BumpMapShaderProgram.hh \
		src/graphics/renderer/shader/CelShadingShaderProgram.hh \
		src/graphics/renderer/shader/DepthMapShaderProgram.hh \
		src/graphics/renderer/shader/FlatShadingShaderProgram.hh \
		src/graphics/renderer/shader/GouraudShadingShaderProgram.hh \
		src/graphics/renderer/shader/NormalMapShaderProgram.hh \
		src/graphics/renderer/shader/PhongShadingShaderProgram.hh \
		src/graphics/renderer/shader/RandomShadingShaderProgram.hh \
		src/graphics/renderer/shader/ShaderProgram.hh \
		src/graphics/renderer/shader/TextureMapShaderProgram.hh \
		src/graphics/renderer/shader/Uniform.hh \
		src/graphics/renderer/shader/Vertex.hh \
		src/graphics/renderer/shader/VertexAttributes.hh \
		src/math/Frustum.hh \
		src/math/lerp.hh \
		src/math/Matrix4.hh \
		src/math/Point.hh \
		src/math/Point3.hh \
		src/math/Quaternion.hh \
		src/math/Vector3.hh \
		src/math/Vector4.hh \
		src/scene/predefined/Suzanne.hh \
		src/scene/predefined/TexturedCube.hh \
		src/scene/predefined/Triangle.hh \
		src/scene/Scene.hh \
		src/scene/SceneNode.hh \
		src/scene/SceneObject.hh \
		src/scene/SceneObjectProperty.hh \
		src/scene/SceneViewer.hh \
		src/scene/property/SceneObjectAppearance.hh \
		src/system/Application.hh \
		src/system/ApplicationPreferences.hh \
		src/system/Error.hh \
		src/system/Service.hh \
		src/system/io/fileReader.hh \
		src/system/io/Resource.hh \
		src/system/io/ResourceManager.hh \
		src/system/io/toString.hh \
		src/system/task/Task.hh \
		src/system/task/TaskManager.hh \
		src/types/Factory.hh \
		src/types/WeakVariant.hh \
		src/ui/FramebufferProvider.hh \
		src/ui/UserInterface.hh
	SOURCES += \
		src/graphics/Camera.cc \
		src/graphics/Color.cc \
		src/graphics/Framebuffer.cc \
		src/graphics/GraphicsEngine.cc \
		src/graphics/Material.cc \
		src/graphics/Mesh.cc \
		src/graphics/Texture.cc \
		src/graphics/filter/ImageFilter.cc \
		src/graphics/filter/TextureFilter.cc \
		src/graphics/renderer/PointRenderer.cc \
		src/graphics/renderer/WireframeRenderer.cc \
		src/graphics/renderer/shader/Fragment.cc \
		src/graphics/renderer/shader/BumpMapShaderProgram.cc \
		src/graphics/renderer/shader/CelShadingShaderProgram.cc \
		src/graphics/renderer/shader/DepthMapShaderProgram.cc \
		src/graphics/renderer/shader/FlatShadingShaderProgram.cc \
		src/graphics/renderer/shader/GouraudShadingShaderProgram.cc \
		src/graphics/renderer/shader/NormalMapShaderProgram.cc \
		src/graphics/renderer/shader/PhongShadingShaderProgram.cc \
		src/graphics/renderer/shader/RandomShadingShaderProgram.cc \
		src/graphics/renderer/shader/TextureMapShaderProgram.cc \
		src/graphics/renderer/shader/Vertex.cc \
		src/graphics/renderer/shader/VertexAttributes.cc \
		src/graphics/Viewport.cc \
		src/math/Frustum.cc \
		src/math/lerp.cc \
		src/math/Matrix4.cc \
		src/math/Point.cc \
		src/math/Point3.cc \
		src/math/Point4.cc \
		src/math/Quaternion.cc \
		src/math/Vector3.cc \
		src/scene/predefined/Suzanne.cc \
		src/scene/predefined/TexturedCube.cc \
		src/scene/predefined/Triangle.cc \
		src/scene/Scene.cc \
		src/scene/SceneNode.cc \
		src/scene/SceneObject.cc \
		src/scene/SceneObjectProperty.cc \
		src/scene/SceneViewer.cc \
		src/scene/property/SceneObjectAppearance.cc \
		src/system/Application.cc \
		src/system/ApplicationPreferences.cc \
		src/system/Service.cc \
		src/system/io/fileReader.cc \
		src/system/io/Resource.cc \
		src/system/io/ResourceManager.cc \
		src/system/io/toString.cc \
		src/system/task/Task.cc \
		src/system/task/TaskManager.cc \
		src/ui/FramebufferProvider.cc \
		src/ui/UserInterface.cc \
		src/clockwork.cc

	# Add resource file configurations.
	RESOURCES += clockwork.qrc

	# Setup the build output directories.
	DESTDIR = build
	OBJECTS_DIR = $${DESTDIR}/obj
	MOC_DIR = $${DESTDIR}/moc
	RCC_DIR = $${DESTDIR}/rcc
	UI_DIR = $${DESTDIR}/ui
} else {
	error(\
		"Building Clockwork requires Qt 5.5."\
		"Make sure your version of qmake is using the Qt 5.5 libraries, or later." \
		"You can find out which version is currently being used by running 'qmake --version'."\
	)
}
