#include "Vector2.h"

namespace fs {
	namespace maths {
		Vector2::Vector2() {
			this->x = 0;
			this->y = 0;
		}

		Vector2::Vector2(const float& x, const float& y) {
			this->x = x;
			this->y = y;
		}

		Vector2& Vector2::add(const Vector2& that) {
			x += that.x;
			y += that.y;

			return *this;
		}

		Vector2& Vector2::subtract(const Vector2& that) {
			x -= that.x;
			y -= that.y;

			return *this;
		}

		Vector2& Vector2::multiply(const Vector2& that)	{
			x *= that.x;
			y *= that.y;

			return *this;
		}

		Vector2& Vector2::multiply(const float& that) {
			x *= that;
			y *= that;

			return *this;
		}

		Vector2& Vector2::divide(const Vector2& that) {
			x /= that.x;
			y /= that.y;

			return *this;
		}

		Vector2 Vector2::normalize() const {
			float l = length();
			return Vector2(x / l, y / l);
		}

		float Vector2::length() const {
			return sqrt((x*x) + (y*y));
		}

		float Vector2::dot(const Vector2& that)	{
			return this->x * that.x + this->y * that.y;
		}

		Vector2 operator+(Vector2 left, const Vector2 & right) {
			return left.add(right);
		}

		Vector2 operator-(Vector2 left, const Vector2 & right) {
			return left.subtract(right);
		}

		Vector2 operator*(Vector2 left, const Vector2 & right) {
			return left.multiply(right);
		}

		Vector2 operator*(Vector2 left, const float& right) {
			return left.multiply(right);
		}

		Vector2 operator/(Vector2 left, const Vector2 & right) {
			return left.divide(right);
		}

		Vector2& Vector2::operator+=(const Vector2& that) {
			return add(that);
		}

		Vector2& Vector2::operator-=(const Vector2& that) {
			return subtract(that);
		}

		Vector2& Vector2::operator*=(const Vector2& that) {
			return multiply(that);
		}

		Vector2& Vector2::operator/=(const Vector2& that) {
			return divide(that);
		}

		bool Vector2::operator==(const Vector2& that) {
			return x == that.x && y == that.y;
		}

		bool Vector2::operator!=(const Vector2& that) {
			return !(*this == that);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector2& vector) {
			return stream << "Vector2(X: " << vector.x << ", Y: " << vector.y << ")";
		}
	}
}