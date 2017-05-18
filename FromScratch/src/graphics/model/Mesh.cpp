#include "Mesh.h"

namespace fs {
	namespace graphics {
		Mesh::Mesh(const unsigned int & vao, const unsigned int & vbo, const unsigned int & ibo, const unsigned int & count)
		{
			m_VAO = vao;
			m_VBO = vbo;
			m_IBO = ibo;
			m_VertexCount = count;
		}
		bool Mesh::operator==(const Mesh & that)
		{
			return m_VAO == that.m_VAO && m_VBO == that.m_VBO && m_IBO == that.m_IBO && m_VertexCount == that.m_VertexCount;
		}
	}
}
