#pragma once
#include "Eupch.h"
#include <glm/glm.hpp>
#include "Core.h"

namespace Eu {
	enum class TextureTypes
	{
		TEXTURE2D,
		CUBETEXTURE,
		TEXTUREARRAY
	};

	class BaseTexture {
	public:
		virtual ~BaseTexture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeigh() const = 0;

		virtual void Bind(uint32_t unitIndex = 0) const = 0;


		virtual void SetData(void* data, uint32_t size) = 0; //upload given pointer to gpu

	private:
	};

	class Texture2D : public BaseTexture {
	public:
		static std::shared_ptr<Texture2D> Create(const std::string& path);
		static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height);


		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeigh() const = 0;

		virtual void Bind(uint32_t unitIndex = 0) const = 0;
		virtual void SetData(void* data, uint32_t size) = 0; //upload given pointer to gpu

	};

	class CubeTexture : public BaseTexture {
	public:
		static std::shared_ptr<CubeTexture> Create(const std::string& path);

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeigh() const = 0;

		virtual void Bind(uint32_t unitIndex = 0) const = 0;
		virtual void SetData(void* data, uint32_t size) = 0; //upload given pointer to gpu

	};
	class TextureArray : public BaseTexture {
	public:
		static std::shared_ptr<TextureArray> Create(const std::vector<std::string>& pathVec);

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeigh() const = 0;


		virtual void Bind(uint32_t unitIndex = 0) const = 0;
		virtual void SetData(void* data, uint32_t size) = 0; //upload given pointer to gpu

	};
}
