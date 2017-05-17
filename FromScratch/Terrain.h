#ifndef FROMSCRATCH_INCLUDE_PLANE
#define FROMSCRATCH_INCLUDE_PLANE
#include "Model.h"
#include <vector>
#include "VertexTextureNormal.h"
#define TERRAIN_SIZE 100
#define TERRAIN_HEIGHT 10
#define TERRAIN_MAX_COLOR 256*256*256

namespace fs {
	namespace graphics {
		class ContentManager;
		class Terrain {
		public:
			ModelPtr m_Model;
			float m_X, m_Z;
			std::vector<VertexTextureNormal> m_Vertices;
			float** m_Grid;
			int m_LengthOfSide;
		public:
			Terrain(ContentManager& content, const char* texture, const char* heightMap, float x, float z);
			~Terrain();
			float getHeight(float x, float z);
		};
	}
}


#endif