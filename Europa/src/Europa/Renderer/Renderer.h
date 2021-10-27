#pragma once
#include "Buffer.h"
#include "RenderCommand.h"

namespace Eu
{

	class Renderer
	{

	public: 
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

	public:
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	
		//void AppRunning();
	/*	void Initialize();*/
	private:
		
	};
}