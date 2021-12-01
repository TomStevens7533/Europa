#include "OpenGLTexture.h"
#include "stb_image.h"
#include <Platform/OpenGL/EuropaOpenGL.h>


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
			EU_CORE_TRACE("Creating 4 Channel Texture: \n From path: {0}", path);
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
			m_HasAlphaChannel = true;

		}
		else if (channels == 3)
		{
			EU_CORE_TRACE("Creating 3 Channel Texture: \n From path: {0}", path);
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}


		//create texture
		//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateTextures.xhtml
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
		glBindTexture(GL_TEXTURE_2D, m_RenderID);
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


		// Set the preferences:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


		
		

		
		//free mempory on cpu
		stbi_image_free(tex);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width{width}, m_Height{m_Width}
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
		//ask for storage on GPU(VRAM)
		//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexStorage2D.xhtml
		glTextureStorage2D(m_RenderID, 1, m_InternalFormat, m_Width, m_Height);

		//set some texture parameters
		//for example when texture does not fit exacltly(min or maxification)
		//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
		glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);




		// Set the preferences:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		//TODO SUPPORT TO CHANGE PART OF TEXTURE CHANGE SIZE TO VEC
		glTextureSubImage2D(m_RenderID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		//n specifies the number of textures to be deleted 
		glDeleteTextures(1, &m_RenderID);
	}

	void OpenGLTexture2D::Bind(uint32_t unitIndex) const
	{
		glActiveTexture(GL_TEXTURE0);

		//opengl uses units so we can access multiple textures at once for more complex rendering tasks
		glBindTexture(GL_TEXTURE_2D, m_RenderID);
	}



	//---------------------------------- 
	//CUBETETURE
	//----------------------------------
	OpenGLCubeTexture::OpenGLCubeTexture(std::string path) : m_Path{path}
	{	//info about opengl cube maps
		//https://learnopengl.com/Advanced-OpenGL/Cubemaps
		glGenTextures(1, &m_RenderID);					//We generate a texture
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RenderID);	//We bind that texture to the appropriate texture target GL_TEXTURE_CUBE_MAP in this case
		

		//Get All texture required for this cube texture
		std::vector<std::string> cubeTexturePathVec;				//openGL cube texture enum to determine faces
		cubeTexturePathVec.push_back(path + "_right.jpg");			//Layer number    Cube Map Face);
		cubeTexturePathVec.push_back(path + "_left.jpg");			//	0               GL_TEXTURE_CUBE_MAP_POSITIVE_X) RIGHT
		cubeTexturePathVec.push_back(path + "_top.jpg");			//	1               GL_TEXTURE_CUBE_MAP_NEGATIVE_X) LEFT
		cubeTexturePathVec.push_back(path + "_bottom.jpg");			//	2               GL_TEXTURE_CUBE_MAP_POSITIVE_Y) TOP	
		cubeTexturePathVec.push_back(path + "_front.jpg");			//	3               GL_TEXTURE_CUBE_MAP_NEGATIVE_Y) BOTTOM
		cubeTexturePathVec.push_back(path + "_back.jpg");			//	4               GL_TEXTURE_CUBE_MAP_POSITIVE_Z) BACK
																	//	5               GL_TEXTURE_CUBE_MAP_NEGATIVE_Z) FRONT



		int width, height, nrChannels;
		stbi_uc* data;
		for (unsigned int i = 0; i < cubeTexturePathVec.size(); i++)
		{

			data = stbi_load(cubeTexturePathVec[i].c_str(), &width, &height, &nrChannels, 0);
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);

		}
		m_Width = width;
		m_Height = height;
		m_Channels = nrChannels;

		//cubemap is like any other texture so we can specify it wrapping/filtering methods
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		//WE DONT NEED TEXTURE COORDINATES FOR A CUBETEXTURE THE TEXTURE COORDINATES ARE DIRECTION VECTOR FROM THE ORIGIN TO THE THAT POINT ON THE TEXTURE
		//SO WE CAN JUST SUPPLY POSITION VECTORS
	
	}

	OpenGLCubeTexture::~OpenGLCubeTexture()
	{
		glDeleteTextures(1, &m_RenderID);
	}

	void OpenGLCubeTexture::Bind(uint32_t unitIndex) const
	{
		glActiveTexture(GL_TEXTURE0);
		//opengl uses units so we can access multiple textures at once for more complex rendering tasks
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RenderID);
	}

	void OpenGLCubeTexture::SetData(void* data, uint32_t size)
	{
		//TODO SUPPORT TO CHANGE PART OF TEXTURE CHANGE SIZE TO VEC
		//glTextureSubImage2D(m_RenderID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

}