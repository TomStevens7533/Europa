#include <Europa.h>



class Sandbox : public Eu::Application
{
public:
	Sandbox()
	{
		
		
	}
	~Sandbox()
	{
		
	}
		
};

Eu::Application* Eu::CreateApplication()
{
	return new Sandbox();
}