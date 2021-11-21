#pragma once
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Eupch.h"

namespace Eu
{
	VertexArray* VertexArray::Create()
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: 
			return nullptr;

		case RendererAPI::API::OpenGL: 
			return new OpenGLVertexArray();

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}