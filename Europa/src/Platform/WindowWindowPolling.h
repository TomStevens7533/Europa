#pragma once
#include "Europa/Input.h"

namespace Eu
{
	class WindowsInput : public Input
	{
	private:
		glm::vec2 m_PreviousMousePosDrag;

	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual glm::vec2 GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual glm::vec2 GetDragDifference(int button) override;
	};
}
