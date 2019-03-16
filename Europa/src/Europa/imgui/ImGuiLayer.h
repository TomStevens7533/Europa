#pragma once

#include "Europa/Layer.h"
#include "Europa/Events/ApplicationEvent.h"
#include "Europa/Events/MouseEvent.h"
#include "Europa/Events/KeyEvent.h"

namespace Eu
{
	class EUROPA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void OnEvent(Event& event);
		void OnUpdate();
		void OnAttach();
		void OnDetach();

	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		float m_Time = 0.0f;
	};


}