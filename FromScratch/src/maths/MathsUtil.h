#ifndef FROMSCRATCH_INCLUDE_MATHSUTIL
#define FROMSCRATCH_INCLUDE_MATHSUTIL
#define _USE_MATH_DEFINES
#include <math.h>
#include "Matrix4.h"
#include "Vector2.h"
#include "Camera.h"

namespace fs {
	namespace maths {
		class MathsUtil {
		public:
			inline static float toRadians(float degrees) {
				return (float)(degrees * (M_PI / 180.0f));
			}

			static maths::Matrix4 createTransformation(Vector3 translation, float angle, Vector3 axis, float scale) {
				Matrix4 transformation(1.0f);
				return transformation.translate(translation).rotate(angle, axis).scale(Vector3(scale, scale, scale));
			}

			static maths::Matrix4 createViewMatrix(graphics::Camera camera) {
				Matrix4 viewMatrix(1.0f);
				Vector3 negPos(-camera.getPosition().x, -camera.getPosition().y, -camera.getPosition().z);
				return viewMatrix.rotate(camera.getPitch(), Vector3(1, 0, 0)).rotate(camera.getYaw(), Vector3(0, 1, 0)).translate(negPos);
			}

			static float barryCentric(Vector3& p1, Vector3& p2, Vector3& p3, Vector2& pos) {
				// flash! ah-AAAAA
				float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
				float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
				float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
				float l3 = 1.0f - l1 - l2;
				return l1 * p1.y + l2 * p2.y + l3 * p3.y;
			}
		};
	}
}

#endif
