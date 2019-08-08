#include "OpenGLVertexArray.h"
#include "glad/glad.h"
#include "Eupch.h"
#include "Europa/Renderer/Shader.h"
#include <Platform\OpenGL\OpenGLBuffer.h>

namespace Eu
{
	GLenum ShaderDataTypeToBaseOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case Eu::ShaderDataType::Float:		 return GL_FLOAT;
		case Eu::ShaderDataType::Float2:	 return GL_FLOAT;
		case Eu::ShaderDataType::Float3:	 return GL_FLOAT;
		case Eu::ShaderDataType::Float4:	 return GL_FLOAT;
		case Eu::ShaderDataType::Mat3:		 return GL_FLOAT;
		case Eu::ShaderDataType::Mat4:		 return GL_FLOAT;
		case Eu::ShaderDataType::Int:		 return GL_INT;
		case Eu::ShaderDataType::Int2:		 return GL_INT;
		case Eu::ShaderDataType::Int3:		 return GL_INT;
		case Eu::ShaderDataType::Int4:		 return GL_INT;
		case Eu::ShaderDataType::Bool:		 return GL_BOOL;
		}
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
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
		glBindVertexArray(m_RendererID);
		VertexBuffer->Bind();

		uint32_t index = 0;
		for (const auto& element : VertexBuffer->GetLayout())
		{

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToBaseOpenGLType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				VertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(VertexBuffer);
	}
	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) 
	{

		glBindVertexArray(m_RendererID);
		IndexBuffer->Bind();
		m_IndexBuffers = IndexBuffer;
	}
}