#ifndef FROMSCRATCH_INCLUDE_VECTOR3
#define FROMSCRATCH_INCLUDE_VECTOR3
#include <iostream>
namespace fs {
	namespace maths {
		struct Vector3 {
			float x, y, z;

			Vector3();
			Vector3(const float x, const float y, const float z);

			Vector3& add(const Vector3& that);
			Vector3& subtract(const Vector3& that);
			Vector3& multiply(const Vector3& that);
			Vector3& divide(const Vector3& that);
			Vector3 normalize() const;
			Vector3 cross(const Vector3& that) const;
			float dot(const Vector3& that) const;
			float length() const;

			friend Vector3 operator+(Vector3 left, const Vector3& right);
			friend Vector3 operator-(Vector3 left, const Vector3& right);
			friend Vector3 operator*(Vector3 left, const Vector3& right);
			friend Vector3 operator/(Vector3 left, const Vector3& right);

			Vector3& operator+=(const Vector3& that);
			Vector3& operator-=(const Vector3& that);
			Vector3& operator*=(const Vector3& that);
			Vector3& operator/=(const Vector3& that);

			bool operator==(const Vector3& that);
			bool operator!=(const Vector3& that);
			bool operator>(const Vector3& that);
			bool operator<(const Vector3& that);
			bool operator>=(const Vector3& that);
			bool operator<=(const Vector3& that);

			friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);
		};
	}
}
#endif