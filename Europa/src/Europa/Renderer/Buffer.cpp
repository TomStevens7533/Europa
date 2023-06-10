#include "Buffer.h"


#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Eu
{
	VertexBuffer* VertexBuffer::Create(void* vertices, uint32_t size)
	{	//MULTIPLE VERTICES INFORMATION
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			EU_CORE_ASSERT(false, "RendererAPI::None is not supported"); 
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}



	IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t count)
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			EU_CORE_ASSERT(false, "RendererAPI::None is not supported"); 
			return nullptr;

		case RendererAPI::API::OpenGL: 
			return new OpenGLIndexBuffer(Indices, count);

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	

}
