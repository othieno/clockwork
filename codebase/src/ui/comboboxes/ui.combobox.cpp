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
#include "ui.combobox.hh"
#include "scene.hh"
#include <QLabel>
#include <QHBoxLayout>


clockwork::ui::GUIComboBox::GUIComboBox(clockwork::ui::UserInterface& ui, const std::string& label) :
GUIComponent(ui),
_qComboBox(new QComboBox(&ui))
{
	// Make the label bold.
	QString boldLabel(label.c_str());
	boldLabel.prepend("<b>");
	boldLabel.append("</b>");

	// Configure the label.
	auto* const qLabel = new QLabel(boldLabel, this);
	qLabel->setStyleSheet("QLabel { color:rgb(255, 255, 255); }");
	qLabel->setTextFormat(Qt::RichText);
	qLabel->setBuddy(_qComboBox);

	// Set the wrapper's layout.
	auto* const layout = new QHBoxLayout(this);
	setLayout(layout);

	// Add the label and combo box to the wrapper.
	layout->addWidget(qLabel);
	layout->addWidget(_qComboBox);

	// Setup the signals.
	connect(_qComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(const int&)));
}


void
clockwork::ui::GUIComboBox::build()
{
	// Block all signals while the combo box is being created. This prevents
	// the componentChanged signal from being raised while elements are being
	// inserted into the combo box.
	_qComboBox->blockSignals(true);

	// Add entries to the combo box.
	loadItemList();

	// Re-activate all signals.
	_qComboBox->blockSignals(false);
}


clockwork::ui::GUIComboBox::GUIComboBox
(
	clockwork::ui::UserInterface& ui,
	const std::string& label,
	std::list<std::string> items
) :
GUIComboBox(ui, label)
{
	// Add items to the combo box.
	for (const auto& item : items)
	{
		const auto& entry = QObject::tr(item.c_str());
		_qComboBox->addItem(entry, entry);
	}
}


void
clockwork::ui::GUIComboBox::onCurrentIndexChanged(const int& index)
{
	onItemSelected(index);
	emit componentChanged(this);
}


void
clockwork::ui::GUIComboBox::setSelectedItem(const int& index)
{
	// Make sure the index is valid.
	const auto& maximumIndex = _qComboBox->count() - 1;
	const auto& minimumIndex = maximumIndex >= 0 ? 0 : -1;

	_qComboBox->setCurrentIndex(std::min(maximumIndex, std::max(minimumIndex, index)));
}


int
clockwork::ui::GUIComboBox::addItem(const QString& text, const QVariant& userData)
{
	const auto itemIndex = _qComboBox->count();
	_qComboBox->addItem(text, userData);

	return itemIndex;
}


void
clockwork::ui::GUIComboBox::onInterfaceUpdate(const clockwork::ui::GUIComponent* const source)
{
	if (source != this)
		setEnabled(clockwork::scene::Scene::getUniqueInstance().hasViewer());
}
