#ifndef FROMSCRATCH_INCLUDE_MODELLOADER
#define FROMSCRATCH_INCLUDE_MODELLOADER
#include "Mesh.h"
#include "Shader.h"
#include "VertexTextureNormal.h"
#include "Model.h"
#include "Texture.h"
#include <vector>
#include <string>
#include <memory>

namespace fs {
	namespace graphics {
		class ContentManager
		{
		private:
			std::vector<unsigned int> m_VAOS;
			std::vector<unsigned int> m_VBOS;
			std::vector<Mesh> m_Meshes;
			std::vector<Shader> m_Shaders;
			std::vector<Texture> m_Textures;
			std::vector<Model> m_Models;
		public:
			ContentManager();
			~ContentManager();
			ModelPtr loadModel(const char* modelPath, const char* texturePath, int numberOfRowsInTexture = 1);
			ModelPtr loadModel(MeshPtr mesh, TexturePtr texture);
			ModelPtr loadModel(std::vector<VertexTextureNormal>& vertices, std::vector<unsigned int>& indices, const char* texturePath, int numberOfRowsInTexture = 1);
			MeshPtr loadMesh(std::vector<VertexTextureNormal>& vertices, std::vector<unsigned int>& indices);
			MeshPtr loadMesh(const char* path);
			ShaderPtr loadShader(const char* fragPath, const char* vertPath);
			TexturePtr loadTexture(const char* path, int rows = 1);

		private:
			void makeVertex(const std::string& vertexIndex, const std::string& uvIndex, const std::string& normalIndex,
				const std::vector<maths::Vector3>& vertices, const std::vector<maths::Vector3>& normals, const std::vector<maths::Vector2>& textures, std::vector<VertexTextureNormal>& vtnVector);
			const unsigned int compileShader(unsigned int shader, const char* src, unsigned int programId);
			const std::string loadFileToString(const char* filePath);
			const std::vector<std::string> splitString(const std::string& s, const char& c);
		};
	}
}
#endif
