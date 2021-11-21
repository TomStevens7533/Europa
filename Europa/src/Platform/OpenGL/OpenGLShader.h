#pragma once
#include "Europa/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Eu {

	class OpenGLVertexShader : public VertexShader
	{
	public:
		OpenGLVertexShader(const std::string& path);
		virtual ~OpenGLVertexShader();

		virtual void SetUniformMatrix4(const glm::mat4& mat4, const char* name, uint32_t renderID) override;
		virtual void SetUniformInt(const int index, const char* name, uint32_t renderID) override;



		virtual void SetUniformVec2(const glm::vec2 index, const char* name, uint32_t renderID)override;
	};

	class OpenGLIndexShader : public IndexShader
	{
	public:
		OpenGLIndexShader(const std::string& path);
		virtual ~OpenGLIndexShader();

		virtual void SetUniformMatrix4(const glm::mat4& mat4, const char* name, uint32_t renderID) override;
		virtual void SetUniformInt(const int index, const char* name, uint32_t renderID) override;
		virtual void SetUniformVec2(const glm::vec2 index, const char* name, uint32_t renderID)override;
	};
}