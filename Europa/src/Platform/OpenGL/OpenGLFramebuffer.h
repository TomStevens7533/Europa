#pragma once
#include "Europa/Renderer/Framebuffer.h"

namespace Eu {

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecific& spec);
		virtual ~OpenGLFrameBuffer();
		void Invalidate();

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual inline uint32_t GetColorAttachment() const override { return m_ColorAttached; }
		virtual inline uint32_t GetDepthAttachment() const override { return m_DepthAttachment; }


		virtual inline FrameBufferSpecific& GetSpecification() override { return m_FrameBufferSpecifics; }

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttached, m_DepthAttachment;
		FrameBufferSpecific m_FrameBufferSpecifics;
	};

}