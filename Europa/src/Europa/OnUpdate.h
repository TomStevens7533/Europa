#pragma once

#include "Europa/Events/ApplicationEvent.h"
#include "Europa/Events/MouseEvent.h"
#include "Europa/Events/KeyEvent.h"

namespace Eu {

	class EUROPA_API Update
	{
	public:
		Update();
		~Update();

		static void OnUpdateEvent();
	protected:
	};

}