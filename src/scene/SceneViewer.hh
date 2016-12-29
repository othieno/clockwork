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
#ifndef CLOCKWORK_SCENE_VIEWER_HH
#define CLOCKWORK_SCENE_VIEWER_HH

#include "SceneObject.hh"
#include "Projection.hh"
#include "Frustum.hh"
#include "Viewport.hh"
#include "RenderingAlgorithm.hh"
#include "Primitive.hh"
#include "Renderer.hh"
#include "ImageFilter.hh"
#include "TextureFilter.hh"
#include <QRectF>


namespace clockwork {
/**
 *
 */
class SceneViewer : public SceneObject {
	Q_OBJECT
	Q_PROPERTY(QVector3D center READ getCenter WRITE setCenter NOTIFY centerChanged)
	Q_PROPERTY(QRectF scissor READ getScissor WRITE setScissor NOTIFY scissorChanged)
public:
	/**
	 * An enumeration of available scene viewers.
	 */
	enum class Type {
		Camera,
	};
	/**
	 *
	 */
	SceneViewer(const SceneViewer&) = delete;
	/**
	 *
	 */
	SceneViewer(SceneViewer&&) = delete;
	/**
	 *
	 */
	SceneViewer& operator=(const SceneViewer&) = delete;
	/**
	 *
	 */
	SceneViewer& operator=(SceneViewer&&) = delete;
	/**
	 * Returns the viewer's type.
	 */
	Type getType() const;
	/**
	 * Returns the viewer's projection.
	 */
	Projection getProjection() const;
	/**
	 * Sets the viewer's projection.
	 * @param projection the projection to set.
	 */
	void setProjection(const Projection projection);
	/**
	 * Returns the viewer's projection transform matrix.
	 */
	const QMatrix4x4& getProjectionTransform() const;
	/**
	 * Returns the viewer's view transform matrix.
	 */
	const QMatrix4x4& getViewTransform() const;
	/**
	 * Returns the viewer's view-projection transform matrix.
	 */
	const QMatrix4x4& getViewProjectionTransform() const;
	/**
	 * Returns the viewer's viewport.
	 */
	const Viewport& getViewport() const;
	/**
	 * Sets the viewer's viewport.
	 * @param viewport the viewport to set.
	 */
	void setViewport(const Viewport& viewport);
	/**
	 * Returns the viewer's reference point.
	 */
	const QVector3D& getCenter() const;
	/**
	 * Sets the viewer's reference point.
	 * @param center the reference point to set.
	 */
	void setCenter(const QVector3D& center);
	/**
	 * Returns the viewer's scissor.
	 */
	const QRectF& getScissor() const;
	/**
	 * Sets the viewer's scissor.
	 * @param scissor the scissor to set.
	 */
	void setScissor(const QRectF& scissor);
	/**
	 * Returns the viewer's view frustum.
	 */
	const Frustum& getViewFrustum() const;
	/**
	 * Sets the viewer's view frustum.
	 * @param viewFrustum the view frustum to set.
	 */
	void setViewFrustum(const Frustum& viewFrustum);
	/**
	 * Returns the viewer's rendering algorithm.
	 */
	RenderingAlgorithm getRenderingAlgorithm() const;
	/**
	 * Sets the viewer's rendering algorithm.
	 * @param algorithm the rendering algorithm to set.
	 */
	void setRenderingAlgorithm(const RenderingAlgorithm algorithm);
	/**
	 * Returns the viewer's primitive mode.
	 */
	Primitive getPrimitiveMode() const;
	/**
	 * Sets the viewer's primitive mode.
	 * @param primitive the primitive mode to set.
	 */
	void setPrimitiveMode(const Primitive primitive);
	/**
	 * Returns the viewer's texture filter.
	 */
	TextureFilter::Identifier getTextureFilter() const;
	/**
	 * Sets the viewer's texture filter.
	 * @param identifier the unique identifier of the texture filter to set.
	 */
	void setTextureFilter(const TextureFilter::Identifier identifier);
	/**
	 * Returns the viewer's post-processing image filters.
	 */
	const QList<ImageFilter::Identifier>& getImageFilters() const;
	/**
	 * Adds the specified image filter.
	 * Note that this function will not ignore duplicates.
	 * @param identifier a unique identifier of the image filter to add.
	 */
	void addImageFilter(const ImageFilter::Identifier identifier);
	/**
	 * Removes all instances of the specified image filter.
	 * @param identifier a unique identifier of the image filter to remove.
	 */
	void removeImageFilter(const ImageFilter::Identifier identifier);
	/**
	 * Removes all image filters.
	 */
	void removeAllImageFilters();
	/**
	 * Returns true if an object is (partially) visible from this SceneViewer's
	 * point of view, false otherwise.
	 * @param object the object to query.
	 */
	bool isObjectVisible(const SceneObject& object) const;
protected:
	/**
	 * Instantiates a named SceneViewer object of a given type.
	 * @param type the viewer's type.
	 * @param name the viewer's name.
	 */
	SceneViewer(const Type type, const QString& name);
private:
	/**
	 * Updates the viewer's view transformation matrix.
	 */
	void updateViewTransform();
	/**
	 * Updates the viewer's projection transformation matrix.
	 */
	void updateProjectionTransform();
	/**
	 * Updates the viewer's view-projection transformation matrix.
	 */
	void updateViewProjectionTransform();
	/**
	 * The type of viewer.
	 */
	const Type type_;
	/**
	 * The viewer's projection.
	 */
	Projection projection_;
	/**
	 * The viewer's projection transformation matrix.
	 */
	QMatrix4x4 projectionTransform_;
	/**
	 * The viewer's view transformation matrix.
	 */
	QMatrix4x4 viewTransform_;
	/**
	 * The viewer's view-projection transformation matrix.
	 */
	QMatrix4x4 viewProjectionTransform_;
	/**
	 * The viewer's reference point, i.e. the position that is being looked at.
	 */
	QVector3D center_;
	/**
	 * The viewer's viewport.
	 */
	Viewport viewport_;
	/**
	 * The viewer's viewport scissor.
	 */
	QRectF scissor_;
	/**
	 * The viewer's view frustum.
	 */
	Frustum viewFrustum_;
	/**
	 * The viewer's rendering algorithm.
	 */
	RenderingAlgorithm renderingAlgorithm_;
	/**
	 * The viewer's primitive mode.
	 */
	Primitive primitiveMode_;
	/**
	 * The unique identifier of the viewer's texture filter.
	 */
	TextureFilter::Identifier textureFilterIdentifier_;
	/**
	 * A list of identifiers of the viewer's post-processing image filters.
	 */
	QList<ImageFilter::Identifier> imageFilterIdentifiers_;
signals:
	/**
	 * A signal that is emitted when the viewer's reference point is changed.
	 */
	void centerChanged(const QVector3D& center);
	/**
	 * A signal that is emitted when the viewer's scissor is changed.
	 */
	void scissorChanged(const QRectF& scissor);
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_VIEWER_HH
