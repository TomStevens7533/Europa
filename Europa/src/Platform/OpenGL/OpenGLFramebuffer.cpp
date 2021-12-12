#include "OpenGLFramebuffer.h"
#include "glad/glad.h"
#include <Europa/Core.h>


namespace Eu {

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecific& spec)
		: m_FrameBufferSpecifics(spec)
	{
		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttached);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttached);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_FrameBufferSpecifics.Width, m_FrameBufferSpecifics.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttached, 0);

		//create depthbuffer image
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_FrameBufferSpecifics.Width, m_FrameBufferSpecifics.Height);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_FrameBufferSpecifics.Width, m_FrameBufferSpecifics.Height, 0, GL_DEPTH_STENCIL,
			GL_UNSIGNED_INT_24_8, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);


		//attach to framebuffer
		EU_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Frame buffer is not complete!");

		//unbind
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

	}

	void OpenGLFrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}


}