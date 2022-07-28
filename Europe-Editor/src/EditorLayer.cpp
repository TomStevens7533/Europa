#include <Europa.h>

#include "VLD/include/vld.h"
#include "Europa/ResourceManager.h"
#include "Europa/Utils.h"
#include "EditorLayer.h"



namespace Eu {
	EuropaEditorLayer::EuropaEditorLayer()
	{
		m_ChunkManager = new ChunkManager(m_Camera);

		m_ptexture = &Eu::ResourceManager::GetInstance()->GetTexture("Resources/minecraft/TextureAtlas.png", Eu::TextureTypes::TEXTURE2D);
		m_pCrosshairTexture = &Eu::ResourceManager::GetInstance()->GetTexture("Resources/minecraft/Crosshair.png", Eu::TextureTypes::TEXTURE2D);


	}

	void EuropaEditorLayer::OnAttach()
	{
		FrameBufferSpecific fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_pFramebuffer = FrameBuffer::Create(fbSpec);
	}

	void EuropaEditorLayer::OnDetach()
	{
		delete m_ChunkManager;
	}

	void EuropaEditorLayer::OnUpdate(TimeStep deltaTime)
	{
		m_pFramebuffer->Bind();

		auto updateTimer = m_TimerManager.AddTimer("Entire OnUpdate");
		m_Camera.OnUpdate(deltaTime);
		m_ChunkManager->Update(deltaTime, m_Camera);


		auto NrmlRendertimer = m_TimerManager.AddTimer("3D Render");

		RenderCommand::SetClearColor({ 0.f, 0.3f, 0.8f, 1.f });
		RenderCommand::Clear();


		Renderer::BeginScene(m_Camera.GetCamera());
		(*m_ptexture)->Bind();

		//m_Chunk->Render();
		m_ChunkManager->Render();
		//m_pScene->RenderScene();
		Eu::Renderer::EndScene();
		m_TimerManager.StopTimer(NrmlRendertimer);


		auto UIRendertimer = m_TimerManager.AddTimer("UIRENDER");


		Renderer2D::BeginUIScene(m_Camera.GetCamera());
		Renderer2D::DrawQuad({ 0.f, 0.f, 0.f }, { 0.2f, 0.2f }, *m_pCrosshairTexture, { 0.8f, 0.f, 0.2f, 1.f });
		Renderer2D::EndUIScene();

		m_TimerManager.StopAllTimers();
		m_pFramebuffer->UnBind();
	}

	void EuropaEditorLayer::OnEvent(Event& event)
	{
		if (event.GetEventType() == Eu::EventType::MouseButtonPressed) {
			Eu::MouseButtonPressedEvent* mouseEvent = dynamic_cast<Eu::MouseButtonPressedEvent*>(&event);
			if (mouseEvent->GetMouseButton() == EU_MOUSE_BUTTON_1) {
				EU_CORE_INFO("Mouse down");
				glm::vec3 cameraPos = m_Camera.GetCamerPos();


				for (Eu::Ray lookRay(cameraPos, m_Camera.GetForwardVector(), 10.f); lookRay.GetCurrentPercent() <= 0.75f; lookRay.Step(0.025f))
				{
					if (m_ChunkManager->DeleteBlockAtPos(lookRay.GetCurrentPos()))
						break;
				}
			}
			else if (mouseEvent->GetMouseButton() == EU_MOUSE_BUTTON_2) {
				for (Eu::Ray lookRay(m_Camera.GetCamerPos(), m_Camera.GetForwardVector(), 10.f); lookRay.GetCurrentPercent() >= -1.f; lookRay.StepBack(-0.025f))
				{
					if (m_ChunkManager->AddBlockAtPos(lookRay.GetCurrentPos(), BlockTypes::DIRT))
						break;
				}
			}
		}
		m_Camera.OneEvent(event);
	}

	void EuropaEditorLayer::OnImGuiRender()
	{
		static bool dock_space_open = true;
		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dock_space_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Docking"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit"))
					Eu::Application::Get().Close();

				ImGui::EndMenu();
			}
			ImGui::ShowDemoWindow();

			ImGui::Begin("Profiling");

			for (auto trResult : m_TimerManager.GetTimerResults())
			{
				char label[50];
				strcpy(label, " %.3fms  ");
				strcat(label, trResult.Name);

				ImGui::Text(label, trResult.Time);
			}



			m_TimerManager.ClearTimerResults();

			//viewport
			ImGui::End();


			ImGui::EndMenuBar();
		}

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("ViewPort");
		ImVec2 viewPortSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *(glm::vec2*)&viewPortSize) {
			m_ViewportSize = { viewPortSize.x, viewPortSize.y }; //assign new viewport size;
			m_pFramebuffer->Resize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y)); //resize framebuffer
		}
		EU_CORE_WARN("Viewport Size: {0}, {1}", viewPortSize.x, viewPortSize.y);
		uint32_t textureID = m_pFramebuffer->GetColorAttachment();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x,m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
		ImGui::End();
		ImGui::PopStyleVar();

	}

}

