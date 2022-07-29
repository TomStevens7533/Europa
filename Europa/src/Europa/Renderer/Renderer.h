#pragma once
#include "Buffer.h"
#include "RenderCommand.h"
#include "Program.h"
#include <glm/glm.hpp>
#include "Europa/Camera/Camera.h"

namespace Eu
{
	class BaseMaterial;
	class Renderer
	{

	public: 
		static void Init();
		static void ShutDown();

		static void BeginScene(const Camera& sceneCamera);
		static void EndScene();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void EnableWireFrame();
		static void DisableWireFrame();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<BaseMaterial> program, const glm::mat4& transform = glm::mat4(1.0f));
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

		static const Camera* m_SceneData;
		static  bool m_IsFirstFrame;
	};
}