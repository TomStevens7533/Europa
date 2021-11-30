#include "OpenGLRendererAPI.h"
#include <glad/glad.h>
#include <Platform/OpenGL/EuropaOpenGL.h>
#include "Europa/Input.h"
#include "Europa/KeyMouseCodes.h"

//raw openGl calls

namespace Eu {
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glClear.xhtml
		//indicates which buffers need to be cleared 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& VertexArray)
	{
		glDrawElements(GL_TRIANGLES, VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawIndexedNoDepth(const std::shared_ptr<VertexArray>& VertexArray)
	{
		glDepthFunc(GL_LEQUAL); //Change depth function so depth test passen when values are equal or less to depth buffers content
		glDrawElements(GL_TRIANGLES, VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glDepthFunc(GL_LESS);

	}

	void OpenGLRendererAPI::EnableDepthTest()
	{
		//openGl depth buffer explained 
		// https://www.youtube.com/watch?v=uJzXDkgm5Fw
		//https://www.youtube.com/watch?v=U9-J8M-oslA


		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
	}

	void OpenGLRendererAPI::EnableWireFrame()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	}

	void OpenGLRendererAPI::DisableWireFrame()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

	void OpenGLRendererAPI::SetBlending()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

	void OpenGLRendererAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t heigth)
	{	
		glViewport(x, y, width, heigth);
	}

}

