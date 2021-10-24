#include "Buffer.h"


#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Eu
{
	VertexBuffer* VertexBuffer::Create(Vertex_Input* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EU_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;

		case RendererAPI::API::OpenGL: EU_CORE_INFO("RendererAPI::OpenGL is active"); return new OpenGLVertexBuffer(vertices, size * sizeof(Vertex_Input));

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t count)
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EU_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;

		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(Indices, count * sizeof(uint32_t));

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	

}
