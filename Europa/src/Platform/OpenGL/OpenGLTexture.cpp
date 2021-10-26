#include "OpenGLTexture.h"
#include <glad/glad.h>
#include "stb_image.h"


namespace Eu {

	OpenGLTexture2D::OpenGLTexture2D(std::string path) : m_Path{path}
	{
		//load in texture
		int width, height, channels;
		stbi_uc* tex = stbi_load(path.c_str(), &width, &height, &channels, 0);
		EU_CORE_ASSERT(tex, "FAILED TO LOAD IMAGE");

		m_Width = width;
		m_Height = height;
		m_Channels = channels;

		if (channels == 4) {
			//create texture
			//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateTextures.xhtml
			glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
			//ask for storage on GPU(VRAM)
			//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexStorage2D.xhtml
			glTextureStorage2D(m_RenderID, 1, GL_RGBA8, m_Width, m_Height);

			//set some texture parameters
			//for example when texture does not fit exacltly(min or maxification)
			//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
			glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			//upload texture
			//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexSubImage2D.xhtml
			//second paramater is level index
			glTextureSubImage2D(m_RenderID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, tex);
		}
		else {
			EU_CORE_ASSERT(channels != 4, "NOT 4 CHANNELSE");

		}

	
		//free mempory on cpu
		stbi_image_free(tex);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RenderID);
	}

	void OpenGLTexture2D::Bind(uint32_t unitIndex) const
	{
		//opengl uses units so we can access multiple textures at once for more complex rendering tasks
		glBindTextureUnit(unitIndex, m_RenderID);
	}

}