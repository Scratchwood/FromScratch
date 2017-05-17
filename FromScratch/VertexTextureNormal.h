#ifndef FROMSCRATCH_INCLUDE_VERTEXTEXTURENORMAL
#define FROMSCRATCH_INCLUDE_VERTEXTEXTURENORMAL

#include "Vector3.h"
#include "Vector2.h"
namespace fs {
	namespace graphics {
		struct VertexTextureNormal {
			maths::Vector3 position;
			maths::Vector2 uv;
			maths::Vector3 normal;

			bool operator==(const VertexTextureNormal& other)
			{
				return this->position == other.position && this->uv == other.uv && this->normal == other.normal;
			}
		};
	}
}

#endif