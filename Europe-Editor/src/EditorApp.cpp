#include <Europa.h>
#include "Europa/EntryPoint.h"

#include "VLD/include/vld.h"
//#include "EditorLayer.h"

namespace Eu {
	class EuropaEditor : public Application
	{
	public:
		EuropaEditor(WindowProps& pr) : Application(pr)
		{

			//PushLayer(new EuropaEditorLayer);


		}
		~EuropaEditor()
		{

		}


	};

	Application* CreateApplication()
	{

		Eu::WindowProps pr;
		pr.Title = "Europa Editor";
		return new EuropaEditor(pr);
	}
}

