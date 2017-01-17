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
#ifndef CLOCKWORK_USER_INTERFACE_HH
#define CLOCKWORK_USER_INTERFACE_HH

#include <QQmlApplicationEngine>
#include "Error.hh"
#include "SelectModel.hh"


namespace clockwork {
/**
 *
 */
class Application;
/**
 *
 */
class UserInterface : private QObject {
	friend class Application;
public:
	/**
	 *
	 */
	UserInterface(const UserInterface&) = delete;
	/**
	 *
	 */
	UserInterface(UserInterface&&) = delete;
	/**
	 *
	 */
	UserInterface& operator=(const UserInterface&) = delete;
	/**
	 *
	 */
	UserInterface& operator=(UserInterface&&) = delete;
private:
	/**
	 * Instantiates a UserInterface object that is bound to a specified application.
	 * @param application the application that this user interface will be bound to.
	 */
	explicit UserInterface(Application& application);
	/**
	 * Initializes the user interface.
	 */
	Error initialize();
	/**
	 * Registers custom data types for use in the QML context.
	 */
	void registerTypes();
	/**
	 * Registers enumerations for use in the specified QML context.
	 * @param context the QML context that the enumerations will be exposed to.
	 */
	void registerEnumerations(QQmlContext& context);
	/**
	 * Creates a SelectModel object for the enumeration E.
	 * @param parent the model's parent.
	 */
	template<class E> static SelectModel* createEnumerationModel(QObject* parent) {
		static_assert(std::is_enum<E>::value);
		using enumeration = enumeration<E>;

		QList<SelectModel::Option> options;
		for (const auto enumerator : enumeration::enumerators()) {
			options << SelectModel::Option(
				enumeration::template name<QString>(enumerator),
				enumeration::ordinal(enumerator)
			);
		}
		return new SelectModel(options, parent);
	}
	/**
	 * The application that this user interface is bound to.
	 */
	Application& application_;
	/**
	 *
	 */
	QQmlApplicationEngine engine_;
};
} // namespace clockwork

#endif // CLOCKWORK_USER_INTERFACE_HH
