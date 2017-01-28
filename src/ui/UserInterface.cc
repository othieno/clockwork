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
#include "UserInterface.hh"
#include "Application.hh"
#include "FramebufferView.hh"
#include "FramebufferProvider.hh"
#include "Service.hh"
#include "ShaderProgramIdentifier.hh"
#include "IlluminationModel.hh"
#include "PrimitiveTopology.hh"
#include "ShadeModel.hh"
#include <QQmlContext>

using clockwork::UserInterface;


UserInterface::UserInterface(Application& application) :
application_(application) {}


clockwork::Error
UserInterface::initialize() {
	engine_.addImageProvider("framebuffer", new FramebufferProvider(Service::Graphics.getFramebuffer()));

	auto* const qmlContext = engine_.rootContext();
	if (qmlContext != nullptr) {
		qmlContext->setContextProperty("application", &application_);
		qmlContext->setContextProperty("settings", &application_.getSettings());
		qmlContext->setContextProperty("scene", &application_.getScene());

		registerEnumerations(*qmlContext);
	} else {
		return Error::InvalidQmlContext;
	}

	registerTypes();

	QPM_INIT(engine_);
	engine_.load(QUrl("qrc:/view/ApplicationWindow.qml"));
	return Error::None;
}


void
UserInterface::registerTypes() {
	qRegisterMetaType<SceneViewer*>("SceneViewer*");
	qmlRegisterType<FramebufferView>("Clockwork", 0, 1, "FramebufferView");
}


void
UserInterface::registerEnumerations(QQmlContext& context) {
	QHash<QString, SelectModel*> models({
		{"shaderPrograms", createEnumerationModel<ShaderProgramIdentifier>(this)},
		{"illuminationModels", createEnumerationModel<IlluminationModel>(this)},
		{"primitiveTopologies", createEnumerationModel<PrimitiveTopology>(this)},
		{"polygonModes", createEnumerationModel<PolygonMode>(this)},
		{"shadeModels", createEnumerationModel<ShadeModel>(this)},
	});
	for (const auto& key : models.keys()) {
		context.setContextProperty(key, models[key]);
	}
}
