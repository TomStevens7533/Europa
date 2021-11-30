#include "Program.h"
#include "Renderer.h"
#include <glad/glad.h>


//maybe use map im not gonna support multiple of the same shaders
namespace Eu 
{

	BaseProgram::BaseProgram()
	{
		m_ShaderMap.insert({ ShaderTypes::T_VertexShader, std::shared_ptr<BaseShader>() });
		m_ShaderMap.insert({ ShaderTypes::T_PixelShader, std::shared_ptr<BaseShader>() });

	}

	BaseProgram* BaseProgram::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EU_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;

		case RendererAPI::API::OpenGL: EU_CORE_INFO("RendererAPI::OpenGL is active"); return new OpenGlProgram();

		}
		EU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	void BaseProgram::AttachVertexShader(const std::string& path)
	{
		//optimize
		m_ShaderMap.at(ShaderTypes::T_VertexShader).reset(VertexShader::Create(path));
	}

	void BaseProgram::AttachPixelShader(const std::string& path)
	{
		//optimize
		m_ShaderMap.at(ShaderTypes::T_PixelShader).reset(IndexShader::Create(path));

	}

	void BaseProgram::SetUniformMatrix4(const glm::mat4& mat4, const char* name, ShaderTypes type)
	{
		m_ShaderMap.at(type)->SetUniformMatrix4(mat4, name, m_RenderID);
	}

	void BaseProgram::SetUniformInt(const int index, const char* name, ShaderTypes type) const
	{
		m_ShaderMap.at(type)->SetUniformInt(index, name, m_RenderID);
	}

	void BaseProgram::SetUniformVec2(const glm::vec2 uniformVec2, const char* name, ShaderTypes type) const
	{
		m_ShaderMap.at(type)->SetUniformVec2(uniformVec2, name, m_RenderID);

	}

	void BaseProgram::SetUniformVec4(const glm::vec4& vec4Uniform, const char* name, ShaderTypes type) const
	{
		m_ShaderMap.at(type)->SetUniformVec4(vec4Uniform, name, m_RenderID);


	}

	void BaseProgram::ClearShaders()
	{
		m_ShaderMap.clear();
	}







	OpenGlProgram::OpenGlProgram()
	{

		// Get a program object.
		m_RenderID = glCreateProgram();

	}

	OpenGlProgram::~OpenGlProgram()
	{
		glDeleteProgram(m_RenderID);
	}

	void OpenGlProgram::LinkProgram()
	{
		// Attach our shaders to our program
		for(auto& keyValPair : m_ShaderMap)
			glAttachShader(m_RenderID,keyValPair.second->GetShaderID());

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
			for (auto& keyValPair : m_ShaderMap)
				glDeleteShader(keyValPair.second->GetShaderID());

			// Use the infoLog as you see fit.
			EU_CORE_ASSERT(false, "shader link compilation failed!!: {0}", infoLog.data());
			// In this simple program, we'll just leave
			return;
		}
		// Always detach shaders after a successful link.
		for (auto& keyValPair : m_ShaderMap)
			glDetachShader(m_RenderID, keyValPair.second->GetShaderID());


	}

	void OpenGlProgram::Bind() const
	{
		glUseProgram(m_RenderID);

	}

	void OpenGlProgram::UnBind() const
	{
		glUseProgram(0);
	}


}

