#ifndef FROMSCRATCH_INCLUDE_CAMERA
#define FROMSCRATCH_INCLUDE_CAMERA
#include "Vector3.h"

namespace fs {
	namespace graphics {
		class Camera {
		private:
			maths::Vector3 m_Position;
			float m_Pitch, m_Yaw, m_Roll;
		public:
			Camera(const maths::Vector3& pos, float pitch, float yaw, float roll);

			void move(float dx, float dy, float dz);
			void rotate(float dx, float dy, float dz);

			inline const maths::Vector3 getPosition() const { return m_Position; };
			inline const float getPitch() const { return m_Pitch; };
			inline const float getYaw() const { return m_Yaw; };
			inline const float getRoll() const { return m_Roll; };
		};
	}
}

#endif
