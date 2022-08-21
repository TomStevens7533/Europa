#include "InternalMaterial.h"
#include "Europa/Renderer/Renderer.h"
#include "Platform/OpenGL/Material/OpenGLMaterial.h"
using namespace Eu;
std::unique_ptr<InternalMaterial> InternalMaterial::GetInternalMaterial()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None:
		return nullptr;

	case RendererAPI::API::OpenGL:
		return std::make_unique<OpenGLMaterial>();
	}
	EU_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

