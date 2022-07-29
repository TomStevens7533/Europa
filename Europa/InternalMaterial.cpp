#include "InternalMaterial.h"
#include "Europa/Renderer/Renderer.h"
using namespace Eu;
InternalMaterial* InternalMaterial::GetInternalMaterial()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None:
		return nullptr;

	case RendererAPI::API::OpenGL:
		return nullptr;
	}
	EU_CORE_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

