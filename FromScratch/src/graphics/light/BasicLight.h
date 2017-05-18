#ifndef FROMSCRATCH_INCLUDE_BASICLIGHT
#define FROMSCRATCH_INCLUDE_BASICLIGHT
#include "Vector3.h"
#include "Vector4.h"

namespace fs {
	namespace graphics {
		struct BasicLight {
			maths::Vector3 position;
			maths::Vector4 color;
		};
	}
}

#endif
