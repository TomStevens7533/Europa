#include "Eupch.h"
#include "OpenGLShader.h"
#include "glm/gtc/type_ptr.inl"
#include <glad/glad.h>
#include "EuropaOpenGL.h"

namespace Eu {

	//vertexShader
	OpenGLVertexShader::OpenGLVertexShader(const std::string& path) : VertexShader(path)
	{



		// Create an empty vertex shader handle
		m_ShaderID = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = GetData().c_str();
		glShaderSource(m_ShaderID, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(m_ShaderID);

		GLint isCompiled = 0;
		glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(m_ShaderID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(m_ShaderID);

			// Use the infoLog as you see fit.
			EU_CORE_ASSERT(false, infoLog.data());
			// In this simple program, we'll just leave
			return;
		}

	}

	OpenGLVertexShader::~OpenGLVertexShader()
	{
		//glDeleteProgram(m_RenderID);
	}

	void OpenGLVertexShader::SetUniformMatrix4(const glm::mat4& mat4, const char* name, uint32_t renderID)
	{
		GLint loc = glGetUniformLocation(renderID, name);
		if (loc == -1) {
			EU_CORE_ASSERT(false, "Matrix not found at loc: ", loc);
		}
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
		glCheckError();

	}

	void OpenGLVertexShader::SetUniformInt(const int index, const char* name, uint32_t renderID)
	{
		GLint loc = glGetUniformLocation(renderID, name);
		if (loc == -1) {
			EU_CORE_ASSERT(false, "Matrix not found at loc: ", loc);
		}
		glUniform1i(loc, index);
		glCheckError();

	}


	//IndexShader
	OpenGLIndexShader::OpenGLIndexShader(const std::string& path): IndexShader(path)
	{
		// Create an empty fragment shader handle
		m_ShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = GetData().c_str();
		glShaderSource(m_ShaderID, 1, &source, 0);

		GLint isCompiled = 0;
		// Compile the fragment shader
		glCompileShader(m_ShaderID);

		glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(m_ShaderID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(m_ShaderID);

			EU_CORE_ASSERT(false, infoLog.data());
			// In this simple program, we'll just leave
			return;
		}
		glCheckError();


	}

	OpenGLIndexShader::~OpenGLIndexShader()
	{
		//glDeleteProgram(m_RenderID);
	}

	void OpenGLIndexShader::SetUniformMatrix4(const glm::mat4& mat4, const char* name, uint32_t renderID)
	{
		GLint loc = glGetUniformLocation(renderID, name);
		if (loc == -1) {
			EU_CORE_ASSERT(false, "Matrix not found at loc: ", loc);
		}
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));

	}

	void OpenGLIndexShader::SetUniformInt(const int index, const char* name, uint32_t renderID)
	{

		GLint loc = glGetUniformLocation(renderID, name);
		if (loc == -1) 
			EU_CORE_ASSERT(false, "Matrix not found at loc: ", loc);
		
		glUniform1i(loc, index); //GIVES INVALID_OPERATION error


	}

}