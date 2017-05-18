#ifndef FROMSCRATCH_INCLUDE_ENTITY
#define FROMSCRATCH_INCLUDE_ENTITY
#include "Model.h"
#include "Vector3.h"

namespace fs {
	namespace graphics {
		class Entity {
		private:
			ModelPtr& m_Model;
			maths::Vector3 m_Position;
			float m_Rx, m_Ry, m_Rz, m_Scale;
			unsigned int m_Id;
			int m_TextureIndex;
			float m_TextureXOffset, m_TextureYOffset;
		public:
			Entity(ModelPtr& model, maths::Vector3 position, float rx, float ry, float rz, float scale, unsigned int id, int textureIndex = 0);

			void rotate(float dx, float dy, float dz);
			void increasePosition(float dx, float dy, float dz);
			void setNewTextureIndex(int index);
			void setHeight(float height);

			inline ModelPtr const& getModel() const { return m_Model; };
			inline maths::Vector3 getPosition() { return m_Position; };
			inline const float getRotationX() const { return m_Rx; };
			inline const float getRotationY() const { return m_Ry; };
			inline const float getRotationZ() const { return m_Rz; };
			inline const float getScale() const { return m_Scale; };
			inline const float getTextureXOffset() const { return m_TextureXOffset; };
			inline const float getTextureYOffset() const { return m_TextureYOffset; };
			bool operator==(const Entity& that);
		};
	}
}


#endif