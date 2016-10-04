#ifndef CLOCKWORK_RENDERERX_HH
#define CLOCKWORK_RENDERERX_HH


namespace clockwork {
/**
 *
 */
class Mesh;
/**
 *
 */
class PipelineContext;
/**
 *
 */
template<class Implementation, class VertexAttributes>
class RendererX {
public:
	/**
	 *
	 */
	using Uniforms = int;//QHash<QString, Renderer::Uniform>;
	/**
	 * Generates a vertex array from the specified mesh.
	 * @param mesh a mesh that will be used to generate the vertex array.
	 */
/*
	static VertexArray generateVertexArray(const Mesh& mesh) {
		return Implementation::generateVertexArray(mesh);
	}
*/
	/**
	 * Draws the specified mesh in the given pipeline context.
	 * @param context the pipeline context.
	 * @param mesh the polygon mesh to draw.
	 */
/*
	void draw(PipelineContext& context, const Mesh& mesh) {
		//Implementation::draw(mesh);
	}
*/
	/**
	 *
	 */
/*
	static VertexAttributes& vertexShader(const Uniforms& uniforms, VertexAttributes& attributes) {
		return Implementation::vertexShader(uniforms, attributes);
	}
*/
};
} // namespace clockwork

#endif // CLOCKWORK_RENDERERX_HH
