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
#pragma once

#include "ui.component.hh"


namespace clockwork {
namespace ui {

/**
 * @see ui.view.scene.hh.
 */
class GUISceneView;

/**
 * @see ui.view.scene.entity.hh.
 */
class GUISceneEntityView;


class GUIControlPanel : public clockwork::ui::GUIComponent
{
public:
	/**
	 * Instantiate a GUIControlPanel attached to the user interface.
	 * @param ui the user interface that this component is attached to.
	 */
	GUIControlPanel(clockwork::ui::UserInterface& ui);
private:
	/**
	 * The scene view.
	 */
	clockwork::ui::GUISceneView* _sceneView;
	/**
	 * The scene entity view.
	 */
	clockwork::ui::GUISceneEntityView* _sceneEntityView;
};

} // namespace ui
} // namespace clockwork
