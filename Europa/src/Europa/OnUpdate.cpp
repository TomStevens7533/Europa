//#pragma once
//#include "OnUpdate.h"
//#include "imgui/ImGuiBuild.cpp"
//#include "imgui.h"
//#include "Application.h"
//#include "Europa/imgui/ImGuiLayer.h"
//
//namespace Eu
//{
//	float m_Time = 0.0f;
//
//	Update::Update()
//	{
//	}
//	Update::~Update()
//	{
//	}
//
//	void Update::OnUpdateEvent()
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		Application& app = Application::Get();
//
//
//		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
//
//
//
//		float time = (float)glfwGetTime();
//		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
//		m_Time = time;
//
//		ImGui_ImplOpenGL3_NewFrame();
//		ImGui::NewFrame();
//
//		static bool show = true;
//		ImGui::ShowDemoWindow(&show);
//
//
//
//		ImGui::Render();
//		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//	}
//
//}