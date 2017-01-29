/*
 * This file is part of Clockwork.
 * https://github.com/othieno/clockwork.
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
#include "FramebufferView.hh"
#include "Framebuffer.hh"
#include "Service.hh"
#include <QSGGeometryNode>
#include <QOpenGLFunctions>

using clockwork::FramebufferView;


FramebufferView::FramebufferView(QQuickItem* const parent) :
QQuickItem(parent) {
	// Indicate that this object should be rendered by the scene graph.
	setFlag(QQuickItem::ItemHasContents);
}


QSGNode*
FramebufferView::updatePaintNode(QSGNode* const oldNode, UpdatePaintNodeData*) {
	QSGGeometryNode* node = static_cast<QSGGeometryNode*>(oldNode);
	if (node == nullptr) {
		node = new QSGGeometryNode;
		node->setGeometry(&geometry_);
		node->setMaterial(MaterialShader::createMaterial(texture_));
		node->setFlag(QSGNode::OwnsMaterial);
	}
	geometry_.update(boundingRect().toRect());
	texture_.updateTexture();

	node->markDirty(QSGNode::DirtyGeometry);

	return node;
}


FramebufferView::Texture::Texture() :
cpuRenderTarget_(nullptr),
gpuRenderTarget_(QOpenGLTexture::Target2D) {}


void
FramebufferView::Texture::bind() {
	gpuRenderTarget_.bind();
}


bool
FramebufferView::Texture::hasAlphaChannel() const {
	return true;
}


bool
FramebufferView::Texture::hasMipmaps() const {
	return false;
}


int
FramebufferView::Texture::textureId() const {
	return gpuRenderTarget_.textureId();
}


QSize
FramebufferView::Texture::textureSize() const {
	return QSize(gpuRenderTarget_.width(), gpuRenderTarget_.height());
}


bool
FramebufferView::Texture::updateTexture() {
	if (gpuRenderTarget_.isCreated()) {
		gpuRenderTarget_.setData(QOpenGLTexture::RGBA, QOpenGLTexture::UInt32_RGBA8, cpuRenderTarget_);
		return true;
	}
	return false;
}


void
FramebufferView::Texture::setClientSideRenderTarget(const void* target) {
	cpuRenderTarget_ = target;
}


void
FramebufferView::Texture::resize(const QSize& size) {
	if (gpuRenderTarget_.isCreated()) {
		gpuRenderTarget_.destroy();
	}
	gpuRenderTarget_.setSize(size.width(), size.height());
	gpuRenderTarget_.setAutoMipMapGenerationEnabled(false);
	gpuRenderTarget_.setFormat(QOpenGLTexture::RGBA8_UNorm);
	gpuRenderTarget_.setMipLevels(0);
	gpuRenderTarget_.setWrapMode(QOpenGLTexture::ClampToEdge);
	gpuRenderTarget_.setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
	gpuRenderTarget_.allocateStorage();
}


bool
FramebufferView::Texture::isCreated() const {
	return gpuRenderTarget_.isCreated();
}


void
FramebufferView::Texture::destroy() {
	if (gpuRenderTarget_.isCreated()) {
		gpuRenderTarget_.destroy();
	}
}


FramebufferView::Geometry::Geometry() :
QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 4) {}


void
FramebufferView::Geometry::update(const QRectF& rect) {
	QSGGeometry::updateTexturedRectGeometry(this, rect, QRectF(0.0, 0.0, 1.0, 1.0));
}


FramebufferView::MaterialState::MaterialState() :
texture(nullptr) {}


FramebufferView::MaterialState::~MaterialState() {
	if (texture != nullptr && texture->isCreated()) {
		texture->destroy();
		texture = nullptr;
	}
}


FramebufferView::Material*
FramebufferView::MaterialShader::createMaterial(FramebufferView::Texture& texture) {
	Material* const material = createMaterial();
	material->state()->texture = &texture;

	if (!texture.isCreated()) {
		const auto& framebuffer = Service::Graphics.getFramebuffer();
		const auto& onFramebufferResized = [&texture, &framebuffer](const QSize& size) {
			texture.resize(size);
			texture.setClientSideRenderTarget(framebuffer.getPixelBuffer());
		};
		connect(&framebuffer, &Framebuffer::resized, onFramebufferResized);
		onFramebufferResized(framebuffer.getResolutionSize());
	}

	return material;
}


QList<QByteArray>
FramebufferView::MaterialShader::attributes() const {
	return {"position", "uv"};
}


const char*
FramebufferView::MaterialShader::vertexShader() const {
	return
	"uniform highp mat4 qt_Matrix;\n"
	"attribute highp vec4 position;\n"
	"attribute highp vec2 uv;\n"
	"varying highp vec2 texCoord;\n"
	"void main() {\n"
		"gl_Position = qt_Matrix * position;\n"
		"texCoord = uv;\n"
	"}";
}


const char*
FramebufferView::MaterialShader::fragmentShader() const {
	// This is a very basic fragment shader except for one simple quirk:
	// The color buffer's pixels are in a 32-bit ARGB format however when
	// they are uploaded to the GPU render target, they are assumed to be
	// in RGBA format which is not the case. This means that the texel's
	// color channels are mismatched like so:
	// Expected format | Actual format
	//               R | A
	//               G | R
	//               B | G
	//               A | B
	// So Red actually contains the Alpha channel, Green contains Red, etc.
	// The solution is to simply swizzle the texel to GBAR.
	return
	"uniform lowp sampler2D texture;\n"
	"uniform lowp float qt_Opacity;\n"
	"varying highp vec2 texCoord;\n"
	"void main() {\n"
		"gl_FragColor = texture2D(texture, texCoord).gbar * qt_Opacity;\n"
	"}";
}


void
FramebufferView::MaterialShader::updateState(const MaterialState* state, const MaterialState*)
{
	if (program()->bind()) {
		QOpenGLFunctions* const f = QOpenGLContext::currentContext()->functions();
		f->glActiveTexture(GL_TEXTURE0);

		state->texture->bind();
	}
}


void
FramebufferView::MaterialShader::resolveUniforms()
{
	auto* const p = program();
	if (p->bind()) {
		p->setUniformValue("texture", 0);
	}
}
