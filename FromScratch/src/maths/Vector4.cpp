#include "Vector4.h"

namespace fs {
	namespace maths {
		Vector4::Vector4() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 0;
		}

		Vector4::Vector4(const float& x, const float& y, const float& z, const float& w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4& Vector4::add(const Vector4& that)
		{
			x += that.x;
			y += that.y;
			z += that.z;
			w += that.w;

			return *this;
		}

		Vector4& Vector4::subtract(const Vector4& that)
		{
			x -= that.x;
			y -= that.y;
			z -= that.z;
			w -= that.w;

			return *this;
		}

		Vector4& Vector4::multiply(const Vector4& that)
		{
			x *= that.x;
			y *= that.y;
			z *= that.z;
			w *= that.w;

			return *this;
		}

		Vector4& Vector4::divide(const Vector4& that)
		{
			x /= that.x;
			y /= that.y;
			z /= that.z;
			w /= that.w;

			return *this;
		}

		Vector4 operator+(Vector4 left, const Vector4 & right)
		{
			return left.add(right);
		}

		Vector4 operator-(Vector4 left, const Vector4 & right)
		{
			return left.subtract(right);
		}

		Vector4 operator*(Vector4 left, const Vector4 & right)
		{
			return left.multiply(right);
		}

		Vector4 operator/(Vector4 left, const Vector4 & right)
		{
			return left.divide(right);
		}

		Vector4& Vector4::operator+=(const Vector4& that)
		{
			return add(that);
		}

		Vector4& Vector4::operator-=(const Vector4& that)
		{
			return subtract(that);
		}

		Vector4& Vector4::operator*=(const Vector4& that)
		{
			return multiply(that);
		}

		Vector4& Vector4::operator/=(const Vector4& that)
		{
			return divide(that);
		}

		bool Vector4::operator==(const Vector4& that) {
			return x == that.x && y == that.y;
		}

		bool Vector4::operator!=(const Vector4& that) {
			return !(*this == that);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector4& vector) {
			return stream << "Vector4(X: " << vector.x << ", Y: " << vector.y << ", Z: " << vector.z << ", W: " << vector.w << ")";
		}
	}
}