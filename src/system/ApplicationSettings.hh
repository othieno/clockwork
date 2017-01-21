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
#include "PrimitiveTopology.hh"


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
	Q_PROPERTY(int primitiveTopology READ getPrimitiveTopology WRITE setPrimitiveTopology NOTIFY primitiveTopologyChanged_)
	Q_PROPERTY(bool enableClipping READ isClippingEnabled WRITE enableClipping NOTIFY clippingToggled)
	Q_PROPERTY(bool enableBackfaceCulling READ isBackfaceCullingEnabled WRITE enableBackfaceCulling NOTIFY backfaceCullingToggled)
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
	 * Returns the primitive topology.
	 */
	int getPrimitiveTopology() const;
	/**
	 * Sets the primitive topology.
	 * @param topology the primitive topology to set.
	 */
	void setPrimitiveTopology(const int topology);
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
		PrimitiveTopology,
		EnableClipping,
		EnableBackfaceCulling,
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
