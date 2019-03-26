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



		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;


		void Begin();
		void End();

	private:
		
		
		float m_Time = 0.0f;
	};


}