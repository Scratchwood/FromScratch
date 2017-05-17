#include "SimpleRenderer.h"
#include <GL\glew.h>
#include "MathsUtil.h"
#include "Matrix4.h"

namespace fs {
	namespace graphics {

		void SimpleRenderer::render(const unsigned int textureId, const float textureRows, 
			const maths::Vector2& textureOffsets, const maths::Matrix4& transform, const unsigned int vertexCount, 
			const unsigned int VAO, const unsigned int VBO, const unsigned int IBO, ShaderPtr shader) {

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureId);
			if (textureRows != -1) {
				shader->setUniform("textureRows", textureRows);
				shader->setUniform("textureOffset", textureOffsets);
			}
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			shader->setModel(transform);

			glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}
