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
#include "render.task.hh"
#include "renderer.factory.hh"
#include "vsd.hh"
#include "services.hh"


clockwork::graphics::Framebuffer& clockwork::concurrency::RenderTask::FRAMEBUFFER =
clockwork::system::Services::Graphics.getFramebuffer();


clockwork::concurrency::RenderTask::RenderTask
(
	const clockwork::physics::RigidBody& body,
	const clockwork::scene::Viewer& viewer
) :
Task(static_cast<int>(clockwork::concurrency::TaskPriority::GraphicsRenderTask)),
_viewpoint(viewer.getPosition()),
_VIEWPORTX((viewer.getViewport().width *  0.5) * FRAMEBUFFER.getWidth()),
_VIEWPORTY((viewer.getViewport().height * 0.5) * FRAMEBUFFER.getHeight()),
_MODEL(body.getModelMatrix()),
_VIEW(viewer.getViewMatrix()),
_PROJECTION(viewer.getProjectionMatrix()),
_model3D(body.getModel3D())
{}


void
clockwork::concurrency::RenderTask::onRun()
{
	if (_model3D != nullptr)
	{
		// Calculate transformation matrices.
		_MODELVIEW = _VIEW * _MODEL;
		_NORMAL = clockwork::Matrix4::transpose(clockwork::Matrix4::inverse(_MODELVIEW));
		_VIEWPROJECTION = _PROJECTION * _VIEW;
		_MODELVIEWPROJECTION = _VIEWPROJECTION * _MODEL;

		// Process the 3D model.
		for (const auto& face : _model3D->getFaces())
		{
			// The face's vertices.
			const auto& vertices = face.getVertices();
			const auto& texcoords = face.getTextureCoordinates();

			// A vector to store potentially visible fragments.
			std::vector<clockwork::graphics::Fragment> fragments;

			// Each face has a triplet of vertices and mapping coordinates.
			// Convert each vertex into a fragment.
			for (unsigned int i = 0; i < 3; ++i)
			{
				// Create a new fragment and set its mapping coordinates.
				const auto& texcoord = texcoords[i];
				clockwork::graphics::Fragment fragment(texcoord.u, texcoord.v);

				// Apply the vertex program and store its result to the newly
				// created fragment. Then list the fragment as potentially visible.
				const auto& vertex = *vertices[i];
				vertexProgram(vertex, fragment);
				fragments.push_back(fragment);
			}

			// Clip vertices that are not in the viewing window. Note that the
			// fragment vector may have more than 3 elements after the clipping
			// operation is performed. The fragments will need to be triangulated.
			clockwork::graphics::vsd::clip(fragments);

			// Perform perspective-divide on the visible fragments to convert the
			// fragments positions from clipping coordinate space to normalised
			// device coordinate space.
			for (auto& fragment : fragments)
			{
				fragment.x /= fragment.w;
				fragment.y /= fragment.w;
				fragment.z /= fragment.w;
				fragment.w  = 1;
			}

			// Rasterise triangular polygonal faces created from the fragment list.
			for (unsigned int i = 0; i < fragments.size() - 2; ++i)
				rasterise({&fragments[i], &fragments[i + 1], &fragments[i + 2]});
		}
	}
}


void
clockwork::concurrency::RenderTask::vertexProgram
(
	const clockwork::graphics::Vertex& vertex,
	clockwork::graphics::Fragment& fragment
)
{
	// Calculate the fragment's position.
	const clockwork::Point4& position = _MODELVIEWPROJECTION * vertex;
	fragment.x = position.x;
	fragment.y = position.y;
	fragment.z = position.z;
	fragment.w = position.w;

	// Calculate the fragment's normal vector components.
	const clockwork::Vector3& normal = clockwork::Vector3::normalise(_NORMAL * vertex.getNormal());
	fragment.i = normal.i;
	fragment.j = normal.j;
	fragment.k = normal.k;
}


void
clockwork::concurrency::RenderTask::rasterise(const std::array<clockwork::graphics::Fragment*, 3>& fragments)
{
	// Perform backface culling. If the polygon isn't discarded, convert its position
	// from normalised device coordinate space to viewport space then pass it on to
	// the primitive assembly step.
	if (!clockwork::graphics::vsd::isBackface(fragments))
	{
		for (auto& immutableFragment : fragments)
		{
			auto* fragment = const_cast<clockwork::graphics::Fragment*>(immutableFragment);

			fragment->x = (fragment->x + 1.0) * _VIEWPORTX;
			fragment->y = (fragment->y + 1.0) * _VIEWPORTY;
		}
		primitiveAssembly(fragments);
	}
}


uint32_t
clockwork::concurrency::RenderTask::fragmentProgram(const clockwork::graphics::Fragment&)
{
	return 0xffffffff;
}
