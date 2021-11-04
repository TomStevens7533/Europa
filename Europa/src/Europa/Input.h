#pragma once

#include "Core.h"
#include "Eupch.h"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp> // glm::vec3

namespace Eu {

	class  Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static glm::vec2 GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static glm::vec2 GetMouseDrag(int button) { return s_Instance->GetDragDifference(button); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual glm::vec2 GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual glm::vec2 GetDragDifference(int button) = 0;
	private:
		static std::shared_ptr<Input> s_Instance;
	};

}