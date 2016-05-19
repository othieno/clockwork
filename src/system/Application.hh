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
#ifndef CLOCKWORK_APPLICATION_HH
#define CLOCKWORK_APPLICATION_HH

#include <QGuiApplication>
#include "Error.hh"
#include "TaskManager.hh"
#include "GraphicsEngine.hh"
#include "UserInterface.hh"


namespace clockwork {
/**
 *
 */
class Application final : public QGuiApplication {
    Q_OBJECT
public:
    /**
     * Instantiates the application.
     */
    Application(int& argc, char** argv);
    /**
     *
     */
    Application(const Application&) = delete;
    /**
     *
     */
    Application(Application&&) = delete;
    /**
     *
     */
    ~Application();
    /**
     *
     */
    Application& operator=(const Application&) = delete;
    /**
     *
     */
    Application& operator=(Application&&) = delete;
    /**
     * Initializes the application.
     */
    Error initialize();
    /**
     * Returns the task manager instance.
     */
    TaskManager& getTaskManager();
    /**
     * Returns the graphics engine instance.
     */
    GraphicsEngine& getGraphicsEngine();
private:
    /**
     * The task manager.
     */
    TaskManager taskManager_;
    /**
     * The graphics engine.
     */
    GraphicsEngine graphicsEngine_;
    /**
     * The application's user interface.
     */
    UserInterface userInterface_;
};
} // namespace clockwork

#endif // CLOCKWORK_APPLICATION_HH
