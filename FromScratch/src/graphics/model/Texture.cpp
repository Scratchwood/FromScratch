#include "Texture.h"
#include <GL\glew.h>

namespace fs {
	namespace graphics {
		Texture::Texture(unsigned int id, int width, int height, int rows, float reflectivity, float shineDamp) {
			m_TextureId = id;
			m_Width = width;
			m_Height = height;
			m_Rows = rows;
			m_Reflectivity = reflectivity;
			m_ShineDamper = shineDamp;
		}

		void Texture::enable() const {
			glBindTexture(GL_TEXTURE_2D, m_TextureId);
		}

		void Texture::disable() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}