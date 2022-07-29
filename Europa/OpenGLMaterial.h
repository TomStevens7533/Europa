#pragma once
#include "InternalMaterial.h"
#include <string>
#include <vector>
#include <memory>
#include "Europa/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Eu {
	class OpenGLMaterial : public InternalMaterial
	{
	public:
		void AttachVertexShader(const std::string& path);
		void AttachPixelShader(const std::string& path);
	


		void Bind() const override;
		void UnBind() const override;

		void SetUniformMatrix4(const glm::mat4& mat4, const char* name) ;
		void SetUniformInt(const int index, const char* name) const ;
		void SetUniformVec2(const glm::vec2 index, const char* name) const ;
		void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name) const;




	private:
		void LinkProgram();
	private:
		OpenGLIndexShader m_IndexShader;
		OpenGLVertexShader m_VertexShader;
		uint32_t m_RenderID;
		std::vector<std::shared_ptr<BaseShader>> m_ShaderMap;
	};

}
