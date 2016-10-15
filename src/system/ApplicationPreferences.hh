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
#ifndef CLOCKWORK_APPLICATION_PREFERENCES_HH
#define CLOCKWORK_APPLICATION_PREFERENCES_HH

#include <QSettings>


namespace clockwork {
/**
 *
 */
class Application;
/**
 *
 */
class ApplicationPreferences : public QSettings {
	Q_OBJECT
	Q_PROPERTY(bool showFramesPerSecond READ isFpsCounterVisible WRITE showFpsCounter NOTIFY fpsCounterVisibilityChanged)
	Q_PROPERTY(bool enableDepthTesting READ isDepthTestingEnabled WRITE enableDepthTesting NOTIFY depthTestingChanged)
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
     * Returns true if depth testing is enabled, false otherwise.
	 */
	bool isDepthTestingEnabled() const;
	/**
     * Toggles depth testing.
     * @param enable enables depth testing if set to true, disables it otherwise.
	 */
	void enableDepthTesting(const bool enabled);
	/**
	 * Returns the list of available languages.
	 */
	static QStringList getAvailableLanguages();
	/**
	 * Returns the list of available framebuffer resolutions.
	 */
	static QStringList getAvailableFramebufferResolutions();
signals:
	/**
	 * A signal that is raised when the FPS counter's visibility is changed.
	 */
	void fpsCounterVisibilityChanged(const bool visible);
	/**
	 * A signal that is raised when depth testing is toggled.
	 */
	void depthTestingChanged(const bool enabled);
private:
	/**
	 * An enumeration of available configuration keys.
	 */
	enum class Key {
		ShowFramesPerSecond,
		EnableDepthTesting,
	};
	/**
	 * Instantiates an ApplicationPreferences object.
	 */
	ApplicationPreferences(Application&);
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
};
} // namespace clockwork

#endif // CLOCKWORK_APPLICATION_PREFERENCES_HH
