#pragma once
namespace Eu
{
	struct GraphicsContext
	{
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;

	};
}