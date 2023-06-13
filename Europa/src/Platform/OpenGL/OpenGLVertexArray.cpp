#include "OpenGLVertexArray.h"
#include "Eupch.h"
#include "Europa/Renderer/Shader.h"
#include <Platform\OpenGL\OpenGLBuffer.h>
#include "EuropaOpenGL.h"


namespace Eu
{
	


	OpenGLVertexArray::OpenGLVertexArray()
	{

		glCreateVertexArrays(1, &m_RendererID);

	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{

		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer)
	{
		EU_CORE_ASSERT(VertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
#ifdef _DEBUG
		glCheckError();
#endif // 
		uint32_t index = 0;
		for (const auto& element : VertexBuffer->GetLayout())
		{
			if (!element.m_IsInt)
			{
				//(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					VertexBuffer->GetLayout().GetStride(),
					(const void*)element.Offset);
			}
			else {
				//(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
				glEnableVertexAttribArray(index);
				glVertexAttribIPointer(index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					VertexBuffer->GetLayout().GetStride(),
					(const void*)element.Offset);
			}
			index++;
		}

		m_VertexBuffers.push_back(VertexBuffer);
		m_VertexBuffers.back()->Bind();
#ifdef _DEBUG
		glCheckError();
#endif // 
	}
	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) 
	{

		glBindVertexArray(m_RendererID);

		m_IndexBuffers = IndexBuffer;
		m_IndexBuffers->Bind();
	}
}

//remoev bindigs