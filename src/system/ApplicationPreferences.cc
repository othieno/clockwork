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
#include "ApplicationPreferences.hh"
#include "Application.hh"
#include "Framebuffer.hh"
#include "toString.hh"
#include <QStandardPaths>

using clockwork::ApplicationPreferences;


ApplicationPreferences::ApplicationPreferences(Application& application) :
QSettings(QString("./clockwork-preferences.pro.user"), Format::IniFormat) {
//FIXME QStandardPaths::AppConfigLocation requires Qt 5.5 at least.
//TODO Add requirement to clockwork.pro file.
//QSettings(QString("%1/preferences.ini").arg(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)), Format::IniFormat) {
	Q_UNUSED(application);
}


bool
ApplicationPreferences::isFpsCounterVisible() const {
	return value(Key::ShowFramesPerSecond, false).toBool();
}


void
ApplicationPreferences::showFpsCounter(const bool visible) {
	if (isFpsCounterVisible() != visible) {
		setValue(Key::ShowFramesPerSecond, visible);
		emit fpsCounterVisibilityChanged(visible);
	}
}


QStringList
ApplicationPreferences::getAvailableLanguages() {
	QStringList languages;
	languages.append("English");


	return languages;
}


QStringList
ApplicationPreferences::getAvailableFramebufferResolutions() {
	QStringList resolutions;
	for (const auto resolution : Framebuffer::getAvailableResolutions()) {
		resolutions.append(toString(resolution));
	}
	return resolutions;
}


bool
ApplicationPreferences::contains(const Key key) const {
	return QSettings::contains(ApplicationPreferences::keyToString(key));
}


QVariant
ApplicationPreferences::value(const Key key, const QVariant& defaultValue) const {
	return QSettings::value(ApplicationPreferences::keyToString(key), defaultValue);
}


void
ApplicationPreferences::setValue(const Key key, const QVariant& value) {
	QSettings::setValue(ApplicationPreferences::keyToString(key), value);
}


QString
ApplicationPreferences::keyToString(const Key key) {
	switch (key) {
		case Key::ShowFramesPerSecond:
			return "showFramesPerSecond";
		default:
			qFatal("[ApplicationPreferences::keyToString] Undefined key!");
	}
}
