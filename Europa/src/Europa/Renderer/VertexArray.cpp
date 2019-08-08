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
		case RendererAPI::None: EU_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;

		case RendererAPI::OpenGL: EU_CORE_INFO("RendererAPI::OpenGL is active"); return new OpenGLVertexArray();

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}