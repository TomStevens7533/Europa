#pragma once
#include "Buffer.h"
#include "RenderCommand.h"
#include "Program.h"
#include <glm/glm.hpp>
#include "Europa/Camera.h"

namespace Eu
{

	class Renderer
	{

	public: 
		static void BeginScene(Camera& sceneCamera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<BaseProgram>& program, const glm::mat4& transform = glm::mat4(1.0f));
		static void SubmitNoDepth(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<BaseProgram>& program, const glm::mat4& transform = glm::mat4(1.0f), bool isBackground = false);
	public:
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	
		//void AppRunning();
	/*	void Initialize();*/
	private:
		struct SceneData
		{
			//deprecated but will reimplement later for more advandec features
			glm::mat4 ViewProjectionMatrix;
		};

		static Camera* m_SceneData;
	};
}