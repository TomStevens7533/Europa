#include "Texture.h"
#include <memory>
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Eu {
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		EU_CORE_INFO("Creating 2D Texture from path: " + path);
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			EU_CORE_ASSERT(false, "RendererAPI::None is not supported"); 
			return nullptr;
			break;

		case RendererAPI::API::OpenGL: 
			return  std::make_shared<OpenGLTexture2D>(path);
			break;

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		EU_CORE_INFO("Creating 2D Texture with size: {0}, {1} ", width, height);
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			EU_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
			break;

		case RendererAPI::API::OpenGL:
			return  std::make_shared<OpenGLTexture2D>(width, height);
			break;

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	std::shared_ptr<CubeTexture> CubeTexture::Create(const std::string& path)
	{
		try
		{
			EU_CORE_INFO("Creating CubeTexture Texture from path: " + path);
			switch (Renderer::GetAPI())
			{
			case RendererAPI::API::None:
				EU_CORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
				break;

			case RendererAPI::API::OpenGL:
				EU_CORE_INFO("RendererAPI::OpenGL is active");
				return  std::make_shared<OpenGLCubeTexture>(path);
				break;

			}
			EU_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
		catch (...)
		{
			EU_CORE_ERROR("CUBE TEXTURE FROM PATH: {0}  CANNOT BE LOADED!!", path);
		}

		
	}

	std::shared_ptr<Eu::TextureArray> TextureArray::Create(const std::vector<std::string>& pathVec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			EU_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
			break;

		case RendererAPI::API::OpenGL:
			return  std::make_shared<OpenGLTextureArray>(pathVec);
			break;

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}

