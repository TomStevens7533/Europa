#include <Europa.h>
#include "Europa/EntryPoint.h"


#include "BlockJsonParser.h"
#include "EditorLayer.h"


namespace Eu {
	class EuropaEditor : public Application
	{
	public:
		EuropaEditor(WindowProps& pr) : Application(pr)
		{
			BlockJsonParser::GetInstance();
			PushLayer(new EuropaEditorLayer);


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

