#include "Matrix4.h"
#include <algorithm>
#include "MathsUtil.h"

namespace fs {
	namespace maths {
		Matrix4::Matrix4() {
			for (int i = 0; i < 16; i++) {
				elements[i] = 0;
			}
		}

		Matrix4::Matrix4(float diagonal) {
			for (int i = 0; i < 16; i++) {
				elements[i] = 0;
			}
			elements[MATRIX_D1] = diagonal;
			elements[MATRIX_D2] = diagonal;
			elements[MATRIX_D3] = diagonal;
			elements[MATRIX_D4] = diagonal;
		}

		Matrix4 Matrix4::identity()
		{
			return Matrix4(1.0f);
		}

		Matrix4 Matrix4::orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
			Matrix4 matrix = identity();
			matrix.elements[MATRIX_D1] = 2.0f / (right - left);
			matrix.elements[MATRIX_D2] = 2.0f / (top - bottom);
			matrix.elements[MATRIX_D3] = 2.0f / (nearPlane / farPlane);

			matrix.elements[12] = (left + right) / (left - right);
			matrix.elements[13] = (bottom + top) / (bottom - top);
			matrix.elements[14] = (farPlane + nearPlane) / (farPlane - nearPlane);

			return matrix;
		}

		Matrix4 Matrix4::perspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)	{
			Matrix4 matrix;
			float q = 1.0f / (tan(MathsUtil::toRadians(0.5f * fieldOfView)));
			float a = q / aspectRatio;

			float b = (nearPlane + farPlane) / (nearPlane - farPlane);
			float c = (2.0f * nearPlane * farPlane) / (nearPlane - farPlane);

			matrix.elements[MATRIX_D1] = a;
			matrix.elements[MATRIX_D2] = q;
			matrix.elements[MATRIX_D3] = b;
			matrix.elements[11] = -1.0f;
			matrix.elements[14] = c;

			return matrix;
		}

		Matrix4& Matrix4::translate(const Vector3 & vector)	{
			this->elements[12] = this->elements[0] * vector.x + this->elements[4] * vector.y + this->elements[8] * vector.z + this->elements[12];
			this->elements[13] = this->elements[1] * vector.x + this->elements[5] * vector.y + this->elements[9] * vector.z + this->elements[13];
			this->elements[14] = this->elements[2] * vector.x + this->elements[6] * vector.y + this->elements[10] * vector.z + this->elements[14];
			this->elements[15] = this->elements[3] * vector.x + this->elements[7] * vector.y + this->elements[11] * vector.z + this->elements[15];

			return *this;
		}

		Matrix4& Matrix4::rotate(const float angle, const Vector3 & axis) {
			if (axis.x == 0 && axis.y == 0 && axis.z == 0) {
				return *this;
			}
			float b00, b01, b02, b10, b11, b12, b20, b21, b22, a00, a01, a02, a03, a10, a11, a12, a13, a20, a21, a22, a23;
			Vector3 na = axis.normalize();
			float x = na.x;
			float y = na.y;
			float z = na.z;

			float rads = MathsUtil::toRadians(angle);
			float c = cos(rads);
			float t = 1.0f - c;
			float s = sin(rads);

			b00 = x * x * t + c; 
			b01 = y * x * t + z * s; 
			b02 = z * x * t - y * s;

			b10 = x * y * t - z * s; 
			b11 = y * y * t + c; 
			b12 = z * y * t + x * s;

			b20 = x * z * t + y * s; 
			b21 = y * z * t - x * s; 
			b22 = z * z * t + c;

			a00 = this->elements[0]; a01 = this->elements[1]; a02 = this->elements[2]; a03 = this->elements[3];
			a10 = this->elements[4]; a11 = this->elements[5]; a12 = this->elements[6]; a13 = this->elements[7];
			a20 = this->elements[8]; a21 = this->elements[9]; a22 = this->elements[10]; a23 = this->elements[11];

			this->elements[0] = a00 * b00 + a10 * b01 + a20 * b02;
			this->elements[1] = a01 * b00 + a11 * b01 + a21 * b02;
			this->elements[2] = a02 * b00 + a12 * b01 + a22 * b02;
			this->elements[3] = a03 * b00 + a13 * b01 + a23 * b02;
			this->elements[4] = a00 * b10 + a10 * b11 + a20 * b12;
			this->elements[5] = a01 * b10 + a11 * b11 + a21 * b12;
			this->elements[6] = a02 * b10 + a12 * b11 + a22 * b12;
			this->elements[7] = a03 * b10 + a13 * b11 + a23 * b12;
			this->elements[8] = a00 * b20 + a10 * b21 + a20 * b22;
			this->elements[9] = a01 * b20 + a11 * b21 + a21 * b22;
			this->elements[10] = a02 * b20 + a12 * b21 + a22 * b22;
			this->elements[11] = a03 * b20 + a13 * b21 + a23 * b22;

			return *this;
		}

		Matrix4& Matrix4::scale(const Vector3 & scale) {
			this->elements[0] =  this->elements[0] * scale.x;
			this->elements[1] =  this->elements[1] * scale.x;
			this->elements[2] =  this->elements[2] * scale.x;
			this->elements[3] =  this->elements[3] * scale.x;
			this->elements[4] =  this->elements[4] * scale.y;
			this->elements[5] =  this->elements[5] * scale.y;
			this->elements[6] =  this->elements[6] * scale.y;
			this->elements[7] =  this->elements[7] * scale.y;
			this->elements[8] =  this->elements[8] * scale.z;
			this->elements[9] =  this->elements[9] * scale.z;
			this->elements[10] = this->elements[10] * scale.z;
			this->elements[11] = this->elements[11] * scale.z;

			return *this;
		}

		Matrix4 Matrix4::createLookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& cameraUp) {
			Matrix4 result;
			Vector3 X, Y, Z;

			Z = cameraPosition - cameraTarget;
			Z = Z.normalize();

			X = cameraUp.cross(Z);
			Y = Z.cross(X);

			X = X.normalize();
			Y = Y.normalize();

			result.elements[0 + 0 * 4] = X.x;
			result.elements[0 + 1 * 4] = X.y;
			result.elements[0 + 2 * 4] = X.z;
			result.elements[0 + 3 * 4] = -X.dot(cameraPosition);

			result.elements[1 + 0 * 4] = Y.x;
			result.elements[1 + 1 * 4] = Y.y;
			result.elements[1 + 2 * 4] = Y.z;
			result.elements[1 + 3 * 4] = -Y.dot(cameraPosition);

			result.elements[2 + 0 * 4] = Z.x;
			result.elements[2 + 1 * 4] = Z.y;
			result.elements[2 + 2 * 4] = Z.z;
			result.elements[2 + 3 * 4] = -Z.dot(cameraPosition);

			result.elements[3 + 0 * 4] = 0;
			result.elements[3 + 1 * 4] = 0;
			result.elements[3 + 2 * 4] = 0;
			result.elements[3 + 3 * 4] = 1.0f;

			return result;
		}

		Matrix4& Matrix4::inverse() {
			// all hail stack overflow
			float matrix[16];

			matrix[0] = elements[5] * elements[10] * elements[15] -
				elements[5] * elements[11] * elements[14] -
				elements[9] * elements[6] * elements[15] +
				elements[9] * elements[7] * elements[14] +
				elements[13] * elements[6] * elements[11] -
				elements[13] * elements[7] * elements[10];

			matrix[4] = -elements[4] * elements[10] * elements[15] +
				elements[4] * elements[11] * elements[14] +
				elements[8] * elements[6] * elements[15] -
				elements[8] * elements[7] * elements[14] -
				elements[12] * elements[6] * elements[11] +
				elements[12] * elements[7] * elements[10];

			matrix[8] = elements[4] * elements[9] * elements[15] -
				elements[4] * elements[11] * elements[13] -
				elements[8] * elements[5] * elements[15] +
				elements[8] * elements[7] * elements[13] +
				elements[12] * elements[5] * elements[11] -
				elements[12] * elements[7] * elements[9];

			matrix[12] = -elements[4] * elements[9] * elements[14] +
				elements[4] * elements[10] * elements[13] +
				elements[8] * elements[5] * elements[14] -
				elements[8] * elements[6] * elements[13] -
				elements[12] * elements[5] * elements[10] +
				elements[12] * elements[6] * elements[9];

			matrix[1] = -elements[1] * elements[10] * elements[15] +
				elements[1] * elements[11] * elements[14] +
				elements[9] * elements[2] * elements[15] -
				elements[9] * elements[3] * elements[14] -
				elements[13] * elements[2] * elements[11] +
				elements[13] * elements[3] * elements[10];

			matrix[5] = elements[0] * elements[10] * elements[15] -
				elements[0] * elements[11] * elements[14] -
				elements[8] * elements[2] * elements[15] +
				elements[8] * elements[3] * elements[14] +
				elements[12] * elements[2] * elements[11] -
				elements[12] * elements[3] * elements[10];

			matrix[9] = -elements[0] * elements[9] * elements[15] +
				elements[0] * elements[11] * elements[13] +
				elements[8] * elements[1] * elements[15] -
				elements[8] * elements[3] * elements[13] -
				elements[12] * elements[1] * elements[11] +
				elements[12] * elements[3] * elements[9];

			matrix[13] = elements[0] * elements[9] * elements[14] -
				elements[0] * elements[10] * elements[13] -
				elements[8] * elements[1] * elements[14] +
				elements[8] * elements[2] * elements[13] +
				elements[12] * elements[1] * elements[10] -
				elements[12] * elements[2] * elements[9];

			matrix[2] = elements[1] * elements[6] * elements[15] -
				elements[1] * elements[7] * elements[14] -
				elements[5] * elements[2] * elements[15] +
				elements[5] * elements[3] * elements[14] +
				elements[13] * elements[2] * elements[7] -
				elements[13] * elements[3] * elements[6];

			matrix[6] = -elements[0] * elements[6] * elements[15] +
				elements[0] * elements[7] * elements[14] +
				elements[4] * elements[2] * elements[15] -
				elements[4] * elements[3] * elements[14] -
				elements[12] * elements[2] * elements[7] +
				elements[12] * elements[3] * elements[6];

			matrix[10] = elements[0] * elements[5] * elements[15] -
				elements[0] * elements[7] * elements[13] -
				elements[4] * elements[1] * elements[15] +
				elements[4] * elements[3] * elements[13] +
				elements[12] * elements[1] * elements[7] -
				elements[12] * elements[3] * elements[5];

			matrix[14] = -elements[0] * elements[5] * elements[14] +
				elements[0] * elements[6] * elements[13] +
				elements[4] * elements[1] * elements[14] -
				elements[4] * elements[2] * elements[13] -
				elements[12] * elements[1] * elements[6] +
				elements[12] * elements[2] * elements[5];

			matrix[3] = -elements[1] * elements[6] * elements[11] +
				elements[1] * elements[7] * elements[10] +
				elements[5] * elements[2] * elements[11] -
				elements[5] * elements[3] * elements[10] -
				elements[9] * elements[2] * elements[7] +
				elements[9] * elements[3] * elements[6];

			matrix[7] = elements[0] * elements[6] * elements[11] -
				elements[0] * elements[7] * elements[10] -
				elements[4] * elements[2] * elements[11] +
				elements[4] * elements[3] * elements[10] +
				elements[8] * elements[2] * elements[7] -
				elements[8] * elements[3] * elements[6];

			matrix[11] = -elements[0] * elements[5] * elements[11] +
				elements[0] * elements[7] * elements[9] +
				elements[4] * elements[1] * elements[11] -
				elements[4] * elements[3] * elements[9] -
				elements[8] * elements[1] * elements[7] +
				elements[8] * elements[3] * elements[5];

			matrix[15] = elements[0] * elements[5] * elements[10] -
				elements[0] * elements[6] * elements[9] -
				elements[4] * elements[1] * elements[10] +
				elements[4] * elements[2] * elements[9] +
				elements[8] * elements[1] * elements[6] -
				elements[8] * elements[2] * elements[5];

			float determinant = elements[0] * matrix[0] + elements[1] * matrix[4] + elements[2] * matrix[8] + elements[3] * matrix[12];

			determinant = 1.0f / determinant;

			for (int i = 0; i < 16; i++) {
				elements[i] = matrix[i] * determinant;
			}

			return *this;
		}

		Matrix4& Matrix4::multiply(const Matrix4 & that) {
			float data[16];
			for (int row = 0; row < 4; row++) {
				for (int column = 0; column < 4; column++) {
					float sum = 0.0f;
					for (int element = 0; element < 4; element++) {
						sum += elements[column + element * 4] * that.elements[element + row * 4];
					}
					data[column + row * 4] = sum;
				}
			}
			memcpy(elements, data, 4 * 4 * sizeof(float));
			return *this;
		}

		Vector3 Matrix4::multiply(const Vector3& that) const {
			return Vector3(
				columns[0].x * that.x + columns[1].x * that.y + columns[2].x * that.z + columns[3].x,
				columns[0].y * that.x + columns[1].y * that.y + columns[2].y * that.z + columns[3].y,
				columns[0].z * that.x + columns[1].z * that.y + columns[2].z * that.z + columns[3].z
			);
		}

		Vector4 Matrix4::multiply(const Vector4& that) const {
			return Vector4(
				columns[0].x * that.x + columns[1].x * that.y + columns[2].x * that.z + columns[3].x * that.w,
				columns[0].y * that.x + columns[1].y * that.y + columns[2].y * that.z + columns[3].y * that.w,
				columns[0].z * that.x + columns[1].z * that.y + columns[2].z * that.z + columns[3].z * that.w,
				columns[0].w * that.x + columns[1].w * that.y + columns[2].w * that.z + columns[3].w * that.w
			);
		}

		Vector3 operator*(const Matrix4 & left, const Vector3 & right) {
			return left.multiply(right);
		}

		Vector4 operator*(const Matrix4 & left, const Vector4 & right) {
			return left.multiply(right);
		}


		Matrix4& Matrix4::operator*=(const Matrix4 & that) {
			return multiply(that);
		}

		Matrix4 operator*(Matrix4 left, const Matrix4 & right) {
			return left.multiply(right);
		}

		std::ostream & operator<<(std::ostream & stream, const Matrix4& matrix)	{
			return stream <<
				"[" << matrix.elements[0 + 0 * 4] << ", " << matrix.elements[0 + 1 * 4] << ", " << matrix.elements[0 + 2 * 4] << ", " << matrix.elements[0 + 3 * 4] << "]" << std::endl
				<< "[" << matrix.elements[1 + 0 * 4] << ", " << matrix.elements[1 + 1 * 4] << ", " << matrix.elements[1 + 2 * 4] << ", " << matrix.elements[1 + 3 * 4] << "]" << std::endl
				<< "[" << matrix.elements[2 + 0 * 4] << ", " << matrix.elements[2 + 1 * 4] << ", " << matrix.elements[2 + 2 * 4] << ", " << matrix.elements[2 + 3 * 4] << "]" << std::endl
				<< "[" << matrix.elements[3 + 0 * 4] << ", " << matrix.elements[3 + 1 * 4] << ", " << matrix.elements[3 + 2 * 4] << ", " << matrix.elements[3 + 3 * 4] << "]" << std::endl;
		}
	}
}