#include "Framebuffer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Renderer.h"

namespace Eu {

	std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecific& fbSpec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			return nullptr;

		case RendererAPI::API::OpenGL: 
			return std::make_shared<OpenGLFrameBuffer>(fbSpec);

		}
		return nullptr;
	}

}