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
#include "services.hh"

using clockwork::concurrency::RenderTask;


RenderTask::RenderTask
(
	const clockwork::graphics::RenderParameters& parameters,
	const clockwork::scene::Viewer& viewer,
	const clockwork::physics::RigidBody& body
) :
_parameters(parameters),
_viewpoint(viewer.getPosition()),
_model3D(body.getModel3D()),
_viewport(viewer.getViewport()),
_MODEL(body.getModelMatrix()),
_VIEW(viewer.getViewMatrix()),
_PROJECTION(viewer.getProjectionMatrix()),
_VIEWPROJECTION(viewer.getViewProjectionMatrix()),
_VIEWPORTX(0),
_VIEWPORTY(0)
{}


void
RenderTask::onRun()
{
	if (_model3D != nullptr && !_model3D->empty())
	{
		auto& framebuffer = clockwork::system::Services::Graphics.getFramebuffer();

		// Calculate the VIEWPORT transformation.
		const_cast<double&>(_VIEWPORTX) = 0.5 * _viewport.width  * framebuffer.getWidth();
		const_cast<double&>(_VIEWPORTY) = 0.5 * _viewport.height * framebuffer.getHeight();

		// Calculate transformation matrices.
		const_cast<clockwork::Matrix4&>(_MODELVIEW) = _VIEW * _MODEL;
		const_cast<clockwork::Matrix4&>(_NORMAL) = clockwork::Matrix4::transpose(clockwork::Matrix4::inverse(_MODELVIEW));
		const_cast<clockwork::Matrix4&>(_VIEWPROJECTION) = _PROJECTION * _VIEW;
		const_cast<clockwork::Matrix4&>(_MODELVIEWPROJECTION) = _VIEWPROJECTION * _MODEL;

		// Process the 3D model.
		for (const auto& face : _model3D->getFaces())
		{
			// The face's vertices.
			const auto& vertices = face.getVertices();
			const auto& texcoords = face.getTextureCoordinates();

			// A vector to store the face's vertices that have been transformed into fragments.
			std::vector<clockwork::graphics::Fragment> fragments;

			// Each face has a triplet of vertices and mapping coordinates.
			// Convert each vertex into a fragment.
			for (unsigned int i = 0; i < 3; ++i)
			{
				// Create a new fragment and set its mapping coordinates.
				const auto& texcoord = texcoords[i];
				clockwork::graphics::Fragment fragment(texcoord.u, texcoord.v);

				// Apply the vertex program and store its result to the newly created fragment.
				const auto& vertex = *vertices[i];
				_parameters.preVertexProgram(face, vertex, fragment);
				vertexProgram(vertex, fragment);
				_parameters.postVertexProgram(face, vertex, fragment);

				// Keep track of the new fragment.
				fragments.push_back(fragment);
			}
			// Clip vertices that are not in the viewing window. Note that the
			// fragment vector may have more than 3 elements after the clipping
			// operation is performed. The fragments will need to be triangulated.
			clip(fragments);

			// Perform perspective-divide on the visible fragments to convert the
			// fragments positions from clipping coordinate space to normalised
			// device coordinate space.
			for (auto& fragment : fragments)
			{
				auto& p = fragment.position;

				p.x /= p.w;
				p.y /= p.w;
				p.z /= p.w;
				p.w  = 1;
			}
			// Rasterise triangular polygonal faces created from the fragment list.
			for (unsigned int i = 0; i < fragments.size() - 2; ++i)
			{
				std::array<const clockwork::graphics::Fragment*, 3> triangle =
				{
					&fragments[i],
					&fragments[i + 1],
					&fragments[i + 2]
				};

				// Perform backface and occlusion culling to determine if the polygon is visible.
				// If the polygon isn't discarded, convert its position from normalised device
				// coordinate space to viewport space then pass it on to the primitive assembly step.
				if (!isBackface(triangle) && !isOccluded(triangle))
				{
					for (auto* const fragment : triangle)
					{
						double& x = const_cast<double&>(fragment->position.x);
						double& y = const_cast<double&>(fragment->position.y);

						x = (x + 1.0) * _VIEWPORTX;
						y = (y + 1.0) * _VIEWPORTY;
					}
					_parameters.primitiveAssembly(triangle);
				}
			}
		}
	}
}


void
RenderTask::vertexProgram(const clockwork::graphics::Vertex& vertex, clockwork::graphics::Fragment& fragment)
{
	// Calculate the fragment's position.
	fragment.position = _MODELVIEWPROJECTION * vertex;

	// Calculate the fragment's normal vector.
	fragment.normal = clockwork::Vector3::normalise(_NORMAL * vertex.getNormal());
}


void
RenderTask::clip(std::vector<clockwork::graphics::Fragment>&) const
{}


bool
RenderTask::isBackface(const std::array<const clockwork::graphics::Fragment*, 3>& triangle) const
{
	const auto* const f0 = triangle[0];
	const auto* const f1 = triangle[1];
	const auto* const f2 = triangle[2];
	if (f0 != nullptr && f1 != nullptr && f2 != nullptr)
	{
		const clockwork::Point3& p0 = f0->position;
		const clockwork::Point3& p1 = f1->position;
		const clockwork::Point3& p2 = f2->position;

		return clockwork::Vector3::cross(p1 - p0, p2 - p1).k > 0;
	}
	else
		return true;
}


bool
RenderTask::isOccluded(const std::array<const clockwork::graphics::Fragment*, 3>& triangle) const
{
	//TODO Implement me.
	return false;
}
