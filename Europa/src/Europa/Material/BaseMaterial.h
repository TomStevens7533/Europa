#pragma once
#include <string>
#include <memory>
#include "InternalMaterial.h"
namespace Eu {
	class BaseTexture;
	class BaseMaterial {
	public:
		BaseMaterial(std::string vertexShader, std::string PixelShader = 0);
		~BaseMaterial();
		virtual void UpdateMaterialVariables() = 0;

		 void SetUniformMatrix4(const glm::mat4& mat4, const char* name) ;
		 void SetUniformInt(const int index, const char* name) const ;
		 void SetUniformVec2(const glm::vec2 index, const char* name) const ;
		 void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name) const ;
		 void SetUniformTexture(const Eu::BaseTexture* tex, const char* name) const;
		 void SetUniform(const char* name) const;


		 void Bind();
		 void UnBind();

	private:
		std::unique_ptr<InternalMaterial> m_InternalMaterial;
	};
}
