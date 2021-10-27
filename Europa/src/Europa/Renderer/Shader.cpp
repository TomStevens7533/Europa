#include "Renderer.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <fstream>
#include <iostream>


namespace Eu
{
	BaseShader::BaseShader(std::string path)
	{
		//Read in data
		ParseFile(path);
	}
	void BaseShader::ParseFile(std::string& path)
	{
		std::ifstream fileStream(path, std::ios::in);

		if (!fileStream.is_open()) {
			EU_CORE_ERROR("Cannot open shader file!");
			return;
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			m_Data.append(line + "\n");
		}
	}
	IndexShader* IndexShader::Create(const std::string& path)
	{ 
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EU_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;

		case RendererAPI::API::OpenGL:  return new OpenGLIndexShader(path);

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

	}



	VertexShader* VertexShader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EU_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;

		case RendererAPI::API::OpenGL: return new OpenGLVertexShader(path);

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}