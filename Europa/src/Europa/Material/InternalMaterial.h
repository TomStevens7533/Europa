#pragma once
#include <string>
#include "glm/ext/matrix_float4x4.hpp"
#include <memory>

namespace Eu {
	class InternalMaterial
	{
	public:
		static std::unique_ptr<InternalMaterial> GetInternalMaterial();
		virtual void Bind()  = 0;
		virtual void UnBind()  = 0;
		virtual ~InternalMaterial() {};
		 virtual void AttachVertexShader(const std::string& path) = 0;
		 virtual void AttachPixelShader(const std::string& path)= 0;

		 virtual void SetUniformMatrix4(const glm::mat4& mat4, const char* name) = 0;
		 virtual void SetUniformInt(const int index, const char* name) const = 0;
		 virtual void SetUniformVec2(const glm::vec2 index, const char* name) const = 0;
		 virtual void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name) const = 0;
		 virtual void SetUniform(const char* name) const = 0;

	};


}
