#pragma once

#include  <string>
#include <glm/glm.hpp>
namespace Eu
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

		~Shader();

		void Bind() const;
		void UnBind() const;

		static Shader* Create();
		void SetUniformMatrix4(const glm::mat4& mat4, const char* name);

	private:
		uint32_t m_RenderID = 0;
		
	};
}