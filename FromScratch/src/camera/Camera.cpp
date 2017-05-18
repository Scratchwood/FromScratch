#include "Camera.h"


namespace fs {
	namespace graphics {
		Camera::Camera(const maths::Vector3& pos, float pitch, float yaw, float roll) {
			m_Position = pos;
			m_Pitch = pitch;
			m_Yaw = yaw;
			m_Roll = roll;
		}

		void Camera::move(float dx, float dy, float dz) {
			m_Position.x += dx;
			m_Position.y += dy;
			m_Position.z += dz;
		}

		void Camera::rotate(float dx, float dy, float dz) {
			m_Pitch += dx;
			m_Yaw += dy;
			m_Roll += dz;
		}
	}
}