#include "Vector3.h"

namespace fs {
	namespace maths {
		Vector3::Vector3() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		Vector3::Vector3(const float x, const float y, const float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3& Vector3::add(const Vector3& that)
		{
			x += that.x;
			y += that.y;
			z += that.z;

			return *this;
		}

		Vector3& Vector3::subtract(const Vector3& that)
		{
			x -= that.x;
			y -= that.y;
			z -= that.z;

			return *this;
		}

		Vector3& Vector3::multiply(const Vector3& that)
		{
			x *= that.x;
			y *= that.y;
			z *= that.z;

			return *this;
		}

		Vector3& Vector3::divide(const Vector3& that)
		{
			x /= that.x;
			y /= that.y;
			z /= that.z;

			return *this;
		}

		Vector3 Vector3::normalize() const {
			float l = length();
			return Vector3(x / l, y / l, z / l);
		}

		Vector3 Vector3::cross(const Vector3& that) const {
			Vector3 result;
			result.x = y * that.z - z * that.y;
			result.y = z * that.x - x * that.z;
			result.z = x * that.y - y * that.x;
			return result;
		}

		float Vector3::dot(const Vector3& that) const {
			return x * that.x + y * that.y + z * that.z;
		}

		float Vector3::length() const {
			return sqrt((x*x) + (y*y) + (z*z));
		}


		Vector3 operator+(Vector3 left, const Vector3 & right)
		{
			return left.add(right);
		}

		Vector3 operator-(Vector3 left, const Vector3 & right)
		{
			return left.subtract(right);
		}

		Vector3 operator*(Vector3 left, const Vector3 & right)
		{
			return left.multiply(right);
		}

		Vector3 operator/(Vector3 left, const Vector3 & right)
		{
			return left.divide(right);
		}

		Vector3& Vector3::operator+=(const Vector3& that)
		{
			return add(that);
		}

		Vector3& Vector3::operator-=(const Vector3& that)
		{
			return subtract(that);
		}

		Vector3& Vector3::operator*=(const Vector3& that)
		{
			return multiply(that);
		}

		Vector3& Vector3::operator/=(const Vector3& that)
		{
			return divide(that);
		}

		bool Vector3::operator==(const Vector3& that) {
			return x == that.x && y == that.y && z == that.z;
		}

		bool Vector3::operator!=(const Vector3& that) {
			return !(*this == that);
		}

		bool Vector3::operator>(const Vector3& that) {
			return x > that.x && y > that.y && z > that.z;
		}

		bool Vector3::operator<(const Vector3& that) {
			return x < that.x && y < that.y && z < that.z;
		}

		bool Vector3::operator>=(const Vector3& that) {
			return !(*this < that);
		}

		bool Vector3::operator<=(const Vector3& that) {
			return !(*this > that);
		}


		std::ostream& operator<<(std::ostream& stream, const Vector3& vector) {
			return stream << "Vector3(X: " << vector.x << ", Y: " << vector.y << ", Z: " << vector.z << ")";
		}
	}
}