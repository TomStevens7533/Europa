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




	OpenGLTextureArray::OpenGLTextureArray(const std::vector<std::string>& pathVec)
	{
		glGenTextures(1, &m_RenderID);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_RenderID);
		// Allocate the storage.
		int width, height, nrChannels;
#ifdef DEBUG
		int previousWidth{}, previousHeight{};

#endif // DEBUG


		std::vector<stbi_uc> pixelData{};
		EU_CORE_ASSERT(pathVec.size() > 0, "NO PATHS ADDED");
		for (size_t i = 0; i < pathVec.size(); i++)
		{
			stbi_uc* data; //Pixel data
			const char* texturePath = pathVec[i].c_str();
			//data is null bij leaves! wordt niet ingeladen.
			data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
			EU_CORE_ASSERT(data != NULL, "CANNOT LOAD IN TEXTURE");

			for (int channel = 0; channel < nrChannels; ++channel) {
				for (int y = 0; y < height; ++y) {
					for (int x = 0; x < width; ++x) {

						pixelData.push_back(data[x + (y * width) + (channel * width * height)]);


						//free


					}
				}
			}


#ifdef DEBUG
			if (previousWidth != 0) {
				EU_CORE_ASSERT(width != previousWidth, "TEXTURE ARRAY WIDTH NOT EQUAL");
				}
			if (previousHeight != 0) {
				EU_CORE_ASSERT(width != previousWidth, "TEXTURE ARRAY HEIGHT NOT EQUAL");
			}
			previousWidth = width;
			previousHeight = height;

#endif // DEBUG
			stbi_image_free(data);

		}
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, pathVec.size());


		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, pathVec.size(), GL_RGBA, GL_UNSIGNED_BYTE, pixelData.data());

		//glTexImage3D(GL_TEXTURE_2D_ARRAY,
		//	0,                 // mipmap level
		//	GL_RGBA8,          // gpu texel format
		//	width,             // width
		//	height,            // height
		//	1,					// depth
		//	0,                 // border
		//	GL_RGBA,		   // cpu pixel format
		//	GL_UNSIGNED_BYTE,  // cpu pixel coord type
		//	pixelData.data());             // pixel data

		// Set the preferences:
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	}

	OpenGLTextureArray::~OpenGLTextureArray()
	{

	}

	void OpenGLTextureArray::Bind(uint32_t unitIndex) const
	{
		glActiveTexture(GL_TEXTURE0 + unitIndex);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_RenderID);

	}

	void OpenGLTextureArray::SetData(void* data, uint32_t size)
	{

	}



}