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


		virtual void Resize(uint32_t width, uint32_t height) override;

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttached = 0, m_DepthAttachment = 0;
		FrameBufferSpecific m_FrameBufferSpecifics;
	};

}