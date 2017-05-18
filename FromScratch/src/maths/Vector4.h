#ifndef FROMSCRATCH_INCLUDE_VECTOR4
#define FROMSCRATCH_INCLUDE_VECTOR4
#include <iostream>
namespace fs {
	namespace maths {
		struct Vector4 {
			float x, y, z, w;

			Vector4();
			Vector4(const float& x, const float& y, const float& z, const float& w);

			Vector4& add(const Vector4& that);
			Vector4& subtract(const Vector4& that);
			Vector4& multiply(const Vector4& that);
			Vector4& divide(const Vector4& that);

			friend Vector4 operator+(Vector4 left, const Vector4& right);
			friend Vector4 operator-(Vector4 left, const Vector4& right);
			friend Vector4 operator*(Vector4 left, const Vector4& right);
			friend Vector4 operator/(Vector4 left, const Vector4& right);

			Vector4& operator+=(const Vector4& that);
			Vector4& operator-=(const Vector4& that);
			Vector4& operator*=(const Vector4& that);
			Vector4& operator/=(const Vector4& that);

			bool operator==(const Vector4& that);
			bool operator!=(const Vector4& that);

			friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector);
		};
	}
}
#endif