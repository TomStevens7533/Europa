#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Europa/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Europa/Material/InternalMaterial.h"

namespace Eu {
	class BaseTexture;
	class OpenGLMaterial final : public InternalMaterial
	{
	public:
		OpenGLMaterial();
		~OpenGLMaterial() override;
		void AttachVertexShader(const std::string& path);
		void AttachPixelShader(const std::string& path);
	


		void Bind()  override;
		void UnBind()  override;

		void SetUniformMatrix4(const glm::mat4& mat4, const char* name) override;
		void SetUniformInt(const int index, const char* name) const override;
		void SetUniformVec2(const glm::vec2 index, const char* name) const ;
		void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name) const override;
		void SetUniform(const char* name) const override;
		void SetUniformTexture(const Eu::BaseTexture* tex, const char* name, uint32_t unitIndex = 0) const override;






	private:
		void LinkProgram();
	private:
		uint32_t m_RenderID;
		std::vector<std::shared_ptr<BaseShader>> m_ShaderMap;
		bool m_IsBound{ false };
	};

}
