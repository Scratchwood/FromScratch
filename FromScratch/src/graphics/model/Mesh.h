#ifndef FROMSCRATCH_INCLUDE_RAWMODEL
#define FROMSCRATCH_INCLUDE_RAWMODEL
#include "Vector3.h"
#define MeshPtr		std::shared_ptr<graphics::Mesh>
namespace fs {
	namespace graphics {
		class Mesh {
		private:
			unsigned int m_VAO, m_VBO, m_IBO, m_VertexCount;
		public:
			maths::Vector3 m_Max, m_Min;
		public:
			Mesh(const unsigned int& vao, const unsigned int& vbo, const unsigned int& ibo, const unsigned int& count);

			inline const unsigned int& getVAO() const { return m_VAO; };
			inline const unsigned int& getVBO() const { return m_VBO; };
			inline const unsigned int& getIBO() const { return m_IBO; };
			inline const unsigned int& getVertexCount() const { return m_VertexCount; };
			bool operator==(const Mesh& that);
		};
	}
}
#endif