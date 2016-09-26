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


namespace clockwork {
/**
 * see Fragment.hh.
 */
class Fragment;
/**
 * @see scene/Scene.hh.
 */
class Scene;
/**
 * @see scene/SceneObject.hh.
 */
class SceneObject;
/**
 * @see scene/SceneViewer.hh.
 */
class SceneViewer;
/**
 * @see system/Service.hh.
 */
class Service;
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
     * Renders the specified scene.
     */
    void render(const Scene& scene);
    /**
     * Renders the specified scene object from the given viewer's point of view.
     * @param viewer the object viewing the scene.
     * @param object the scene object to render.
     */
    void renderObject(const SceneViewer& viewer, const SceneObject& object);
    /**
     * Returns the framebuffer instance.
     */
    Framebuffer& getFramebuffer();
    /**
     * Returns true if the specified fragment passes all fragment tests, false otherwise.
     * @param fragment the Fragment instance to test.
     */
    bool fragmentPasses(const Fragment& fragment);
private:
    /**
     *
     */
    GraphicsEngine();
    /**
     * The framebuffer.
     */
    Framebuffer framebuffer_;
};
} // namespace clockwork
#endif // CLOCKWORK_GRAPHICS_ENGINE_HH
