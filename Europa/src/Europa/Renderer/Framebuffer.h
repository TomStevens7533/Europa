#pragma once
#include <memory>

namespace Eu {

	struct FrameBufferSpecific {
		//specification for a Framebuffer
		uint32_t Width;
		uint32_t Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};


	class FrameBuffer
	{
	public:
		static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecific& fbSpec);

		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual inline uint32_t GetColorAttachment() const = 0;

		virtual FrameBufferSpecific& GetSpecification() = 0;
		
	};

}