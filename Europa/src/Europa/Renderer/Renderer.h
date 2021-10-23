#pragma once
#include "Buffer.h"
#include "Shader.h"
#include "RendererAPI.h"
namespace Eu
{

	class Renderer
	{

	public: 
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<int>& vertexArray);

	public:
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	
		//void AppRunning();
	/*	void Initialize();*/
	private:
		
	};
}