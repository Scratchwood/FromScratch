#include "Shader.h"
#include <GL\glew.h>

namespace fs {
	namespace graphics {
		Shader::Shader(unsigned int id, unsigned int vid, unsigned int fid) {
			m_Id = id;
			m_VertexId = vid;
			m_FragmentId = fid;

			glBindAttribLocation(m_Id, 0, "position");
			glBindAttribLocation(m_Id, 1, "texCoords");
			glBindAttribLocation(m_Id, 2, "normal");

			m_LocationMap["projection"]		= glGetUniformLocation(m_Id, "projection");
			m_LocationMap["view"]			= glGetUniformLocation(m_Id, "view");
			m_LocationMap["model"]			= glGetUniformLocation(m_Id, "model");
			m_LocationMap["lightPosition"]	= glGetUniformLocation(m_Id, "lightPosition");
			m_LocationMap["lightColor"]		= glGetUniformLocation(m_Id, "lightColor");
			m_LocationMap["reflectivity"]	= glGetUniformLocation(m_Id, "reflectivity");
			m_LocationMap["shineDamper"]	= glGetUniformLocation(m_Id, "shineDamper");
		}

		void Shader::enable() const {
			glUseProgram(m_Id);
		}

		void Shader::disable() const {
			glUseProgram(0);
		}

		void Shader::setUniform(const std::string& name, const float value) {
			glUniform1f(getLocation(name), value);
		}

		void Shader::setUniform(const std::string & name, const int value) {
			glUniform1i(getLocation(name), value);
		}

		void Shader::setUniform(const std::string & name, const unsigned int count, const float * value) {
			glUniform1fv(getLocation(name), count, value);
		}

		void Shader::setUniform(const std::string & name, const unsigned int count, const int * value) {
			glUniform1iv(getLocation(name), count, value);
		}

		void Shader::setUniform(const std::string & name, const maths::Matrix4 & value)	{
			glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, value.elements);
		}

		void Shader::setUniform(const std::string & name, const maths::Vector2 & value)	{
			glUniform2f(getLocation(name), value.x, value.y);
		}

		void Shader::setUniform(const std::string & name, const maths::Vector3 & value)	{
			glUniform3f(getLocation(name), value.x, value.y, value.z);
		}

		void Shader::setUniform(const std::string & name, const maths::Vector4 & value)	{
			glUniform4f(getLocation(name), value.x, value.y, value.z, value.w);
		}

		void Shader::setProjection(const maths::Matrix4 & value) {
			glUniformMatrix4fv(m_LocationMap["projection"], 1, GL_FALSE, value.elements);
		}

		void Shader::setView(const maths::Matrix4 & value) {
			glUniformMatrix4fv(m_LocationMap["view"], 1, GL_FALSE, value.elements);
		}

		void Shader::setModel(const maths::Matrix4 & value)	{
			glUniformMatrix4fv(m_LocationMap["model"], 1, GL_FALSE, value.elements);
		}

		void Shader::setLight(const BasicLight& value) {
			glUniform3f(m_LocationMap["lightPosition"], value.position.x, value.position.y, value.position.z);
			glUniform4f(m_LocationMap["lightColor"], value.color.x, value.color.y, value.color.z, value.color.w);
		}

		void Shader::setSpecularity(const float reflectivity, const float damper)
		{
			glUniform1f(m_LocationMap["reflectivity"], reflectivity);
			glUniform1f(m_LocationMap["shineDamper"], damper);
		}

		unsigned int Shader::getLocation(const std::string& name) {
			if (m_LocationMap[name] == NULL) {
				m_LocationMap[name] = glGetUniformLocation(m_Id, name.c_str());
			}
			return m_LocationMap[name];
		}
	}
}