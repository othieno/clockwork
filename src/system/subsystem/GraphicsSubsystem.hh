/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2016 Jeremy Othieno.
 *
 * The MIT License (MIT)
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef CLOCKWORK_GRAPHICS_SUBSYSTEM_HH
#define CLOCKWORK_GRAPHICS_SUBSYSTEM_HH

#include "RenderingContext.hh"
#include "Error.hh"


namespace clockwork {
/**
 * @see ApplicationSettings.hh.
 */
class ApplicationSettings;
/**
 * @see Mesh.hh.
 */
class Mesh;
/**
 * @see scene/Scene.hh.
 */
class Scene;
/**
 *
 */
class GraphicsSubsystem : public QObject {
	Q_OBJECT
	Q_PROPERTY(bool enableFpsCounter READ isFpsCounterEnabled WRITE enableFpsCounter NOTIFY fpsCounterToggled)
	Q_PROPERTY(int shaderProgram READ getShaderProgramIdentifier_ WRITE setShaderProgram_ NOTIFY shaderProgramChanged_)
	Q_PROPERTY(int primitiveTopology READ getPrimitiveTopology_ WRITE setPrimitiveTopology_ NOTIFY primitiveTopologyChanged_)
	Q_PROPERTY(bool enableClipping READ isClippingEnabled WRITE enableClipping NOTIFY clippingToggled)
	Q_PROPERTY(bool enableBackfaceCulling READ isBackfaceCullingEnabled WRITE enableBackfaceCulling NOTIFY backfaceCullingToggled)
	Q_PROPERTY(int polygonMode READ getPolygonMode_ WRITE setPolygonMode_ NOTIFY polygonModeChanged_)
	Q_PROPERTY(int shadeModel READ getShadeModel_ WRITE setShadeModel_ NOTIFY shadeModelChanged_)
	Q_PROPERTY(bool enableLineAntiAliasing READ isLineAntiAliasingEnabled WRITE enableLineAntiAliasing NOTIFY lineAntiAliasingToggled)
	Q_PROPERTY(bool enableScissorTest READ isScissorTestEnabled WRITE enableScissorTest NOTIFY scissorTestToggled)
	Q_PROPERTY(bool enableStencilTest READ isStencilTestEnabled WRITE enableStencilTest NOTIFY stencilTestToggled)
	Q_PROPERTY(bool enableDepthTest READ isDepthTestEnabled WRITE enableDepthTest NOTIFY depthTestToggled)
	Q_PROPERTY(QRectF normalizedScissorBox READ getNormalizedScissorBox WRITE setNormalizedScissorBox NOTIFY normalizedScissorBoxChanged)
	Q_PROPERTY(int framebufferResolution READ getFramebufferResolution_ WRITE setFramebufferResolution_ NOTIFY framebufferResolutionChanged_)
	Q_PROPERTY(int frameRenderTime READ getFrameRenderTime CONSTANT)
	friend class Service;
	static_assert(std::is_same<int, enum_traits<ShaderProgramIdentifier>::Ordinal>::value);
	static_assert(std::is_same<int, enum_traits<PrimitiveTopology>::Ordinal>::value);
	static_assert(std::is_same<int, enum_traits<PolygonMode>::Ordinal>::value);
	static_assert(std::is_same<int, enum_traits<ShadeModel>::Ordinal>::value);
	static_assert(std::is_same<int, enum_traits<Framebuffer::Resolution>::Ordinal>::value);
public:
	/**
	 *
	 */
	GraphicsSubsystem(const GraphicsSubsystem&) = delete;
	/**
	 *
	 */
	GraphicsSubsystem(GraphicsSubsystem&&) = delete;
	/**
	 *
	 */
	GraphicsSubsystem& operator=(const GraphicsSubsystem&) = delete;
	/**
	 *
	 */
	GraphicsSubsystem& operator=(GraphicsSubsystem&&) = delete;
	/**
	 * Initializes the graphics engine.
	 * @param settings the application's settings.
	 */
	Error initialize(const ApplicationSettings& settings);
	/**
	 * Returns the framebuffer's current resolution.
	 */
	const QSize& getFramebufferResolution() const;
	/**
	 * Returns the framebuffer resolution identifier as an integer value.
	 */
	inline int getFramebufferResolution_() const {
		return enum_traits<Framebuffer::Resolution>::ordinal(renderingContext_.framebuffer.getResolutionIdentifier());
	}
	/**
	 * Sets the framebuffer's resolution.
	 * @param resolutionIdentifier the identifier of the resolution to set.
	 */
	void setFramebufferResolution(const Framebuffer::Resolution resolutionIdentifier);
	/**
	 * Sets the framebuffer's resolution.
	 * @param resolution the integer value of the resolution identifier to set.
	 */
	inline void setFramebufferResolution_(const int resolution) {
		setFramebufferResolution(enum_traits<Framebuffer::Resolution>::enumerator(resolution));
	}
	/**
	 * Clears the framebuffer.
	 */
	void clear();
	/**
	 * Renders the specified scene.
	 */
	void render(const Scene& scene);
	/**
	 * Returns the framebuffer instance.
	 */
	Framebuffer& getFramebuffer();
	/**
	 * Returns true if the FPS counter is enabled, false otherwise.
	 */
	bool isFpsCounterEnabled() const;
	/**
	 * Toggles the FPS counter.
	 * @param enable enables the FPS counter if set to true, disables it otherwise.
	 */
	void enableFpsCounter(const bool enable = true);
	/**
	 * Returns the shader program identifier.
	 */
	ShaderProgramIdentifier getShaderProgramIdentifier() const;
	/**
	 * Returns the shader program identifier as an integer value.
	 */
	inline int getShaderProgramIdentifier_() const {
		return enum_traits<ShaderProgramIdentifier>::ordinal(getShaderProgramIdentifier());
	}
	/**
	 * Sets the shader program.
	 * @param identifier the identifier of the shader program to set.
	 */
	void setShaderProgram(const ShaderProgramIdentifier identifier);
	/**
	 * Sets the shader program.
	 * @param identifier the integer value of the identifier of the shader program to set.
	 */
	inline void setShaderProgram_(const int identifier) {
		setShaderProgram(enum_traits<ShaderProgramIdentifier>::enumerator(identifier));
	}
	/**
	 * Returns the primitive topology.
	 */
	PrimitiveTopology getPrimitiveTopology() const;
	/**
	 * Returns the primitive topology as an integer value.
	 */
	inline int getPrimitiveTopology_() const {
		return enum_traits<PrimitiveTopology>::ordinal(getPrimitiveTopology());
	}
	/**
	 * Sets the primitive topology.
	 * @param topology the primitive topology to set.
	 */
	void setPrimitiveTopology(const PrimitiveTopology topology);
	/**
	 * Sets the primitive topology.
	 * @param topology the integer value of the primitive topology to set.
	 */
	inline void setPrimitiveTopology_(const int topology) {
		setPrimitiveTopology(enum_traits<PrimitiveTopology>::enumerator(topology));
	}
	/**
	 * Returns true if clipping is enabled, false otherwise.
	 */
	bool isClippingEnabled() const;
	/**
	 * Toggles clipping.
	 * @param enable enables clipping if set to true, disables it otherwise.
	 */
	void enableClipping(const bool enable = true);
	/**
	 * Returns true if backface culling is enabled, false otherwise.
	 */
	bool isBackfaceCullingEnabled() const;
	/**
	 * Toggles backface culling.
	 * @param enable enables backface culling if set to true, disables it otherwise.
	 */
	void enableBackfaceCulling(const bool enable = true);
	/**
	 * Returns true if line anti-aliasing is enabled, false otherwise.
	 */
	bool isLineAntiAliasingEnabled() const;
	/**
	 * Toggles line anti-aliasing.
	 * @param enable enables line anti-aliasing if set to true, disables it otherwise.
	 */
	void enableLineAntiAliasing(const bool enable = true);
	/**
	 * Returns the polygon mode.
	 */
	PolygonMode getPolygonMode() const;
	/**
	 * Returns the polygon mode as an integer value.
	 */
	inline int getPolygonMode_() const {
		return enum_traits<PolygonMode>::ordinal(getPolygonMode());
	}
	/**
	 * Sets the polygon mode.
	 * @param mode the polygon mode to set.
	 */
	void setPolygonMode(const PolygonMode mode);
	/**
	 * Sets the polygon mode.
	 * @param mode the integer value of the polygon mode to set.
	 */
	inline void setPolygonMode_(const int mode) {
		setPolygonMode(enum_traits<PolygonMode>::enumerator(mode));
	}
	/**
	 * Returns the shade model.
	 */
	ShadeModel getShadeModel() const;
	/**
	 * Returns the shade model as an integer value.
	 */
	inline int getShadeModel_() const {
		return enum_traits<ShadeModel>::ordinal(getShadeModel());
	}
	/**
	 * Sets the shade model.
	 * @param model the shade model to set.
	 */
	void setShadeModel(const ShadeModel model);
	/**
	 * Sets the shade model.
	 * @param mode the integer value of the shade model to set.
	 */
	inline void setShadeModel_(const int model) {
		setShadeModel(enum_traits<ShadeModel>::enumerator(model));
	}
	/**
	 * Returns true if the scissor test is enabled, false otherwise.
	 */
	bool isScissorTestEnabled() const;
	/**
	 * Toggles the scissor test.
	 * @param enable enables the scissor test if set to true, disables it otherwise.
	 */
	void enableScissorTest(const bool enable = true);
	/**
	 * Returns true if the stencil test is enabled, false otherwise.
	 */
	bool isStencilTestEnabled() const;
	/**
	 * Toggles the stencil test.
	 * @param enable enables the stencil test if set to true, disables it otherwise.
	 */
	void enableStencilTest(const bool enable = true);
	/**
	 * Returns true if the depth test is enabled, false otherwise.
	 */
	bool isDepthTestEnabled() const;
	/**
	 * Toggles the depth test.
	 * @param enable enables the depth test if set to true, disables it otherwise.
	 */
	void enableDepthTest(const bool enable = true);
	/**
	 * Returns the viewport's normalized scissor box.
	 */
	const QRectF& getNormalizedScissorBox() const;
	/**
	 * Sets the viewport's normalized scissor box.
	 * @param scissorBox the normalized scissor box to set.
	 */
	void setNormalizedScissorBox(const QRectF& scissorBox);
	/**
	 * Returns the time it took to render the previous frame in milliseconds.
	 */
	int getFrameRenderTime() const {
		return frameRenderTime_;
	}
private:
	/**
	 * Instantiates a GraphicsSubsystem object.
	 */
	GraphicsSubsystem() = default;
	/**
	 * Returns the current shader program's draw command.
	 */
	void (*getDrawCommand())(const RenderingContext&, const Mesh&, Framebuffer&);
	/**
	 * Updates the viewport's scissor box based on the normalized scissor box
	 * and the framebuffer's current resolution.
	 */
	void updateScissorBox();
	/**
	 * The rendering context.
	 */
	RenderingContext renderingContext_;
	/**
	 * The time it took to render the previous frame in milliseconds.
	 */
	int frameRenderTime_;
signals:
	/**
	 * A signal that is emitted when the rendering context changes.
	 */
	void renderingContextChanged();
	/**
	 * A signal that is emitted when the FPS counter's visibility changes.
	 */
	void fpsCounterToggled(const bool visible);
	/**
	 * A signal that is emitted when the shader program changes.
	 * @param identifier the new shader program's identifier.
	 */
	void shaderProgramChanged(const ShaderProgramIdentifier identifier);
	/**
	 * A signal that is emitted when the shader program changes.
	 * @param identifier the integer value of the new shader program's identifier.
	 */
	void shaderProgramChanged_(const int identifier);
	/**
	 * A signal that is emitted when the primitive topology changes.
	 * @param topology the new primitive topology.
	 */
	void primitiveTopologyChanged(const PrimitiveTopology topology);
	/**
	 * A signal that is emitted when the primitive topology changes.
	 * @param topology the integer value of the new primitive topology.
	 */
	void primitiveTopologyChanged_(const int topology);
	/**
	 * A signal that is emitted when clipping is toggled.
	 */
	void clippingToggled(const bool enabled);
	/**
	 * A signal that is emitted when backface culling is toggled.
	 */
	void backfaceCullingToggled(const bool enabled);
	/**
	 * A signal that is emitted when the polygon mode changes.
	 * @param mode the new polygon mode.
	 */
	void polygonModeChanged(const PolygonMode mode);
	/**
	 * A signal that is emitted when the polygon mode changes.
	 * @param mode the integer value of the new polygon mode.
	 */
	void polygonModeChanged_(const int mode);
	/**
	 * A signal that is emitted when the shade model changes.
	 * @param model the new shade model.
	 */
	void shadeModelChanged(const ShadeModel model);
	/**
	 * A signal that is emitted when the shade model changes.
	 * @param model the integer value of the new shade model.
	 */
	void shadeModelChanged_(const int model);
	/**
	 * A signal that is emitted when the line anti-aliasing is toggled.
	 */
	void lineAntiAliasingToggled(const bool enabled);
	/**
	 * A signal that is emitted when the scissor test is toggled.
	 */
	void scissorTestToggled(const bool enabled);
	/**
	 * A signal that is emitted when the stencil test is toggled.
	 */
	void stencilTestToggled(const bool enabled);
	/**
	 * A signal that is emitted when the depth test is toggled.
	 */
	void depthTestToggled(const bool enabled);
	/**
	 * A signal that is emitted when the viewport's normalized scissor box changes.
	 * @param scissorBox the new scissor box.
	 */
	void normalizedScissorBoxChanged(const QRectF& scissorBox);
	/**
	 * A signal that is emitted when the framebuffer's resolution changes.
	 * @param resolution the new framebuffer resolution's identifier.
	 */
	void framebufferResolutionChanged(const Framebuffer::Resolution resolution);
	/**
	 * A signal that is emitted when the framebuffer's resolution changes.
	 * @param resolution the integer value of the new framebuffer resolution's identifier.
	 */
	void framebufferResolutionChanged_(const int resolution);
};
} // namespace clockwork
#endif // CLOCKWORK_GRAPHICS_SUBSYSTEM_HH
