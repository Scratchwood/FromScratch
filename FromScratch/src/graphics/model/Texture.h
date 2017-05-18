#ifndef FROMSCRATCH_INCLUDE_TEXTURE
#define FROMSCRATCH_INCLUDE_TEXTURE
#define TexturePtr	std::shared_ptr<graphics::Texture>
namespace fs {
	namespace graphics {
		class Texture {
		private:
			unsigned int m_TextureId;
			float m_Reflectivity, m_ShineDamper, m_Rows;
			int m_Width, m_Height;
		public:
			Texture(unsigned int id, int width, int height, int rows, float reflectivity, float shineDamp);
			void enable() const;
			void disable() const;

			inline const int getWidth() const { return m_Width; }
			inline const int getHeight() const { return m_Height; }
			inline const unsigned int getId() const { return m_TextureId; };
			inline const float getReflectivity() const { return m_Reflectivity; }
			inline const float getShineDamper() const { return m_ShineDamper; }
			inline const float getRows() const { return m_Rows; };
			
		};
	}
}


#endif