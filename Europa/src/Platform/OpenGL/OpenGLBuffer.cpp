#include "OpenGLBuffer.h"
#include "Eupch.h"
#include <glad/glad.h>
namespace Eu
{

	//ARRAYBUFFER
	OpenGLVertexBuffer::OpenGLVertexBuffer(Vertex_Input* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);			//generate buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);//bind buffer with type GL_ARRAY_BUFFER
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //put data on buffer we send vertices //static_draw we dont really want to change this data(necessary so opengl can know where to put the data(limited speed))
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//INDEXBUFFER
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* Indices, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, Indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}