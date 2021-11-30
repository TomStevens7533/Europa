#pragma once

#include  <string>
#include "glm/glm.hpp"

namespace Eu
{
	class BaseShader {
	public:
		BaseShader(std::string path);
		virtual ~BaseShader() {};

		inline const unsigned int GetShaderID() { return m_ShaderID; }

		virtual void SetUniformMatrix4(const glm::mat4& mat4, const char* name, uint32_t renderID) = 0;
		virtual void SetUniformInt(const int index, const char* name, uint32_t renderID) = 0;
		
		virtual void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name, uint32_t renderID) = 0;
		virtual void SetUniformVec2(const glm::vec2 index, const char* name, uint32_t renderID) = 0;

	protected:
		std::string& GetData() { return m_Data; }

	protected:
		unsigned int m_ShaderID;
	private:
		void ParseFile(std::string& path);
	private:
		std::string m_Path;
		std::string m_Data;
	};

	class VertexShader : public BaseShader
	{
	public:
		VertexShader(const std::string& path) : BaseShader(path) {};
		virtual ~VertexShader() {};

		static VertexShader* Create(const std::string& path);
		virtual void SetUniformMatrix4(const glm::mat4& mat4, const char* name, uint32_t renderID) = 0;
		virtual void SetUniformInt(const int index, const char* name, uint32_t renderID) = 0;
		virtual void SetUniformVec2(const glm::vec2 index, const char* name, uint32_t renderID) = 0;
		virtual void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name, uint32_t renderID) = 0;



	};

	class IndexShader : public BaseShader
	{
	public:
		IndexShader(const std::string& path) : BaseShader(path) {};
		virtual ~IndexShader() {};

		static IndexShader* Create(const std::string& path);
		virtual void SetUniformMatrix4(const glm::mat4& mat4, const char* name, uint32_t renderID) = 0;
		virtual void SetUniformInt(const int index, const char* name, uint32_t renderID) = 0;
		virtual void SetUniformVec2(const glm::vec2 index, const char* name, uint32_t renderID) = 0;
		virtual void SetUniformVec4(const glm::vec4& vec4Uniform, const char* name, uint32_t renderID) = 0;




	};
}