#pragma once
#include "Eupch.h"
#include <glm/glm.hpp>
#include "Core.h"

namespace Eu {
	enum class TextureTypes
	{
		TEXTURE2D,
		CUBETEXTURE
	};

	class BaseTexture {
	public:
		virtual ~BaseTexture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeigh() const = 0;

		virtual void Bind(uint32_t unitIndex = 0) const = 0;
		//Elite::RGBColor Sample(const Elite::FVector2& uv, uint8_t& transparancy) const;

	private:
		//SDL_Surface* m_pSDLsurface;
	};

	class Texture2D : public BaseTexture {
	public:
		static std::shared_ptr<Texture2D> Create(const std::string& path);
	};

	class CubeTexture : public BaseTexture {
	public:
		static std::shared_ptr<CubeTexture> Create(const std::string& path);
	};
}
