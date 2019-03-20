#include "WindowWindowPolling.h"
#include "Europa/KeyMouseCodes.h"
#include "Europa/Application.h"
#include <GLFW/glfw3.h>

namespace Eu
{

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetPureWindow());
		auto state = glfwGetKey(window, keycode);
	
		return state == EU_PRESS || state == EU_REPEAT;
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

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetPureWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return y;
	}
}

