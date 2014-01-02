/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Jeremy Othieno.
 *
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
#include "ui.hh"
#include "ui.combobox.line.algorithm.hh"
#include "scene.hh"
#include "scene.viewer.hh"
#include "renderer.factory.hh"
#include "renderer.implementation.wireframe.hh"


clockwork::ui::GUILineAlgorithmComboBox::GUILineAlgorithmComboBox(UserInterface& ui) :
GUIComboBox(ui, "Line Algorithm")
{
	// Build the combo box.
	build();
}


void
clockwork::ui::GUILineAlgorithmComboBox::loadItemList()
{
	auto* const renderer =	static_cast<clockwork::graphics::WireframeRenderer*>
	(clockwork::graphics::RendererFactory::getUniqueInstance().get(clockwork::graphics::Renderer::Type::Wireframe));

	const auto& algorithms = renderer->getLineAlgorithmList();
	const auto& defaultAlgorithm = renderer->getLineAlgorithm();
	int defaultIndex = 0;

	// Add the keys as items to the combo box.
	for (const auto& algorithm : algorithms)
	{
		using UserDataType = std::underlying_type<clockwork::graphics::WireframeRenderer::LineAlgorithm>::type;

		const auto& text = QString(clockwork::toString(algorithm).c_str());
		const auto& userData = static_cast<UserDataType>(algorithm);

		// Add the item to the combo box.
		const auto& itemIndex = addItem(text, userData);

		// Get the index of the current item.
		if (algorithm == defaultAlgorithm)
			defaultIndex = itemIndex;
	}
	setSelectedItem(defaultIndex);
}


void
clockwork::ui::GUILineAlgorithmComboBox::onInterfaceUpdate(const clockwork::ui::GUIComponent* const source)
{
	if (source != this)
	{
		// The line algorithm combo box is only visible if the current renderer is
		// set to Renderer::Type::Wireframe, and enabled if a scene viewer is set.
		bool isEnabled = false;
		bool isVisible = false;
		auto* const viewer = clockwork::scene::Scene::getUniqueInstance().getViewer();
		if (viewer != nullptr)
		{
			isEnabled = true;
			isVisible = clockwork::graphics::Renderer::Type::Wireframe == viewer->getRendererType();
		}
		setEnabled(isEnabled);
		setVisible(isVisible);
	}
}


void
clockwork::ui::GUILineAlgorithmComboBox::onItemSelected(const int& index)
{
	static auto* const renderer =	static_cast<clockwork::graphics::WireframeRenderer*>
	(clockwork::graphics::RendererFactory::getUniqueInstance().get(clockwork::graphics::Renderer::Type::Wireframe));

	renderer->setLineAlgorithm(getItem<clockwork::graphics::WireframeRenderer::LineAlgorithm>(index));
}
