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
#ifndef CLOCKWORK_FRAMEBUFFER_VIEW_HH
#define CLOCKWORK_FRAMEBUFFER_VIEW_HH

#include <QQuickItem>
#include <QSGDynamicTexture>
#include <QSGGeometry>
#include <QSGSimpleMaterialShader>
#include <QOpenGLTexture>


namespace clockwork {
/**
 *
 */
class FramebufferView : public QQuickItem {
	Q_OBJECT
public:
	/**
	 * Instantiates a FramebufferView object as a child of the specified parent.
	 * @param parent this FramebufferView instance's parent.
	 */
	explicit FramebufferView(QQuickItem* const parent = nullptr);
	/**
	 * @see QQuickItem::updatePaintNode.
	 */
	QSGNode* updatePaintNode(QSGNode* const, UpdatePaintNodeData* const) Q_DECL_OVERRIDE;
private:
	/**
	 *
	 */
	class Texture : public QSGDynamicTexture {
	public:
		/**
		 * Instantiates a Texture object.
		 */
		Texture();
		/**
		 * @see QSGTexture::bind.
		 */
		void bind() Q_DECL_OVERRIDE;
		/**
		 * @see QSGTexture::hasAlphaChannel.
		 */
		bool hasAlphaChannel() const Q_DECL_OVERRIDE;
		/**
		 * @see QSGTexture::hasMipmaps.
		 */
		bool hasMipmaps() const Q_DECL_OVERRIDE;
		/**
		 * @see QSGTexture::textureId.
		 */
		int textureId() const Q_DECL_OVERRIDE;
		/**
		 * @see QSGTexture::textureSize.
		 */
		QSize textureSize() const Q_DECL_OVERRIDE;
		/**
		 * Uploads the client-side buffer to the render texture's GPU memory.
		 */
		bool updateTexture() Q_DECL_OVERRIDE;
		/**
		 * Sets the client-side (CPU) render target.
		 * @param target the client-side render target to set.
		 */
		void setClientSideRenderTarget(const void* const target);
		/**
		 * Resizes the texture.
		 * @param size the texture's new size.
		 */
		void resize(const QSize& size);
		/**
		 * Returns true if the texture has been created, false otherwise.
		 */
		bool isCreated() const;
		/**
		 * Destroys the texture.
		 */
		void destroy();
	private:
		/**
		 * The buffer located in CPU (client-side) memory that contains pixels that are
		 * uploaded to GPU (server-side) memory. If it helps, you may think of client-side
		 * memory as a backbuffer and server-side memory as a frontbuffer.
		 */
		const void* cpuRenderTarget_;
		/**
		 * The buffer located in GPU (server-side) memory that contains pixels that are
		 * displayed on the screen.
		 */
		QOpenGLTexture gpuRenderTarget_;
	} texture_;
	/**
	 *
	 */
	class Geometry : public QSGGeometry {
	public:
		/**
		 * Instantiates a Geometry object.
		 */
		Geometry();
		/**
		 * Updates the geometry with the coordinates in the specified rectangle.
		 */
		void update(const QRectF& rect);
	} geometry_;
	/**
	 * The material shader's state.
	 */
	struct MaterialState {
		/**
		 * Instantiates a MaterialState object.
		 */
		MaterialState();
		/**
		 * Destroys the MaterialState object.
		 */
		~MaterialState();
		/**
		 *
		 */
		Texture* texture;
	};
	/**
	 * The material used by the FramebufferView's scene graph geometry node.
	 */
	using Material = QSGSimpleMaterial<MaterialState>;
	/**
	 *
	 */
	class MaterialShader : public QSGSimpleMaterialShader<MaterialState> {
		QSG_DECLARE_SIMPLE_SHADER(MaterialShader, MaterialState)
	public:
		/**
		 * @see QSGSimpleMaterialShader::attributes.
		 */
		QList<QByteArray> attributes() const Q_DECL_OVERRIDE;
		/**
		 * @see QSGSimpleMaterialShader::vertexShader.
		 */
		const char* vertexShader() const Q_DECL_OVERRIDE;
		/**
		 * @see QSGSimpleMaterialShader::fragmentShader.
		 */
		const char* fragmentShader() const Q_DECL_OVERRIDE;
		/**
		 * @see QSGSimpleMaterialShader::updateState.
		 */
		void updateState(const MaterialState* const newState, const MaterialState* const oldState) Q_DECL_OVERRIDE;
		/**
		 * @see QSGSimpleMaterialShader::resolveUniforms.
		 */
		void resolveUniforms() Q_DECL_OVERRIDE;
		/**
		 * Creates a material that binds the specified texture to its state.
		 * @param texture a texture that is bound to the Material's state.
		 */
		static Material* createMaterial(Texture& texture);
	};
};
} // namespace clockwork

#endif // CLOCKWORK_FRAMEBUFFER_VIEW_HH
