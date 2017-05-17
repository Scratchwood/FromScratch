#include "Model.h"

namespace fs {
	namespace graphics {

		Model::Model() {
			m_Mesh = nullptr;
			m_Texture = nullptr;
			m_Id = 0;
		}

		Model::Model(TexturePtr tex, MeshPtr model, unsigned int id) {
			m_Texture = tex;
			m_Mesh = model;
			m_Id = id;
		}

		bool Model::operator==(const Model & that)
		{
			return m_Texture->getId() == that.m_Texture->getId() && m_Mesh == that.m_Mesh;
		}

	}
}