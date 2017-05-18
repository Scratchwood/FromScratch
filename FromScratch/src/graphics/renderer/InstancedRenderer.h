#ifndef FROMSCRATCH_INCLUDE_INSTANCEDRENDERER
#define FROMSCRATCH_INCLUDE_INSTANCEDRENDERER
#include <map>
#include <vector>
#define FROMSCRATCH_MAX_INSANCES 10000
#define FROMSCRATCH_INSTANCED_DATA_LENGTH 16


namespace fs {
	namespace graphics {
		struct BasicLight;
		struct Shader;
		struct Vector4;
		class Camera;
		class Entity;
		class Model;
		class InstancedRenderer
		{
		private:
			Shader* m_Shader;
			std::map<unsigned int, std::vector<Entity>> m_Entities;
			unsigned int m_InstanceVBO;
			std::vector<float> m_BufferData;
		public:
			InstancedRenderer(Shader* shader);
			~InstancedRenderer();

			void render(BasicLight light, Camera camera);
			void addEntity(const Entity& entity);
		private:
			void bind(const Model& model) const;
			void unbind() const;
		};
	}
}
#endif