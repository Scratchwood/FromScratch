#include "Terrain.h"
#include <GL\glew.h>
#include "VertexTextureNormal.h"
#include "ContentManager.h"
#include "MathsUtil.h"

namespace fs {
	namespace graphics {
		Terrain::Terrain(ContentManager& content, const char* texture, const char* heightMap, float x, float z) {
			// load heightmap and make it into a texture
			TexturePtr heightmapTexture = content.loadTexture(heightMap);
			glBindTexture(GL_TEXTURE_2D, heightmapTexture->getId());
			int size = heightmapTexture->getHeight() * heightmapTexture->getWidth() * 3;
			unsigned char* imageInfo = new unsigned char[size];
			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, imageInfo);
			glBindTexture(GL_TEXTURE_2D, 0);
			// init grid as a 2D array for ease of debugging
			m_LengthOfSide = heightmapTexture->getHeight();
			m_Grid = new float*[m_LengthOfSide];
			for (int i = 0; i < m_LengthOfSide; i++) {
				m_Grid[i] = new float[m_LengthOfSide];
			}
			// extract the color of the pixel and convert it to a height
			int tx = 0, ty = 0;
			for (int i = 0; i < size; i+=3) {
				int r = (int)*imageInfo++ ;
				int g = (int)*imageInfo++ ;
				int b = (int)*imageInfo++ ;
				float c = (b << 16) | (g << 8) | r;
				float height = c;
				height -= TERRAIN_MAX_COLOR / 2.0f;
				height /= TERRAIN_MAX_COLOR / 2.0f;
				height *= TERRAIN_HEIGHT;
				m_Grid[tx][ty] = height;
				tx++;
				if (tx % m_LengthOfSide == 0) {
					tx = 0;
					ty++;
				}
			}
			//delete imageInfo; // I feel like I should do this but it gets sad when I do it. 

			// print debug info
			for (int y = 0; y < m_LengthOfSide; y++) {
				for (int x = 0; x < m_LengthOfSide; x++) {
					std::cout << m_Grid[x][y] << " , ";
				}
				std::cout << std::endl;
			}
			std::vector<VertexTextureNormal> vertices;
			std::vector<unsigned int> indices;
			int vertexPointer = 0;
			float l, d, r, u;
			// for each height in the grid, make a vertex with appropriate coordinates
			for (int i = 0; i < m_LengthOfSide; i++) {
				for (int j = 0; j < m_LengthOfSide; j++) {
					VertexTextureNormal vtn;
					int x = (float)j / ((float)m_LengthOfSide - 1) * TERRAIN_SIZE;
					int z = (float)i / ((float)m_LengthOfSide - 1) * TERRAIN_SIZE;
					vtn.position = maths::Vector3(
						x,
						m_Grid[j][i],
						z);
					// method for calculating normal described in: http://stackoverflow.com/questions/13983189/opengl-how-to-calculate-normals-in-a-terrain-height-grid
					// potentially incorrectly implemented..
					/*l = getHeight(j, i - 1);
					r = getHeight(j, i + 1);
					d = getHeight(j - 1, i);
					u = getHeight(j + 1, i);
					vtn.normal = maths::Vector3(l-r, d-u, 2.0f).normalize();*/
					vtn.normal = maths::Vector3(0, 1, 0);
					vtn.uv = maths::Vector2((float)j / ((float)m_LengthOfSide - 1), (float)i / ((float)m_LengthOfSide - 1));
					vertices.push_back(vtn);
				}
			}

			for (int gz = 0; gz < m_LengthOfSide - 1; gz++) {
				for (int gx = 0; gx< m_LengthOfSide - 1; gx++) {
					int topLeft = (gz * m_LengthOfSide) + gx;
					int topRight = topLeft + 1;
					int bottomLeft = ((gz + 1) * m_LengthOfSide) + gx;
					int bottomRight = bottomLeft + 1;
					indices.push_back(topLeft);
					indices.push_back(bottomLeft);
					indices.push_back(topRight);
					indices.push_back(topRight);
					indices.push_back(bottomLeft);
					indices.push_back(bottomRight);
				}	
			}
			m_Vertices = vertices;
			m_Model = content.loadModel(vertices, indices, texture);
			m_X = x * TERRAIN_SIZE;
			m_Z = z * TERRAIN_SIZE;
		}

		Terrain::~Terrain()
		{
			for (int i = 0; i < m_LengthOfSide; ++i) {
				delete[] m_Grid[i];
			}
			delete[] m_Grid;
		}

		float Terrain::getHeight(float x, float z)
		{
			/*if (x < 0 || x >= m_LengthOfSide || z < 0 || z >= m_LengthOfSide) {
				std::cout << "OUT OF BOUNDS" << std::endl;
				return 0;
			}*/
			// transform an x,z coordinate into various different spaces to finally use
			// barrycentric method to calculate the height
			float localX = x - m_X;
			float localZ = z - m_Z;
			float gridQuadSize = TERRAIN_SIZE / (m_LengthOfSide);
			int gridX = std::floor(localX / gridQuadSize);
			int gridY = std::floor(localZ / gridQuadSize);
			float xCoord = std::fmodf(localX, gridQuadSize) / gridQuadSize;
			float zCoord = std::fmodf(localZ, gridQuadSize) / gridQuadSize;
			float height = 0.0f;

			if (xCoord <= (1 - zCoord)) {
				height = maths::MathsUtil::barryCentric(maths::Vector3(0, m_Grid[gridX][gridY], 0),
					maths::Vector3(1, m_Grid[gridX +1][gridY], 0),
					maths::Vector3(0, m_Grid[gridX][gridY +1], 1),
					maths::Vector2(xCoord, zCoord));
			}
			else {
				height = maths::MathsUtil::barryCentric(maths::Vector3(1, m_Grid[gridX +1][gridY], 0),
					maths::Vector3(1, m_Grid[gridX +1][gridY +1], 1),
					maths::Vector3(0, m_Grid[gridX][gridY +1], 1),
					maths::Vector2(xCoord, zCoord));
			}
			return height;
		}
	}
}