//#include "OnEventDo.h"
//#include "glad/glad.h"
//#include "KeyMouseCodes.h"
//#include "imgui.h"
//
//
//
//namespace Eu
//{
//
//	Input::~Input()
//	{
//		EventDispatcher Dispatcher(m_Event);
//
//		Dispatcher.Dispatch<MouseButtonPressedEvent>(EU_BIND_EVENT_FN(Input::OnMouseButtonPressed));
//		Dispatcher.Dispatch<MouseButtonReleasedEvent>(EU_BIND_EVENT_FN(Input::OnMouseButtonReleased));
//		Dispatcher.Dispatch<KeyPressedEvent>(EU_BIND_EVENT_FN(Input::OnKeyButtonPressed));
//		Dispatcher.Dispatch<KeyReleasedEvent>(EU_BIND_EVENT_FN(Input::OnKeyButtonReleased));
//		Dispatcher.Dispatch<MouseScrolledEvent>(EU_BIND_EVENT_FN(Input::OnMouseScroll));
//		Dispatcher.Dispatch<MouseMovedEvent>(EU_BIND_EVENT_FN(Input::OnMouseMoveEvent));
//		Dispatcher.Dispatch<WindowResizeEvent>(EU_BIND_EVENT_FN(Input::OnWindowResizeEvent));
//		Dispatcher.Dispatch<KeyTypedEvent>(EU_BIND_EVENT_FN(Input::OnKeyTypedEvent));
//	}
//	
//
//	bool Input::OnMouseButtonPressed(MouseButtonPressedEvent& e)
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.MouseDown[e.GetMouseButton()] = true;
//
//		return false;
//	}
//	bool Input::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.MouseDown[e.GetMouseButton()] = false;
//
//		return false;
//	}
//
//	bool Input::OnKeyButtonPressed(KeyPressedEvent& e)
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.KeysDown[e.GetKeyCode()] = true;
//
//		io.KeyCtrl = io.KeysDown[EU_KEY_LEFT_CONTROL] || io.KeysDown[EU_KEY_RIGHT_CONTROL];
//		io.KeyAlt = io.KeysDown[EU_KEY_LEFT_ALT] || io.KeysDown[EU_KEY_RIGHT_ALT];
//		io.KeyShift = io.KeysDown[EU_KEY_LEFT_SHIFT] || io.KeysDown[EU_KEY_RIGHT_SHIFT];
//		io.KeySuper = io.KeysDown[EU_KEY_LEFT_SUPER] || io.KeysDown[EU_KEY_RIGHT_SUPER];
//
//		return false;
//
//	}
//	bool Input::OnKeyButtonReleased(KeyReleasedEvent& e)
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.KeysDown[e.GetKeyCode()] = false;
//
//		return false;
//	}
//	
//	bool Input::OnMouseScroll(MouseScrolledEvent& e)
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.MouseWheel += e.GetYOffset();
//		io.MouseWheelH += e.GetXOffset();
//	
//
//		return false;
//	}
//	bool Input::OnMouseMoveEvent(MouseMovedEvent & e)
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.MousePos = ImVec2(e.GetX(), e.GetY());
//		return false;
//	}
//	
//	bool Input::OnWindowResizeEvent(WindowResizeEvent & e)
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
//		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
//		glViewport(0, 0, e.GetWidth(), e.GetHeight());
//		return false;
//	}
//	bool Input::OnKeyTypedEvent(KeyTypedEvent & e)
//	{
//		ImGuiIO& io = ImGui::GetIO();
//		int keycode = e.GetKeyCode();
//		if (keycode > 0 && keycode < 0x10000)
//			io.AddInputCharacter((unsigned int short)keycode);
//
//		
//		return false;
//
//	}
//}