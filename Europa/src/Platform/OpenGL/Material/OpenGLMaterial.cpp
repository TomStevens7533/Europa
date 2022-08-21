#include "Eupch.h"
#include "OpenGLMaterial.h"
#include <glad/glad.h>
#include "glm/gtc/type_ptr.inl"

using namespace Eu;

OpenGLMaterial::OpenGLMaterial()
{
	m_RenderID = glCreateProgram();

}

void Eu::OpenGLMaterial::Bind() 
{
	if (m_IsBound == false) {
		glUseProgram(m_RenderID);
		m_IsBound = true;
	}

}

void Eu::OpenGLMaterial::UnBind() 
{
	if (m_IsBound == true) {
		glUseProgram(0);
		m_IsBound = false;
	}
}

void Eu::OpenGLMaterial::SetUniformMatrix4(const glm::mat4& mat4, const char* name)
{
	GLint loc = glGetUniformLocation(m_RenderID, name);
	if (loc == -1) {
		EU_CORE_ASSERT(false, "Matrix not found at loc: ", loc);
	}
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Eu::OpenGLMaterial::SetUniformInt(const int index, const char* name) const
{
	GLint loc = glGetUniformLocation(m_RenderID, name);
	if (loc == -1) {
		EU_CORE_ASSERT(false, "Matrix not found at loc: ", loc);
	}
	glUniform1i(loc, index);
}

void Eu::OpenGLMaterial::SetUniformVec2(const glm::vec2 index, const char* name) const
{
	GLint loc = glGetUniformLocation(m_RenderID, name);
	if (loc == -1) {
		EU_CORE_ASSERT(false, "Matrix not found at loc: ", loc);
	}
	glUniform2f(loc, index.x, index.y);
}

void Eu::OpenGLMaterial::SetUniformVec4(const glm::vec4& vec4Uniform, const char* name) const
{
	GLint loc = glGetUniformLocation(m_RenderID, name);
	if (loc == -1) {
		EU_CORE_ASSERT(false, "vec4 uniform not found at loc: ", loc);
	}
	glUniform4f(loc, vec4Uniform.x, vec4Uniform.y, vec4Uniform.z, vec4Uniform.w);
}

void OpenGLMaterial::LinkProgram()
{
	// Attach our shaders to our program
	for (auto& key : m_ShaderMap)
		glAttachShader(m_RenderID, key->GetShaderID());

	// Link our program
	glLinkProgram(m_RenderID);



	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_RenderID, GL_LINK_STATUS, (int*)&isLinked);
	Bind();
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_RenderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_RenderID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_RenderID);
		// Don't leak shaders either.
		for (auto& key : m_ShaderMap)
			glDeleteShader(key->GetShaderID());

		// Use the infoLog as you see fit.
		EU_CORE_ASSERT(false, "shader link compilation failed!!: {0}", infoLog.data());
		// In this simple program, we'll just leave
		return;
	}
	// Always detach shaders after a successful link.
	for (auto& key : m_ShaderMap)
		glDetachShader(m_RenderID, key->GetShaderID());
}


OpenGLMaterial::~OpenGLMaterial()
{
	EU_CORE_INFO("Deleting Material");

}

void Eu::OpenGLMaterial::AttachVertexShader(const std::string& path)
{
	m_ShaderMap.push_back(std::make_shared<OpenGLVertexShader>(path));
}

void Eu::OpenGLMaterial::AttachPixelShader(const std::string& path)
{
	m_ShaderMap.push_back(std::make_shared<OpenGLIndexShader>(path));
	LinkProgram();

}

