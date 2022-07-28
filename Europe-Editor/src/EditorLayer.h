#include "Europa/Layer.h"
#include "Europa/Profiling/TimerManager.h"
#include "Minecraft/Chunkmanager.h"


namespace Eu {
	class EuropaEditorLayer : public Layer
	{
	public:
		EuropaEditorLayer();
		virtual ~EuropaEditorLayer() {};


		void OnAttach() override;


		void OnDetach() override;


		void OnUpdate(TimeStep deltaTime) override;


		void OnEvent(Event& event) override;


		void OnImGuiRender() override;

	private:
		std::shared_ptr<Eu::FrameBuffer> m_pFramebuffer;

		ChunkManager* m_ChunkManager;
		Eu::TimerManager m_TimerManager;


		std::shared_ptr<Eu::BaseTexture>* m_ptexture;
		std::shared_ptr<Eu::BaseTexture>* m_pCrosshairTexture;

		Eu::PerspectiveCameraController m_Camera;

		glm::vec2 m_ViewportSize;
	};


}
