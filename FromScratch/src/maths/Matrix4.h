#ifndef FROMSCRATCH_INCLUDE_MATRIX4
#define FROMSCRATCH_INCLUDE_MATRIX4
#include "Vector3.h"
#include "Vector4.h"

#define MATRIX_D1 0
#define MATRIX_D2 5
#define MATRIX_D3 10
#define MATRIX_D4 15

namespace fs {
	namespace maths {
		struct Matrix4 {
			union {
				float elements[16];
				Vector4 columns[4];
			};

			Matrix4();
			Matrix4(float diagonal);

			static Matrix4 identity();
			static Matrix4 orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
			static Matrix4 perspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
			Matrix4& translate(const Vector3& vector);
			Matrix4& rotate(const float angle, const Vector3& axis);
			Matrix4& scale(const Vector3& scale);
			static Matrix4 createLookAt(const Vector3& cameraPosition, const Vector3& target, const Vector3& upVector);

			Matrix4& inverse();
			Matrix4& multiply(const Matrix4& that);
			friend Matrix4 operator*(Matrix4 left, const Matrix4& right);
			Matrix4& operator*=(const Matrix4& that);

			Vector3 multiply(const Vector3& that) const;
			friend Vector3 operator*(const Matrix4& left, const Vector3& right);

			Vector4 multiply(const Vector4& that) const;
			friend Vector4 operator*(const Matrix4& left, const Vector4& right);

			friend std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix);
		};
	}
}
#endif
