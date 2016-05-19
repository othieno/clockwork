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
 *
 */
class TaskManager;
/**
 *
 */
class Scene;
/**
 *
 */
class GraphicsEngine {
public:
    /**
     *
     */
    explicit GraphicsEngine(TaskManager&);
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
     * Returns the framebuffer instance.
     */
    Framebuffer& getFramebuffer();
private:
    /**
     * The task manager.
     */
    TaskManager& taskManager_;
    /**
     * The framebuffer.
     */
    Framebuffer framebuffer_;
};
} // namespace clockwork
#endif // CLOCKWORK_GRAPHICS_ENGINE_HH
