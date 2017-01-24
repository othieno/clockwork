# This file is part of Clockwork.
#
# Copyright (c) 2013-2016 Jeremy Othieno.
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
	# Include theme configurations.
	include(src/ui/theme/material/material.pri)
	include(src/ui/theme/atomic/atomic.pri)

	# Setup the compiler arguments.
	TEMPLATE = app
	TARGET = clockwork
	VERSION = 0.0.0
	REPOSITORY = "https://github.com/othieno/clockwork"
	CONFIG += c++14
	QMAKE_CXXFLAGS += -Wextra
	INCLUDEPATH += \
		src/graphics/filter \
		src/graphics/lighting \
		src/graphics/renderer/shader \
		src/graphics/renderer \
		src/graphics \
		src/math \
		src/scene/predefined \
		src/scene/property \
		src/scene \
		src/system/io \
		src/system/task \
		src/system \
		src/types \
		src/ui/components \
		src/ui/models \
		src/ui \
		src
	HEADERS += \
		src/graphics/Camera.hh \
		src/graphics/Color.hh \
		src/graphics/GraphicsEngine.hh \
		src/graphics/Material.hh \
		src/graphics/Mesh.hh \
		src/graphics/Projection.hh \
		src/graphics/Texture.hh \
		src/graphics/ViewFrustum.hh \
		src/graphics/Viewport.hh \
		src/graphics/filter/ImageFilter.hh \
		src/graphics/filter/ImageFilterFactory.hh \
		src/graphics/filter/TextureFilter.hh \
		src/graphics/filter/TextureFilterFactory.hh \
		src/graphics/lighting/IlluminationModel.hh \
		src/graphics/renderer/BaseFragment.hh \
		src/graphics/renderer/BaseShaderProgram.hh \
		src/graphics/renderer/BaseVertex.hh \
		src/graphics/renderer/BaseVertexAttributes.hh \
		src/graphics/renderer/Framebuffer.hh \
		src/graphics/renderer/PolygonMode.hh \
		src/graphics/renderer/PrimitiveTopology.hh \
		src/graphics/renderer/Renderer.hh \
		src/graphics/renderer/Renderer.inl \
		src/graphics/renderer/RenderingAlgorithm.hh \
		src/graphics/renderer/RenderingContext.hh \
		src/graphics/renderer/ShadeModel.hh \
		src/graphics/renderer/Uniform.hh \
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
		src/math/lerp.hh \
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
		src/system/ApplicationSettings.hh \
		src/system/Error.hh \
		src/system/Service.hh \
		src/system/io/fileReader.hh \
		src/system/io/Resource.hh \
		src/system/io/ResourceManager.hh \
		src/system/io/toString.hh \
		src/system/task/Task.hh \
		src/system/task/TaskManager.hh \
		src/types/enum_traits.hh \
		src/types/Factory.hh \
		src/types/WeakVariant.hh \
		src/ui/components/FramebufferView.hh \
		src/ui/models/SelectModel.hh \
		src/ui/FramebufferProvider.hh \
		src/ui/UserInterface.hh
	SOURCES += \
		src/graphics/Camera.cc \
		src/graphics/Color.cc \
		src/graphics/GraphicsEngine.cc \
		src/graphics/Material.cc \
		src/graphics/Mesh.cc \
		src/graphics/Texture.cc \
		src/graphics/filter/ImageFilter.cc \
		src/graphics/filter/TextureFilter.cc \
		src/graphics/renderer/BaseFragment.cc \
		src/graphics/renderer/BaseVertex.cc \
		src/graphics/renderer/BaseVertexAttributes.cc \
		src/graphics/renderer/Framebuffer.cc \
		src/graphics/renderer/shader/BumpMapShaderProgram.cc \
		src/graphics/renderer/shader/CelShadingShaderProgram.cc \
		src/graphics/renderer/shader/DepthMapShaderProgram.cc \
		src/graphics/renderer/shader/FlatShadingShaderProgram.cc \
		src/graphics/renderer/shader/GouraudShadingShaderProgram.cc \
		src/graphics/renderer/shader/NormalMapShaderProgram.cc \
		src/graphics/renderer/shader/PhongShadingShaderProgram.cc \
		src/graphics/renderer/shader/RandomShadingShaderProgram.cc \
		src/graphics/renderer/shader/TextureMapShaderProgram.cc \
		src/graphics/ViewFrustum.cc \
		src/graphics/Viewport.cc \
		src/math/lerp.cc \
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
		src/system/ApplicationSettings.cc \
		src/system/Service.cc \
		src/system/io/fileReader.cc \
		src/system/io/Resource.cc \
		src/system/io/ResourceManager.cc \
		src/system/io/toString.cc \
		src/system/task/Task.cc \
		src/system/task/TaskManager.cc \
		src/ui/components/FramebufferView.cc \
		src/ui/models/SelectModel.cc \
		src/ui/FramebufferProvider.cc \
		src/ui/UserInterface.cc \
		src/clockwork.cc

	DEFINES += \
		APPLICATION_VERSION=\\\"$$VERSION\\\" \
		APPLICATION_REPOSITORY=\\\"$$REPOSITORY\\\" \
		QPM_INIT\\(E\\)=\"E.addImportPath(QStringLiteral(\\\"qrc:/\\\"));\"

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
