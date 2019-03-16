#include <Europa.h>



class Sandbox : public Eu::Application
{
public:
	Sandbox()
	{
		PushOverlay(new Eu::ImGuiLayer);
		
	}
	~Sandbox()
	{
		
	}
		
};

Eu::Application* Eu::CreateApplication()
{
	return new Sandbox();
}