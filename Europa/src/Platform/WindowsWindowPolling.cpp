#include "WindowWindowPolling.h"
#include "Europa/KeyMouseCodes.h"
#include "Europa/Application.h"

namespace Eu
{

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetPureWindow());
		auto state = glfwGetKey(window, keycode);
	
		return state == EU_PRESS || state == EU_REPEAT;
	}
	glm::vec2 WindowsInput::GetDragDifference(int button) {

		if (IsMouseButtonPressedImpl(button) && m_PreviousMousePosDrag != glm::vec2{0,0}) {

			auto currentPair = GetMousePositionImpl();
			glm::vec2 dragDifference = m_PreviousMousePosDrag - currentPair;
			m_PreviousMousePosDrag = currentPair;//Set previous mouse pos

			return dragDifference;
		}
		auto currentPair = GetMousePositionImpl();
		m_PreviousMousePosDrag = currentPair;//Set previous mouse pos
		return { 0,0 };
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetPureWindow());
		auto state = glfwGetMouseButton(window, button);
		if (state == 1)
		{
			EU_CLIENT_ERROR("pressed");
		}

		return state == EU_PRESS;
	}

	glm::vec2 WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetPureWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		
		return GetMousePositionImpl().x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		
		return GetMousePositionImpl().y;
	}
}

