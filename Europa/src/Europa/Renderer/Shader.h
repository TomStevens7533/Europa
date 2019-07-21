#pragma once

#include  <string>
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

	private:
		uint32_t m_RenderID = 0;
		
	};
}