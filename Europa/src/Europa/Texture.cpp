#include "Texture.h"
#include <memory>
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Eu {
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		EU_CORE_INFO("Creating Texture!");
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EU_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;

		case RendererAPI::API::OpenGL: EU_CORE_INFO("RendererAPI::OpenGL is active"); return  std::make_shared<OpenGLTexture2D>(path);

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}

