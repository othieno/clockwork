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
#ifndef CLOCKWORK_APPLICATION_HH
#define CLOCKWORK_APPLICATION_HH

#include <QGuiApplication>
#include "ApplicationSettings.hh"
#include "Error.hh"
#include "UserInterface.hh"
#include "Scene.hh"


namespace clockwork {
/**
 *
 */
class Application final : public QGuiApplication {
	Q_OBJECT
	Q_PROPERTY(QString applicationRepository READ applicationRepository CONSTANT)
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
	 * Returns the application's source code repository URL.
	 */
	QString applicationRepository() const;
	/**
	 * Initializes the application.
	 */
	Error initialize();
	/**
	 * Returns the application's configuration settings.
	 */
	ApplicationSettings& getSettings();
	/**
	 * Updates the application's state.
	 */
	Q_INVOKABLE void update();
private:
	/**
	 * Parses the specified command line arguments.
	 */
	void parseCommandLineArguments(int& argc, char** argv);
	/**
	 * The application's configuration settings.
	 */
	ApplicationSettings settings_;
	/**
	 * The application's user interface.
	 */
	UserInterface userInterface_;
	/**
	 * The application's scene.
	 */
	Scene scene_;
signals:
	/**
	 * A signal that is emitted when the update process is completed.
	 */
	void updateCompleted();
};
} // namespace clockwork

#endif // CLOCKWORK_APPLICATION_HH
