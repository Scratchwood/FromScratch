#include "Entity.h"

namespace fs {
	namespace graphics {
		Entity::Entity(ModelPtr& model, maths::Vector3 position, float rx, float ry, float rz, float scale, unsigned int id, int textureIndex) :
			m_Model(model) {
			m_Position = position;
			m_Rx = rx;
			m_Ry = ry;
			m_Rz = rz;
			m_Scale = scale;
			m_Id = id;
			setNewTextureIndex(textureIndex);
		}

		void Entity::rotate(float dx, float dy, float dz) {
			m_Rx += dx;
			m_Ry += dy;
			m_Rz += dz;
		}

		void Entity::increasePosition(float dx, float dy, float dz) {
			m_Position.x += dx;
			m_Position.y += dy;
			m_Position.z += dz;
		}

		void Entity::setNewTextureIndex(int index)
		{
			m_TextureIndex = index;
			int rows = m_Model->getTexture()->getRows();
			int column = m_TextureIndex % rows;
			int row = m_TextureIndex / rows;
			m_TextureXOffset = (float)column / (float)rows;
			m_TextureYOffset = (float)row / (float)rows;
		}

		void Entity::setHeight(float height)
		{
			m_Position.y = height;
		}

		bool Entity::operator==(const Entity & that)
		{
			return this->m_Id == that.m_Id ;
		}
	}
}