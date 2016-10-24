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
#include "ApplicationSettings.hh"
#include "Application.hh"
#include "Framebuffer.hh"
#include "Service.hh"
#include "toString.hh"
#include <QStandardPaths>

using clockwork::ApplicationSettings;


ApplicationSettings::ApplicationSettings(Application& application) :
QSettings(QString("./clockwork-preferences.pro.user"), Format::IniFormat) {
//FIXME QStandardPaths::AppConfigLocation requires Qt 5.5 at least.
//TODO Add requirement to clockwork.pro file.
//QSettings(QString("%1/preferences.ini").arg(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)), Format::IniFormat) {
	Q_UNUSED(application);
}


bool
ApplicationSettings::isFpsCounterVisible() const {
	return value(Key::ShowFramesPerSecond, false).toBool();
}


void
ApplicationSettings::showFpsCounter(const bool visible) {
	if (isFpsCounterVisible() != visible) {
		setValue(Key::ShowFramesPerSecond, visible);
		emit fpsCounterVisibilityChanged(visible);
	}
}


bool
ApplicationSettings::isDepthTestingEnabled() const {
	const bool defaultValue = Service::Graphics.isDepthTestingEnabled();
	return value(Key::EnableDepthTesting, defaultValue).toBool();
}


void
ApplicationSettings::enableDepthTesting(const bool enable) {
	if (isDepthTestingEnabled() != enable) {
		setValue(Key::ShowFramesPerSecond, enable);
		emit depthTestingChanged(enable);
	}
}


QStringList
ApplicationSettings::getAvailableLanguages() {
	QStringList languages;
	languages.append("English");


	return languages;
}


QStringList
ApplicationSettings::getAvailableFramebufferResolutions() {
	QStringList resolutions;
	for (const auto resolution : Framebuffer::getAvailableResolutions()) {
		resolutions.append(toString(resolution));
	}
	return resolutions;
}


bool
ApplicationSettings::contains(const Key key) const {
	return QSettings::contains(ApplicationSettings::keyToString(key));
}


QVariant
ApplicationSettings::value(const Key key, const QVariant& defaultValue) const {
	return QSettings::value(ApplicationSettings::keyToString(key), defaultValue);
}


void
ApplicationSettings::setValue(const Key key, const QVariant& value) {
	QSettings::setValue(ApplicationSettings::keyToString(key), value);
}


QString
ApplicationSettings::keyToString(const Key key) {
	switch (key) {
		case Key::ShowFramesPerSecond:
			return "showFramesPerSecond";
		case Key::EnableDepthTesting:
			return "enableDepthTesting";
		default:
			qFatal("[ApplicationSettings::keyToString] Undefined key!");
	}
}
