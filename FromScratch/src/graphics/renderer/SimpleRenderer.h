#ifndef FROMSCRATCH_INCLUDE_SIMPLERENDERER
#define FROMSCRATCH_INCLUDE_SIMPLERENDERER
#include "Entity.h"
#include "Shader.h"
#include "Terrain.h"
#include <memory>

namespace fs {
	namespace graphics {
		
		class SimpleRenderer
		{
		public:

			void render(const unsigned int textureId, const float textureRows,
				const maths::Vector2& textureOffsets, const maths::Matrix4& transform, const unsigned int vertexCount,
				const unsigned int VAO, const unsigned int VBO, const unsigned int IBO, ShaderPtr shader);
		};
	}
}
#endif

