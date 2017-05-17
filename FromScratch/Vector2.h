#ifndef FROMSCRATCH_INCLUDE_VECTOR2
#define FROMSCRATCH_INCLUDE_VECTOR2
#include <iostream>
namespace fs {
	namespace maths {
		struct Vector2 {
			float x, y;

			Vector2();
			Vector2(const float& x, const float& y);

			Vector2& add(const Vector2& that);
			Vector2& subtract(const Vector2& that);
			Vector2& multiply(const Vector2& that);
			Vector2& multiply(const float& that);
			Vector2& divide(const Vector2& that);
			Vector2 normalize() const;
			float length() const;
			float dot(const Vector2& that);

			friend Vector2 operator+(Vector2 left, const Vector2& right);
			friend Vector2 operator-(Vector2 left, const Vector2& right);
			friend Vector2 operator*(Vector2 left, const Vector2& right);
			friend Vector2 operator*(Vector2 left, const float& right);
			friend Vector2 operator/(Vector2 left, const Vector2& right);

			Vector2& operator+=(const Vector2& that);
			Vector2& operator-=(const Vector2& that);
			Vector2& operator*=(const Vector2& that);
			Vector2& operator/=(const Vector2& that);

			bool operator==(const Vector2& that);
			bool operator!=(const Vector2& that);

			friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);
		};
	}
}
#endif