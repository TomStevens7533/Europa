#include "Eupch.h"
#include "OpenGLContext.h"
#include "Europa/Log.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <Platform/OpenGL/EuropaOpenGL.h>

namespace Eu
{
	OpenGLRenderer::OpenGLRenderer(GLFWwindow* windowhandle)
		:m_WindowHandle(windowhandle)
	{
		EU_CORE_ASSERT(windowhandle, "Graphics Context is null")

	}

	void OpenGLRenderer::Init()
	{

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EU_CORE_ASSERT(status, "Failed to initialize!");

		EU_CORE_INFO("OpenGL Renderer: {0} {1} {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

	}

	void OpenGLRenderer::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}