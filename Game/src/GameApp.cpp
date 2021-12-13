#include <Europa.h>
#include "Europa/EntryPoint.h"





class Sandbox : public Eu::Application
{
public:
	Sandbox(Eu::WindowProps& pr) : Eu::Application()
	{

		//PushLayer(new MineCraftLayer);


	}
	~Sandbox()
	{
		
	}

		
};

Eu::Application* Eu::CreateApplication()
{
	Eu::WindowProps pr;
	pr.Title = "Test Enviroment";
	return new Sandbox();
}