#ifndef FROMSCRATCH_INCLUDE_TEXTUREDMODEL
#define FROMSCRATCH_INCLUDE_TEXTUREDMODEL
#include "Mesh.h"
#include "Texture.h"
#include <memory>
#define ModelPtr	std::shared_ptr<graphics::Model>
namespace fs {
	namespace graphics {
		class Model {
		private:
			MeshPtr m_Mesh;
			TexturePtr m_Texture;
			unsigned int m_Id;
		public:
			Model();
			Model(TexturePtr tex, MeshPtr model, unsigned int id);

			inline const MeshPtr getMesh() const { return m_Mesh; }
			inline const TexturePtr getTexture() const { return m_Texture; }
			inline const unsigned int getId() const { return m_Id; };
			bool operator==(const Model& that);
		};
	}
}



#endif
