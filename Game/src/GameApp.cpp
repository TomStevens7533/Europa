#include <Europa.h>
#include "Europa/EntryPoint.h"
#include "TestLayer.h"


class Sandbox : public Eu::Application
{
public:
	Sandbox(Eu::WindowProps& pr) : Eu::Application(pr)
	{

		PushLayer(new TestLayer());


	}
	~Sandbox()
	{
		
	}

		
};

Eu::Application* Eu::CreateApplication()
{
	Eu::WindowProps pr;
	pr.Title = "Test Enviroment";
	return new Sandbox(pr);
}