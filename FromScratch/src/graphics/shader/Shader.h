#ifndef FROMSCRATCH_INCLUDE_SHADER
#define FROMSCRATCH_INCLUDE_SHADER

#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "BasicLight.h"
#include <map>
#include <string>

#define ShaderPtr std::shared_ptr<graphics::Shader>

namespace fs {
	namespace graphics {
		struct Shader {
		private:
			unsigned int m_Id, m_VertexId, m_FragmentId;
			std::map<std::string, unsigned int> m_LocationMap;
		public:
			Shader(unsigned int id, unsigned int vid, unsigned int fid);
			void enable() const;
			void disable() const;
			inline const unsigned int getId() const { return m_Id; };

			void setUniform(const std::string& name, const float value);
			void setUniform(const std::string& name, const int value);
			void setUniform(const std::string& name, const unsigned int count, const float* value);
			void setUniform(const std::string& name, const unsigned int count, const int* value);
			void setUniform(const std::string& name, const maths::Matrix4& value);
			void setUniform(const std::string& name, const maths::Vector2& value);
			void setUniform(const std::string& name, const maths::Vector3& value);
			void setUniform(const std::string& name, const maths::Vector4& value);
			void setProjection(const maths::Matrix4& value);
			void setView(const maths::Matrix4& value);
			void setModel(const maths::Matrix4& value);
			void setLight(const BasicLight& value);
			void setSpecularity(const float reflectivity, const float damper);
		private:
			unsigned int getLocation(const std::string& name);
		};
	}
}

#endif;