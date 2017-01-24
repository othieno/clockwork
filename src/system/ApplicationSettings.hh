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
#ifndef CLOCKWORK_APPLICATION_SETTINGS_HH
#define CLOCKWORK_APPLICATION_SETTINGS_HH

#include <QSettings>
#include "BaseShaderProgram.hh"
#include "PrimitiveTopology.hh"
#include "PolygonMode.hh"
#include "ShadeModel.hh"


namespace clockwork {
/**
 *
 */
class Application;
/**
 *
 */
class ApplicationSettings : public QSettings {
	Q_OBJECT
	Q_PROPERTY(bool showFramesPerSecond READ isFpsCounterVisible WRITE showFpsCounter NOTIFY fpsCounterVisibilityChanged)
	Q_PROPERTY(bool showBorderlessWindow READ isWindowBorderless WRITE showBorderlessWindow NOTIFY windowBorderVisibilityChanged)
	Q_PROPERTY(int shaderProgram READ getShaderProgramOrdinal WRITE setShaderProgram NOTIFY shaderProgramChanged_)
	Q_PROPERTY(int primitiveTopology READ getPrimitiveTopologyOrdinal WRITE setPrimitiveTopology NOTIFY primitiveTopologyChanged_)
	Q_PROPERTY(bool enableClipping READ isClippingEnabled WRITE enableClipping NOTIFY clippingToggled)
	Q_PROPERTY(bool enableBackfaceCulling READ isBackfaceCullingEnabled WRITE enableBackfaceCulling NOTIFY backfaceCullingToggled)
	Q_PROPERTY(int polygonMode READ getPolygonModeOrdinal WRITE setPolygonMode NOTIFY polygonModeChanged_)
	Q_PROPERTY(int shadeModel READ getShadeModelOrdinal WRITE setShadeModel NOTIFY shadeModelChanged_)
	Q_PROPERTY(bool enableScissorTest READ isScissorTestEnabled WRITE enableScissorTest NOTIFY scissorTestChanged)
	Q_PROPERTY(bool enableStencilTest READ isStencilTestEnabled WRITE enableStencilTest NOTIFY stencilTestChanged)
	Q_PROPERTY(bool enableDepthTest READ isDepthTestEnabled WRITE enableDepthTest NOTIFY depthTestChanged)
	Q_PROPERTY(QString fileLocation READ fileName CONSTANT)
	Q_PROPERTY(QStringList availableLanguages READ getAvailableLanguages CONSTANT)
	Q_PROPERTY(QStringList availableFramebufferResolutions READ getAvailableFramebufferResolutions CONSTANT)
	friend class Application;
public:
	/**
	 * Returns true if the FPS counter should be visible, false otherwise.
	 */
	bool isFpsCounterVisible() const;
	/**
	 * Sets the FPS counter's visibility.
	 * @param visible makes the FPS counter visible if set to true, hides it otherwise.
	 */
	void showFpsCounter(const bool visible);
	/**
	 * Returns true if the window borders are visible, false otherwise.
	 */
	bool isWindowBorderless() const;
	/**
	 * Sets the visibility of the window's borders.
	 * @param visible makes the borders visible if set to true, hides them otherwise.
	 */
	void showBorderlessWindow(const bool visible);
	/**
	 * Returns the shader program's integer value.
	 */
	int getShaderProgramOrdinal() const;
	static_assert(std::is_same<int, enum_traits<BaseShaderProgram::Identifier>::Ordinal>::value);
	/**
	 * Returns the shader program.
	 */
	inline BaseShaderProgram::Identifier getShaderProgram() const {
		return enum_traits<BaseShaderProgram::Identifier>::enumerator(getShaderProgramOrdinal());
	}
	/**
	 * Sets the shader program.
	 * @param identifier the integer value of the shader program identifier to set.
	 */
	void setShaderProgram(const int identifier);
	/**
	 * Returns the primitive topology's integer value.
	 */
	int getPrimitiveTopologyOrdinal() const;
	static_assert(std::is_same<int, enum_traits<PrimitiveTopology>::Ordinal>::value);
	/**
	 * Returns the primitive topology.
	 */
	inline PrimitiveTopology getPrimitiveTopology() const {
		return enum_traits<PrimitiveTopology>::enumerator(getPrimitiveTopologyOrdinal());
	}
	/**
	 * Sets the primitive topology.
	 * @param topology the integer value of the primitive topology to set.
	 */
	void setPrimitiveTopology(const int topology);
	/**
	 * Returns true if clipping is enabled, false otherwise.
	 */
	bool isClippingEnabled() const;
	/**
	 * Toggles clipping.
	 * @param enable enables clipping if set to true, disables it otherwise.
	 */
	void enableClipping(const bool enable);
	/**
	 * Returns true if backface culling is enabled, false otherwise.
	 */
	bool isBackfaceCullingEnabled() const;
	/**
	 * Toggles backface culling.
	 * @param enable enables backface culling if set to true, disables it otherwise.
	 */
	void enableBackfaceCulling(const bool enable);
	/**
	 * Returns the polygon mode's integer value.
	 */
	int getPolygonModeOrdinal() const;
	static_assert(std::is_same<int, enum_traits<PolygonMode>::Ordinal>::value);
	/**
	 * Returns the polygon mode.
	 */
	inline PolygonMode getPolygonMode() const {
		return enum_traits<PolygonMode>::enumerator(getPolygonModeOrdinal());
	}
	/**
	 * Sets the polygon mode.
	 * @param mode the integer value of the polygon mode to set.
	 */
	void setPolygonMode(const int mode);
	/**
	 * Returns the shade model's integer value.
	 */
	int getShadeModelOrdinal() const;
	static_assert(std::is_same<int, enum_traits<ShadeModel>::Ordinal>::value);
	/**
	 * Returns the shade model.
	 */
	inline ShadeModel getShadeModel() const {
		return enum_traits<ShadeModel>::enumerator(getShadeModelOrdinal());
	}
	/**
	 * Sets the shade model.
	 * @param model the integer value of the shade model to set.
	 */
	void setShadeModel(const int model);
	/**
	 * Returns true if the scissor test is enabled, false otherwise.
	 */
	bool isScissorTestEnabled() const;
	/**
	 * Toggles the scissor test.
	 * @param enable enables the scissor test if set to true, disables it otherwise.
	 */
	void enableScissorTest(const bool enable);
	/**
	 * Returns true if the stencil test is enabled, false otherwise.
	 */
	bool isStencilTestEnabled() const;
	/**
	 * Toggles the stencil test.
	 * @param enable enables the stencil test if set to true, disables it otherwise.
	 */
	void enableStencilTest(const bool enable);
	/**
	 * Returns true if the depth test is enabled, false otherwise.
	 */
	bool isDepthTestEnabled() const;
	/**
	 * Toggles the depth test.
	 * @param enable enables the depth test if set to true, disables it otherwise.
	 */
	void enableDepthTest(const bool enable);
	/**
	 * Returns the list of available languages.
	 */
	static QStringList getAvailableLanguages();
	/**
	 * Returns the list of available framebuffer resolutions.
	 */
	static QStringList getAvailableFramebufferResolutions();
private:
	/**
	 * An enumeration of available configuration keys.
	 */
	enum class Key {
		ShowBorderlessWindow,
		ShowFramesPerSecond,
		ShaderProgram,
		PrimitiveTopology,
		EnableClipping,
		EnableBackfaceCulling,
		PolygonMode,
		ShadeModel,
		EnableScissorTest,
		EnableStencilTest,
		EnableDepthTest,
	};
	/**
	 * Instantiates an ApplicationSettings object.
	 */
	ApplicationSettings();
	/**
	 * Returns true if a value with the specified key exists in the configuration, false otherwise.
	 * @param key the key to query.
	 */
	bool contains(const Key key) const;
	/**
	 * Returns the stored value for the specified key.
	 * @param key the key to query.
	 * @param defaultValue if no value is found, then this value will be returned.
	 */
	QVariant value(const Key key, const QVariant& defaultValue = QVariant()) const;
	/**
	 * Stores the value with the specified key.
	 */
	void setValue(const Key key, const QVariant& value);
	/**
	 * Converts the specified configuration key into a string.
	 * @param key the configuration key to convert.
	 */
	static QString keyToString(const Key key);
signals:
	/**
	 * A signal that is raised when the FPS counter's visibility is changed.
	 */
	void fpsCounterVisibilityChanged(const bool visible);
	/**
	 * A signal that is raised when the visibility of the window's borders changes.
	 */
	void windowBorderVisibilityChanged(const bool visible);
	/**
	 * Signals that are raised when the shader program is changed.
	 */
	void shaderProgramChanged_(const int identifier);
	void shaderProgramChanged(const BaseShaderProgram::Identifier identifier);
	/**
	 * Signals that are raised when the primitive topology is changed.
	 */
	void primitiveTopologyChanged_(const int topology);
	void primitiveTopologyChanged(const PrimitiveTopology topology);
	/**
	 * A signal that is raised when clipping is toggled.
	 */
	void clippingToggled(const bool enabled);
	/**
	 * A signal that is raised when backface culling is toggled.
	 */
	void backfaceCullingToggled(const bool enabled);
	/**
	 * Signals that are raised when the polygon mode is changed.
	 */
	void polygonModeChanged_(const int mode);
	void polygonModeChanged(const PolygonMode mode);
	/**
	 * Signals that are raised when the shade model is changed.
	 */
	void shadeModelChanged_(const int model);
	void shadeModelChanged(const ShadeModel model);
	/**
	 * A signal that is raised when the scissor test is toggled.
	 */
	void scissorTestChanged(const bool enabled);
	/**
	 * A signal that is raised when the stencil test is toggled.
	 */
	void stencilTestChanged(const bool enabled);
	/**
	 * A signal that is raised when the depth test is toggled.
	 */
	void depthTestChanged(const bool enabled);
};
} // namespace clockwork

#endif // CLOCKWORK_APPLICATION_SETTINGS_HH
