#pragma once
#include "Europa/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Eu
{


	class OpenGLRenderer : public GraphicsContext
	{
	public:
		OpenGLRenderer(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffer() override;

	private:

		GLFWwindow* m_WindowHandle;
	};

}