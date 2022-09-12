#include "Europa/Layer.h"
#include "Europa/Profiling/TimerManager.h"
#include "Europa/Scenegraph.h"

class ChunkComponent;


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
		Eu::ScenGraph m_LayerSceneGraph;
		std::shared_ptr<Eu::PerspectiveCameraControllerComponent> m_pCamera;
		std::shared_ptr<ChunkComponent> m_ChunkComp;
		Eu::TimerManager m_TimerManager;


		std::shared_ptr<Eu::BaseTexture>* m_ptexture;
		std::shared_ptr<Eu::BaseTexture>* m_pCrosshairTexture;

		std::shared_ptr<Eu::GameObject> m_pPlayer;
		std::shared_ptr<Eu::GameObject> m_pChunk;
		float angle{ 0 };


		glm::vec2 m_ViewportSize;
	};


}
