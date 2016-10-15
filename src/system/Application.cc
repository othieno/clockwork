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
#include "Application.hh"
#include "Service.hh"

using clockwork::Application;


Application::Application(int& argc, char** argv) :
QGuiApplication(argc, argv),
preferences_(*this),
userInterface_() {
	setApplicationName("Clockwork");
	setApplicationVersion("0.0.0");
	parseCommandLineArguments(argc, argv);
}


Application::~Application() {}


clockwork::Error
Application::initialize() {
	Framebuffer& framebuffer = Service::Graphics.getFramebuffer();
	framebuffer.setResolution(Framebuffer::Resolution::VGA);

	return userInterface_.initialize(*this);
}


QString
Application::applicationRepository() const {
	return QString("https://github.com/othieno/clockwork");
}


clockwork::ApplicationPreferences&
Application::getPreferences() {
	return preferences_;
}


void
Application::update() {
	Service::Graphics.clear();
	Service::Graphics.render(scene_);
}


void
Application::parseCommandLineArguments(int& argc, char** argv) {
	//TODO Implement me.
	Q_UNUSED(argc);
	Q_UNUSED(argv);
}
