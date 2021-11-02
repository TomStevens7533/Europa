#include "OpenGLRendererAPI.h"
#include <glad/glad.h>
#include <Platform/OpenGL/EuropaOpenGL.h>

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
		glCheckError();
		glDrawElements(GL_TRIANGLES, VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawIndexedNoDepth(const std::shared_ptr<VertexArray>& VertexArray)
	{
		glCheckError();
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


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	}

}

