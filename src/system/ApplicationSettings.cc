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
	}
}


clockwork::ShaderProgramIdentifier
ApplicationSettings::getShaderProgramIdentifier() const {
	using enum_traits = enum_traits<ShaderProgramIdentifier>;

	static_assert(std::is_same<int, enum_traits::Ordinal>::value);
	constexpr int DEFAULT_IDENTIFIER = enum_traits::ordinal(ShaderProgramIdentifier::Minimal);
	const int identifier = value(Key::ShaderProgramIdentifier, DEFAULT_IDENTIFIER).toInt();

	return enum_traits::enumerator(identifier);
}


void
ApplicationSettings::setShaderProgramIdentifier(const ShaderProgramIdentifier identifier) {
	if (getShaderProgramIdentifier() != identifier) {
		setValue(Key::ShaderProgramIdentifier, enum_traits<ShaderProgramIdentifier>::ordinal(identifier));
	}
}


clockwork::PrimitiveTopology
ApplicationSettings::getPrimitiveTopology() const {
	using enum_traits = enum_traits<PrimitiveTopology>;

	static_assert(std::is_same<int, enum_traits::Ordinal>::value);
	constexpr int DEFAULT_TOPOLOGY = enum_traits::ordinal(PrimitiveTopology::Triangle);
	const int topology = value(Key::PrimitiveTopology, DEFAULT_TOPOLOGY).toInt();

	return enum_traits::enumerator(topology);
}


void
ApplicationSettings::setPrimitiveTopology(const PrimitiveTopology topology) {
	if (getPrimitiveTopology() != topology) {
		setValue(Key::PrimitiveTopology, enum_traits<PrimitiveTopology>::ordinal(topology));
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
	}
}


bool
ApplicationSettings::isBackfaceCullingEnabled() const {
	return value(Key::EnableBackfaceCulling, true).toBool();
}


void
ApplicationSettings::enableBackfaceCulling(const bool enable) {
	if (isBackfaceCullingEnabled() != enable) {
		setValue(Key::EnableBackfaceCulling, enable);
	}
}


clockwork::PolygonMode
ApplicationSettings::getPolygonMode() const {
	using enum_traits = enum_traits<PolygonMode>;

	static_assert(std::is_same<int, enum_traits::Ordinal>::value);
	constexpr int DEFAULT_MODE = enum_traits::ordinal(PolygonMode::Fill);
	const int mode = value(Key::PolygonMode, DEFAULT_MODE).toInt();

	return enum_traits::enumerator(mode);
}


void
ApplicationSettings::setPolygonMode(const PolygonMode mode) {
	if (getPolygonMode() != mode) {
		setValue(Key::PolygonMode, enum_traits<PolygonMode>::ordinal(mode));
	}
}


clockwork::ShadeModel
ApplicationSettings::getShadeModel() const {
	using enum_traits = enum_traits<ShadeModel>;

	static_assert(std::is_same<int, enum_traits::Ordinal>::value);
	constexpr int DEFAULT_MODEL = enum_traits::ordinal(ShadeModel::Flat);
	const int model = value(Key::ShadeModel, DEFAULT_MODEL).toInt();

	return enum_traits::enumerator(model);
}


void
ApplicationSettings::setShadeModel(const ShadeModel model) {
	if (getShadeModel() != model) {
		setValue(Key::ShadeModel, enum_traits<ShadeModel>::ordinal(model));
	}
}


bool
ApplicationSettings::isLineAntiAliasingEnabled() const {
	return value(Key::EnableLineAntiAliasing, false).toBool();
}


void
ApplicationSettings::enableLineAntiAliasing(const bool enable) {
	if (isLineAntiAliasingEnabled() != enable) {
		setValue(Key::EnableLineAntiAliasing, enable);
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
	}
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
			return "theme/ShowBorderlessWindow";
		case Key::ShowFramesPerSecond:
			return "debug/ShowFramesPerSecond";
		case Key::ShaderProgramIdentifier:
			return "renderingcontext/ShaderProgram";
		case Key::PrimitiveTopology:
			return "renderingcontext/PrimitiveTopology";
		case Key::EnableClipping:
			return "renderingcontext/EnableClipping";
		case Key::EnableBackfaceCulling:
			return "renderingcontext/EnableBackfaceCulling";
		case Key::PolygonMode:
			return "renderingcontext/PolygonMode";
		case Key::ShadeModel:
			return "renderingcontext/ShadeModel";
		case Key::EnableLineAntiAliasing:
			return "renderingcontext/EnableLineAntiAliasing";
		case Key::EnableScissorTest:
			return "renderingcontext/EnableScissorTest";
		case Key::EnableStencilTest:
			return "renderingcontext/EnableStencilTest";
		case Key::EnableDepthTest:
			return "renderingcontext/EnableDepthTest";
		default:
			qFatal("[ApplicationSettings::keyToString] Undefined key!");
	}
}
