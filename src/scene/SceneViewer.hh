/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2014-2016 Jeremy Othieno.
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
#include "Renderer.hh"
#include "ImageFilter.hh"
#include "TextureFilter.hh"


namespace clockwork {
/**
 *
 */
class SceneViewer : public SceneObject {
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
	 * Returns the viewer's view transform matrix.
	 */
	const Matrix4& getViewTransform() const;
	/**
	 * Returns the viewer's projection transform matrix.
	 */
	const Matrix4& getProjectionTransform() const;
	/**
	 * Returns the viewer's view-projection transform matrix.
	 */
	const Matrix4& getViewProjectionTransform() const;
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
	 * Returns the viewer's line-drawing algorithm.
	 */
	Renderer::LineDrawingAlgorithm getLineDrawingAlgorithm() const;
	/**
	 * Sets the viewer's line-drawing algorithm.
	 * @param algorithm the line-drawing algorithm to set.
	 */
	void setLineDrawingAlgorithm(const Renderer::LineDrawingAlgorithm algorithm);
	/**
	 * Returns the viewer's primitive mode.
	 */
	Renderer::Primitive getPrimitiveMode() const;
	/**
	 * Sets the viewer's primitive mode.
	 * @param primitive the primitive mode to set.
	 */
	void setPrimitiveMode(const Renderer::Primitive primitive);
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
	 * Calculates and returns the viewer's view transform.
	 */
	Matrix4 calculateViewTransform() const;
	/**
	 * Calculates and returns the viewer's projection transform.
	 */
	Matrix4 calculateProjectionTransform() const;
	/**
	 * The type of viewer.
	 */
	const Type type_;
	/**
	 * The viewer's projection.
	 */
	Projection projection_;
	/**
	 * The view transformation matrix.
	 */
	mutable Matrix4 cachedViewTransform_;
	/**
	 * When true, this signals that the cached view transformation matrix needs
	 * to be updated before being accessed.
	 */
	mutable bool updateCachedViewTransform_;
	/**
	 * The projection transformation matrix.
	 */
	mutable Matrix4 cachedProjectionTransform_;
	/**
	 * When true, this signals that the cached projection transformation matrix
	 * needs to be updated before being accessed.
	 */
	mutable bool updateCachedProjectionTransform_;
	/**
	 * The view-projection transformation matrix.
	 */
	mutable Matrix4 cachedViewProjectionTransform_;
	/**
	 * The viewer's viewport.
	 */
	Viewport viewport_;
	/**
	 * The viewer's view frustum.
	 */
	Frustum viewFrustum_;
	/**
	 * The viewer's rendering algorithm.
	 */
	RenderingAlgorithm renderingAlgorithm_;
	/**
	 * The viewer's line-drawing algorithm.
	 */
	Renderer::LineDrawingAlgorithm lineDrawingAlgorithm_;
	/**
	 * The viewer's primitive mode.
	 */
	Renderer::Primitive primitiveMode_;
	/**
	 * The unique identifier of the viewer's texture filter.
	 */
	TextureFilter::Identifier textureFilterIdentifier_;
	/**
	 * A list of identifiers of the viewer's post-processing image filters.
	 */
	QList<ImageFilter::Identifier> imageFilterIdentifiers_;
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_VIEWER_HH
