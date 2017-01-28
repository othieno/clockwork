/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2017 Jeremy Othieno.
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
import QtQuick 2.4
import Material 0.2 as Material
import Material.ListItems 0.1 as ListItem
import Atomic 0.1 as Atomic


Flickable {
	anchors.fill: parent
	contentWidth: parent.width
	contentHeight: Math.max(content.implicitHeight, height)
	boundsBehavior: Flickable.StopAtBounds
	Column {
		id: content
		anchors.fill: parent
		ListItem.Subheader {
			text: qsTr("Shaders")
		}
		Atomic.Select {
			id: selectShaderProgram
			title: qsTr("Shader program")
			model: shaderPrograms
			initialValue: graphics.shaderProgram
			onChanged: graphics.shaderProgram = value
		}


		ListItem.Subheader {
			text: qsTr("Vertex specification")
		}
		Atomic.Select {
			id: selectPrimitiveTopology
			title: qsTr("Primitive topology")
			model: primitiveTopologies
			initialValue: graphics.primitiveTopology
			onChanged: graphics.primitiveTopology = value
		}


		ListItem.Subheader {
			text: qsTr("Vertex processing")
		}


		ListItem.Subheader {
			text: qsTr("Vertex post-processing")
		}
		ListItem.Subtitled {
			text: qsTr("Enable clipping")
			subText: qsTr("Clips primitives to the view volume.")
			secondaryItem: Material.Switch {
				id: toggleClipping
				checked: graphics.enableClipping
				anchors.verticalCenter: parent.verticalCenter
			}
			onClicked: {
				toggleClipping.checked = !toggleClipping.checked
				graphics.enableClipping = toggleClipping.checked
			}
		}


		ListItem.Subheader {
			text: qsTr("Primitive assembly")
		}
		ListItem.Subtitled {
			text: qsTr("Enable backface culling")
			subText: qsTr("Discards surfaces that are not facing the camera.")
			secondaryItem: Material.Switch {
				id: toggleBackfaceCulling
				checked: graphics.enableBackfaceCulling
				anchors.verticalCenter: parent.verticalCenter
			}
			onClicked: {
				toggleBackfaceCulling.checked = !toggleBackfaceCulling.checked
				graphics.enableBackfaceCulling = toggleBackfaceCulling.checked
			}
		}
/*
		ListItem.Divider {}
		ListItem.Subtitled {
			text: qsTr("Enable view frustum culling")
			subText: qsTr("Discards primitives that are outside the camera's view volume.")
			secondaryItem: Material.Switch {
				id: toggleViewFrustumCulling
				checked: graphics.enableViewFrustumCulling
				anchors.verticalCenter: parent.verticalCenter
			}
			onClicked: {
				toggleViewFrustumCulling.checked = !toggleViewFrustumCulling.checked
				graphics.enableViewFrustumCulling = toggleViewFrustumCulling.checked
			}
		}
		ListItem.Divider {}
		ListItem.Subtitled {
			text: qsTr("Enable contribution culling")
			subText: qsTr("Discards objects that are too far away or too small to contribute significantly to the final render.")
			secondaryItem: Material.Switch {
				id: toggleContributionCulling
				checked: graphics.enableContributionCulling
				anchors.verticalCenter: parent.verticalCenter
			}
			onClicked: {
				toggleContributionCulling.checked = !toggleContributionCulling.checked
				graphics.enableContributionCulling = toggleContributionCulling.checked
			}
		}
*/


		ListItem.Subheader {
			text: qsTr("Rasterization")
		}
		Atomic.Select {
			id: selectPolygonMode
			title: qsTr("Polygon mode")
			model: polygonModes
			initialValue: graphics.polygonMode
			onChanged: graphics.polygonMode = value
		}
		ListItem.Divider {}
		Atomic.Select {
			id: selectShadeModel
			title: qsTr("Shade model")
			model: shadeModels
			initialValue: graphics.shadeModel
			onChanged: graphics.shadeModel = value
		}
		ListItem.Divider {}
		ListItem.Subtitled {
			text: qsTr("Enable line anti-aliasing")
			subText: qsTr("Draws smoother lines.")
			secondaryItem: Material.Switch {
				id: toggleLineAntiAliasing
				checked: graphics.enableLineAntiAliasing
				anchors.verticalCenter: parent.verticalCenter
			}
			onClicked: {
				toggleLineAntiAliasing.checked = !toggleLineAntiAliasing.checked
				graphics.enableLineAntiAliasing = toggleLineAntiAliasing.checked
			}
		}


		ListItem.Subheader {
			text: qsTr("Fragment processing")
		}
		ListItem.Subtitled {
			text: qsTr("Enable scissor test")
			subText: qsTr("Discards fragments that fall outside of the scissor's bounding box.")
			secondaryItem: Material.Switch {
				id: toggleScissorTest
				checked: graphics.enableScissorTest
				anchors.verticalCenter: parent.verticalCenter
			}
			onClicked: {
				toggleScissorTest.checked = !toggleScissorTest.checked
				graphics.enableScissorTest = toggleScissorTest.checked
			}
		}
		ListItem.Divider {}
		ListItem.Subtitled {
			text: qsTr("Enable stencil test")
			subText: qsTr("Discards fragments that fall outside of the stencil's cut-out.")
			secondaryItem: Material.Switch {
				id: toggleStencilTest
				checked: graphics.enableStencilTest
				anchors.verticalCenter: parent.verticalCenter
			}
			onClicked: {
				toggleStencilTest.checked = !toggleStencilTest.checked
				graphics.enableStencilTest = toggleStencilTest.checked
			}
		}
		ListItem.Divider {}
		ListItem.Subtitled {
			text: qsTr("Enable depth test")
			subText: qsTr("Discards fragments that are not visible based on how close they are to the viewer.")
			secondaryItem: Material.Switch {
				id: toggleDepthTest
				checked: graphics.enableDepthTest
				anchors.verticalCenter: parent.verticalCenter
			}
			onClicked: {
				toggleDepthTest.checked = !toggleDepthTest.checked
				graphics.enableDepthTest = toggleDepthTest.checked
			}
		}


		ListItem.Subheader {
			text: qsTr("Framebuffer post-processing")
		}
	}
}
