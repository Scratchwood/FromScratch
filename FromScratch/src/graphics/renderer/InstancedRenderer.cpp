#include "InstancedRenderer.h"
#include "BasicLight.h"
#include "Shader.h"
#include "Entity.h"
#include "Camera.h"
#include "MathsUtil.h"
#include <GL\glew.h>

namespace fs {
	namespace graphics {
		InstancedRenderer::InstancedRenderer(Shader * shader)
		{
			m_Shader = shader;
			glBindAttribLocation(shader->getId(), 3, "model");
		}

		InstancedRenderer::~InstancedRenderer()
		{
			delete m_Shader;
		}

		void InstancedRenderer::render(BasicLight light, Camera camera)
		{
			m_Shader->enable();
			m_Shader->setView(maths::MathsUtil::createViewMatrix(camera));
			m_Shader->setLight(light);
			for (auto it = m_Entities.begin(); it != m_Entities.end(); ++it) {
				m_BufferData.clear();
				std::vector<Entity> batch = it->second;
				for (auto batch_it = batch.begin(); batch_it != batch.end(); ++batch_it) {
					maths::Matrix4 transformation = maths::MathsUtil::createTransformation(batch_it->getPosition(), 0, maths::Vector3(0, 0, 0), batch_it->getScale());

					m_BufferData.push_back(transformation.columns[0].x);
					m_BufferData.push_back(transformation.columns[0].y);
					m_BufferData.push_back(transformation.columns[0].z);
					m_BufferData.push_back(transformation.columns[0].w);

					m_BufferData.push_back(transformation.columns[1].x);
					m_BufferData.push_back(transformation.columns[1].y);
					m_BufferData.push_back(transformation.columns[1].z);
					m_BufferData.push_back(transformation.columns[1].w);

					m_BufferData.push_back(transformation.columns[2].x);
					m_BufferData.push_back(transformation.columns[2].y);
					m_BufferData.push_back(transformation.columns[2].z);
					m_BufferData.push_back(transformation.columns[2].w);

					m_BufferData.push_back(transformation.columns[3].x);
					m_BufferData.push_back(transformation.columns[3].y);
					m_BufferData.push_back(transformation.columns[3].z);
					m_BufferData.push_back(transformation.columns[3].w);
				}
				bind(*batch[0].getModel());		

				glDrawElementsInstanced(GL_TRIANGLES, batch[0].getModel()->getMesh()->getVertexCount(), GL_UNSIGNED_INT, 0, m_BufferData.size());

				unbind();
			}
			
			m_Shader->disable();
			m_Entities.clear();
		}

		void InstancedRenderer::addEntity(const Entity & entity)
		{
			auto it = m_Entities.find(entity.getModel()->getId());
			if (it == m_Entities.end()) {
				std::vector<Entity> tempV;
				tempV.push_back(entity);
				m_Entities.insert({ entity.getModel()->getId(), tempV });
				return;
			}
			it->second.push_back(entity);
		}

		void InstancedRenderer::bind(const Model& model) const
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model.getTexture()->getId());

			glBindVertexArray(model.getMesh()->getVAO());

			glBindBuffer(GL_ARRAY_BUFFER, model.getMesh()->getVBO());
			glBufferSubData(GL_ARRAY_BUFFER, 8 * sizeof(float), m_BufferData.size(), &m_BufferData);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);
			glEnableVertexAttribArray(5);
			glEnableVertexAttribArray(6);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.getMesh()->getIBO());
			m_Shader->setSpecularity(model.getTexture()->getReflectivity(), model.getTexture()->getShineDamper());
		}

		void InstancedRenderer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(3);
			glDisableVertexAttribArray(4);
			glDisableVertexAttribArray(5);
			glDisableVertexAttribArray(6);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}