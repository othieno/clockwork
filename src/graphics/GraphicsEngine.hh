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
#ifndef CLOCKWORK_GRAPHICS_ENGINE_HH
#define CLOCKWORK_GRAPHICS_ENGINE_HH

#include "RenderingContext.hh"
#include "RenderingAlgorithm.hh"
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
 * @see renderer/RenderingContext.hh.
 */
struct RenderingContext;
/**
 *
 */
class GraphicsEngine : public QObject {
	friend class Service;
public:
	/**
	 *
	 */
	GraphicsEngine(const GraphicsEngine&) = delete;
	/**
	 *
	 */
	GraphicsEngine(GraphicsEngine&&) = delete;
	/**
	 *
	 */
	GraphicsEngine& operator=(const GraphicsEngine&) = delete;
	/**
	 *
	 */
	GraphicsEngine& operator=(GraphicsEngine&&) = delete;
	/**
	 * Initializes the graphics engine.
	 * @param settings the application's settings.
	 */
	Error initialize(const ApplicationSettings& settings);
	/**
	 * Returns the framebuffer's current resolution.
	 */
	Framebuffer::Resolution getFramebufferResolution() const;
	/**
	 * Sets the framebuffer's resolution.
	 * @param resolution the resolution to set.
	 */
	void setFramebufferResolution(const Framebuffer::Resolution resolution);
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
	 * Returns the primitive topology.
	 */
	PrimitiveTopology getPrimitiveTopology() const;
	/**
	 * Sets the primitive topology.
	 * @param topology the primitive topology to set.
	 */
	void setPrimitiveTopology(const PrimitiveTopology topology);

	/**
	 * Returns true if clipping is enabled, false otherwise.
	 */
	bool isClippingEnabled() const;
	/**
	 * Toggles clipping.
	 * @param enabled enables clipping if set to true, disables it otherwise.
	 */
	void enableClipping(const bool enabled = true);
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
	 * Returns the line-drawing algorithm.
	 */
	LineDrawingAlgorithm getLineDrawingAlgorithm() const;
	/**
	 * Sets the line-drawing algorithm.
	 * @param algorithm the line-drawing algorithm to set.
	 */
	void setLineDrawingAlgorithm(const LineDrawingAlgorithm algorithm);
	/**
	 * Returns the polygon mode.
	 */
	PolygonMode getPolygonMode() const;
	/**
	 * Sets the polygon mode.
	 * @param mode the polygon mode to set.
	 */
	void setPolygonMode(const PolygonMode mode);
	/**
	 * Returns the shade model.
	 */
	ShadeModel getShadeModel() const;
	/**
	 * Sets the shade model.
	 * @param model the shade model to set.
	 */
	void setShadeModel(const ShadeModel model);
	/**
	 * Returns true if the scissor test is enabled, false otherwise.
	 */
	bool isScissorTestEnabled() const;
	/**
	 * Toggles the scissor test.
	 * @param enable enables the scissor test if set to true, disables it otherwise.
	 */
	void enableScissorTest(const bool enable);
	/**
	 * Returns true if the stencil test is enabled, false otherwise.
	 */
	bool isStencilTestEnabled() const;
	/**
	 * Toggles the stencil test.
	 * @param enable enables the stencil test if set to true, disables it otherwise.
	 */
	void enableStencilTest(const bool enable);
	/**
	 * Returns true if the depth test is enabled, false otherwise.
	 */
	bool isDepthTestEnabled() const;
	/**
	 * Toggles the depth test.
	 * @param enable enables the depth test if set to true, disables it otherwise.
	 */
	void enableDepthTest(const bool enable);
private:
	/**
	 * A pointer to a function that draws a mesh in a specified rendering context.
	 */
	typedef void (*DrawFunction)(const RenderingContext&, const Mesh&, Framebuffer&);
	/**
	 * Instantiates a GraphicsEngine object.
	 */
	GraphicsEngine() = default;
	/**
	 * Returns the specified rendering algorithm's draw function.
	 * @param algorithm the rendering algorithm to query.
	 */
	DrawFunction getDrawFunction(const RenderingAlgorithm algorithm);
	/**
	 * The rendering context.
	 */
	RenderingContext renderingContext_;
};
} // namespace clockwork
#endif // CLOCKWORK_GRAPHICS_ENGINE_HH
