/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2014-2016 Jeremy Othieno.
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

#include "Framebuffer.hh"
#include "RenderingAlgorithm.hh"
#include "LineDrawingAlgorithm.hh"


namespace clockwork {
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
class GraphicsEngine {
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
    ~GraphicsEngine();
    /**
     *
     */
    GraphicsEngine& operator=(const GraphicsEngine&) = delete;
    /**
     *
     */
    GraphicsEngine& operator=(GraphicsEngine&&) = delete;
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
     * Returns the line-drawing algorithm.
     */
    LineDrawingAlgorithm getLineDrawingAlgorithm() const;
    /**
     * Sets the line-drawing algorithm.
     * @param algorithm the line-drawing algorithm to set.
     */
    void setLineDrawingAlgorithm(const LineDrawingAlgorithm algorithm);
    /**
     * Returns true if depth testing is enabled, false otherwise.
     */
    bool isDepthTestingEnabled() const;
    /**
     * Toggles depth testing.
     * @param enable enables depth testing if set to true, disables it otherwise.
     */
    void enableDepthTesting(const bool enable);
private:
    /**
     * A pointer to a function that draws a mesh in a specified rendering context.
     */
    typedef void (*DrawFunction)(RenderingContext&, const Mesh&);
    /**
     * Instantiates a GraphicsEngine object.
     */
    GraphicsEngine();
    /**
     * Returns the specified rendering algorithm's draw function.
     * @param algorithm the rendering algorithm to query.
     */
    DrawFunction getDrawFunction(const RenderingAlgorithm algorithm);
    /**
     * The framebuffer.
     */
    Framebuffer framebuffer_;
    /**
     * The line-drawing algorithm to use.
     */
    LineDrawingAlgorithm lineDrawingAlgorithm_;
    /**
     * If set to true, depth testing will be performed on fragments
     * before being written to the framebuffer.
     */
    bool enableDepthTesting_;
};
} // namespace clockwork
#endif // CLOCKWORK_GRAPHICS_ENGINE_HH
