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
#include "toString.hh"
#include "enum_traits.hh"
#include <QStandardPaths>

using clockwork::ApplicationSettings;


ApplicationSettings::ApplicationSettings() :
QSettings(QString("./clockwork-preferences.pro.user"), Format::IniFormat) {
//QSettings(QString("%1/configuration.ini").arg(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)), Format::IniFormat) {
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
ApplicationSettings::isWindowBorderless() const {
	return value(Key::ShowBorderlessWindow, false).toBool();
}


void
ApplicationSettings::showBorderlessWindow(const bool visible) {
	if (isWindowBorderless() != visible) {
		setValue(Key::ShowBorderlessWindow, visible);
		emit windowBorderVisibilityChanged(visible);
	}
}


bool
ApplicationSettings::isClippingEnabled() const {
	return value(Key::EnableClipping, true).toBool();
}


void
ApplicationSettings::enableClipping(const bool enable) {
	if (isClippingEnabled() != enable) {
		setValue(Key::EnableClipping, enable);
		emit clippingToggled(enable);
	}
}


bool
ApplicationSettings::isScissorTestEnabled() const {
	return value(Key::EnableScissorTest, false).toBool();
}


void
ApplicationSettings::enableScissorTest(const bool enable) {
	if (isScissorTestEnabled() != enable) {
		setValue(Key::EnableScissorTest, enable);
		emit scissorTestChanged(enable);
	}
}


bool
ApplicationSettings::isStencilTestEnabled() const {
	return value(Key::EnableStencilTest, false).toBool();
}


void
ApplicationSettings::enableStencilTest(const bool enable) {
	if (isStencilTestEnabled() != enable) {
		setValue(Key::EnableStencilTest, enable);
		emit stencilTestChanged(enable);
	}
}


bool
ApplicationSettings::isDepthTestEnabled() const {
	return value(Key::EnableDepthTest, true).toBool();
}


void
ApplicationSettings::enableDepthTest(const bool enable) {
	if (isDepthTestEnabled() != enable) {
		setValue(Key::EnableDepthTest, enable);
		emit depthTestChanged(enable);
	}
}


int
ApplicationSettings::getPrimitiveTopology() const {
	static_assert(std::is_same<int, clockwork::enum_traits<clockwork::PrimitiveTopology>::Ordinal>::value);
	return value(
		Key::PrimitiveTopology,
		enum_traits<PrimitiveTopology>::ordinal(PrimitiveTopology::Triangle)
	).toInt();
}


void
ApplicationSettings::setPrimitiveTopology(const int topology) {
	if (getPrimitiveTopology() != topology) {
		setValue(Key::PrimitiveTopology, topology);
		emit primitiveTopologyChanged_(topology);
		emit primitiveTopologyChanged(enum_traits<PrimitiveTopology>::enumerator(topology));
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
		case Key::ShowBorderlessWindow:
			return "showBorderlessWindow";
		case Key::ShowFramesPerSecond:
			return "showFramesPerSecond";
		case Key::PrimitiveTopology:
			return "primitiveTopology";
		case Key::EnableClipping:
			return "enableClipping";
		case Key::EnableScissorTest:
			return "enableScissorTest";
		case Key::EnableStencilTest:
			return "enableStencilTest";
		case Key::EnableDepthTest:
			return "enableDepthTest";
		default:
			qFatal("[ApplicationSettings::keyToString] Undefined key!");
	}
}
