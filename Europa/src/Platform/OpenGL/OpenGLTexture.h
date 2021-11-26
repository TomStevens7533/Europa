#pragma once
#include "Eupch.h"
#include <glm/glm.hpp>
#include "Europa/Texture.h"

namespace Eu {

	class OpenGLTexture2D final : public Texture2D
	{
	public:
		OpenGLTexture2D(std::string path);
		virtual ~OpenGLTexture2D();

		uint32_t GetWidth() const override { return m_Width; };
		uint32_t GetHeigh() const override { return m_Height; };
		void Bind(uint32_t unitIndex) const override;


	private:
		//opengl expects unsinged integers
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_Channels;

		bool m_HasAlphaChannel = false;

		uint32_t m_RenderID;

		//debug info
		std::string m_Path;
	};


	class OpenGLCubeTexture final : public CubeTexture
	{
	public:
		OpenGLCubeTexture(std::string path);
		virtual ~OpenGLCubeTexture();

		uint32_t GetWidth() const override { return m_Width; };
		uint32_t GetHeigh() const override { return m_Height; };
		void Bind(uint32_t unitIndex) const override;


		//opengl expects unsinged integers
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_Channels;

		uint32_t m_RenderID;

		//debug info
		std::string m_Path;
	};


}