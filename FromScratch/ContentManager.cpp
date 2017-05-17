#include "ContentManager.h"
#include <FreeImage.h>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <limits>

namespace fs {
	namespace graphics {

		ContentManager::ContentManager()
		{

		}

		ContentManager::~ContentManager() {
			for (size_t i = 0; i < m_VAOS.size(); i++) {
				glDeleteVertexArrays(1, &m_VAOS[i]);
			}
			for (size_t i = 0; i < m_VBOS.size(); i++) {
				glDeleteBuffers(1, &m_VBOS[i]);
			}

			for (size_t i = 0; i < m_Shaders.size(); i++) {
				glDeleteProgram(m_Shaders[i].getId());
			}
			for (size_t i = 0; i < m_Textures.size(); i++) {
				GLuint tex_id = m_Textures[i].getId();
				glDeleteTextures(1, &tex_id);
			}
		}

		ModelPtr ContentManager::loadModel(const char * modelPath, const char * texturePath, int numberOfRowsInTexture)
		{
			return loadModel(loadMesh(modelPath), loadTexture(texturePath, numberOfRowsInTexture));
		}

		ModelPtr ContentManager::loadModel(MeshPtr mesh, TexturePtr texture)
		{
			Model model(texture, mesh, m_Models.size());
			m_Models.push_back(model);
			return std::make_shared<Model>(m_Models.back());
		}

		ModelPtr ContentManager::loadModel(std::vector<VertexTextureNormal>& vertices, std::vector<unsigned int>& indices, const char * texturePath, int numberOfRowsInTexture )
		{
			return loadModel(loadMesh(vertices, indices), loadTexture(texturePath, numberOfRowsInTexture));
		}

		MeshPtr ContentManager::loadMesh(std::vector<VertexTextureNormal>& vertices, std::vector<unsigned int>& indices) {
			float maxFloat = std::numeric_limits<float>::max();
			float minFloat = std::numeric_limits<float>::min();
			maths::Vector3 max(minFloat, minFloat, minFloat);
			maths::Vector3 min(maxFloat, maxFloat, maxFloat);
			for (size_t i = 0; i < vertices.size(); i++) {
				if (vertices[i].position >= max) {
					max = vertices[i].position;
				}
				if (vertices[i].position <= min) {
					min = vertices[i].position;
				}
			}
			unsigned int f_VAO, f_VBO, f_IBO;
			glGenVertexArrays(1, &f_VAO);
			glBindVertexArray(f_VAO);

			glGenBuffers(1, &f_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, f_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glGenBuffers(1, &f_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, f_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexTextureNormal), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTextureNormal), (const GLvoid*)0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTextureNormal), (const GLvoid *)(offsetof(VertexTextureNormal, VertexTextureNormal::uv)));
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTextureNormal), (const GLvoid *)(offsetof(VertexTextureNormal, VertexTextureNormal::normal)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(0);
			Mesh m(f_VAO, f_VBO, f_IBO, indices.size());
			m_Meshes.push_back(m);
			m_VAOS.push_back(f_VAO);
			m_VBOS.push_back(f_VBO);
			m_VBOS.push_back(f_IBO);
			return std::make_shared<Mesh>(m_Meshes.back());
		}

		MeshPtr ContentManager::loadMesh(const char* path) {
			std::string obj = loadFileToString(path);
			std::istringstream f(obj);
			std::string line;

			std::vector<maths::Vector3> vertices;
			std::vector<maths::Vector3> normals;
			std::vector<maths::Vector2> textures;

			std::vector<unsigned int> vertexIndices;
			std::vector<unsigned int> normalIndices;
			std::vector<unsigned int> uvIndices;

			std::set<std::string> uniqueVtn;
			std::vector<VertexTextureNormal> vtnVector;

			while (std::getline(f, line)) {
				if (line.find("v ") == 0) {
					std::vector<std::string> values = splitString(line, ' ');
					vertices.push_back(maths::Vector3(maths::Vector3(std::stof(values[1]), std::stof(values[2]), std::stof(values[3]))));
				}
				else if (line.find("vt ") == 0) {
					std::vector<std::string> values = splitString(line, ' ');
					textures.push_back(maths::Vector2(std::stof(values[1]), std::stof(values[2])));
				}
				else if (line.find("vn ") == 0) {
					std::vector<std::string> values = splitString(line, ' ');
					normals.push_back(maths::Vector3(std::stof(values[1]), std::stof(values[2]), std::stof(values[3])));
				}
				else if (line.find("f ") == 0) {
					std::vector<std::string> values = splitString(line, ' ');
					std::vector<std::string> vertex1 = splitString(values[1], '/');
					std::vector<std::string> vertex2 = splitString(values[2], '/');
					std::vector<std::string> vertex3 = splitString(values[3], '/');

					vertexIndices.push_back(std::stoi(vertex1[1]) - 1);
					vertexIndices.push_back(std::stoi(vertex2[1]) - 1);
					vertexIndices.push_back(std::stoi(vertex3[1]) - 1);

					makeVertex(vertex1[0], vertex1[1], vertex1[2], vertices, normals, textures, vtnVector);
					makeVertex(vertex2[0], vertex2[1], vertex2[2], vertices, normals, textures, vtnVector);
					makeVertex(vertex3[0], vertex3[1], vertex3[2], vertices, normals, textures, vtnVector);
				}
			}
			return loadMesh(vtnVector, vertexIndices);
		}

		ShaderPtr ContentManager::loadShader(const char* fragPath, const char* vertPath) {
			GLuint id = glCreateProgram();
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertexSourceStr = loadFileToString(vertPath);
			std::string fragmentSourceStr = loadFileToString(fragPath);

			const char* vertexSource = vertexSourceStr.c_str();
			const char* fragmentSource = fragmentSourceStr.c_str();

			GLuint vertexCompiled = compileShader(vertexShader, vertexSource, id);
			GLuint fragmentCompiled = compileShader(fragmentShader, fragmentSource, id);
			if (vertexCompiled == 0 || fragmentCompiled == 0) {
				return 0;
			}

			glLinkProgram(id);
			glValidateProgram(id);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			Shader shader(id, vertexShader, fragmentShader);
			m_Shaders.push_back(shader);
			return std::make_shared<Shader>(m_Shaders.back());
		}

		TexturePtr ContentManager::loadTexture(const char* path, int rows) {
			int width, height;
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			FIBITMAP *dib(0);
			BYTE* pixels(0);

			fif = FreeImage_GetFileType(path, 0);

			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(path);
			if (fif == FIF_UNKNOWN)
				return nullptr;

			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, path);
			if (!dib)
				return nullptr;

			pixels = FreeImage_GetBits(dib);
			width = FreeImage_GetWidth(dib);
			height = FreeImage_GetHeight(dib);
			int bits = FreeImage_GetBPP(dib);
			int size = width * height * (bits / 8);
			BYTE* result = new BYTE[size];
			memcpy(result, pixels, size);
			FreeImage_Unload(dib);

			unsigned int textureId;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, result);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5f);
			glBindTexture(GL_TEXTURE_2D, 0);

			delete result;
			// TODO save specularity stuff somewhere logical. like a material in .obj or something
			Texture texture(textureId, width, height, rows, 0.01f, 40);
			m_Textures.push_back(texture);
			return std::make_shared<Texture>(m_Textures.back());
		}


		#pragma region private_methods

		void ContentManager::makeVertex(const std::string& vertexIndex, const std::string& uvIndex, const std::string& normalIndex,
			const std::vector<maths::Vector3>& vertices, const std::vector<maths::Vector3>& normals, const std::vector<maths::Vector2>& textures, std::vector<VertexTextureNormal>& vtnVector) {

			VertexTextureNormal temp;
			temp.position = vertices[std::stoi(vertexIndex) - 1];
			temp.normal = normals[std::stoi(normalIndex) - 1];
			temp.uv = textures[std::stoi(uvIndex) - 1];
			if (std::find(vtnVector.begin(), vtnVector.end(), temp) != vtnVector.end()) {
				return; // it is already added
			}
			else {
				vtnVector.push_back(temp);
			}
		}

		const unsigned int ContentManager::compileShader(unsigned int shader, const char* src, unsigned int programId) {
			glShaderSource(shader, 1, &src, NULL);
			glCompileShader(shader);

			GLint result;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint len;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
				std::vector<char> error(len);
				glGetShaderInfoLog(shader, len, &len, &error[0]);
				std::string errorMsg(begin(error), end(error));
				std::cout << "Error compiling: " << std::endl << errorMsg << std::endl;
				glDeleteShader(shader);
				return 0;
			}
			glAttachShader(programId, shader);
			return 1;
		}

		const std::string ContentManager::loadFileToString(const char* filePath) {
			FILE* file = fopen(filePath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);
			std::string result(data);
			delete[] data;
			return result;
		}

		const std::vector<std::string> ContentManager::splitString(const std::string& s, const char& c)
		{
			std::string buff{ "" };
			std::vector<std::string> v;

			for (auto n : s)
			{
				if (n != c) buff += n; else
					if (n == c && buff != "") { v.push_back(buff); buff = ""; }
			}
			if (buff != "") v.push_back(buff);

			return v;
		}
		#pragma endregion
	}
}
