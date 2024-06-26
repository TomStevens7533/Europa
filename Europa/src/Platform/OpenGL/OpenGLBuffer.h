#pragma once
#include "Europa/Renderer/Buffer.h"



namespace Eu
{




	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size);
	
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }


		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		
	

	private:
		BufferLayout m_Layout;
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* Indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind()  const;
		virtual void Unbind() const; 

		virtual uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
		uint32_t* m_Indices;
	};
}
