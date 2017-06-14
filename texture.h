#pragma once

#include <string>
#include <GL/glew.h>
class Texture
{
	public:
		Texture(const std::string& fileName);
		void Bind(unsigned int unit);	// uint is how many textures you want to bind
		virtual ~Texture();
	protected:

	private:
		Texture(const Texture& other);
		void operator=(const Texture& other);

		GLuint m_texture;	// texture ID
};

