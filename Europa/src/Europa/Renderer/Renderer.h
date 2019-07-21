#pragma once
#include "Buffer.h"
#include "Shader.h"
#include <memory>
namespace Eu
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1

	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
		static RendererAPI s_RendererAPI;
	
		//void AppRunning();
	/*	void Initialize();*/
	private:
		
	};
}