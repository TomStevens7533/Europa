#include "Eupch.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

#include  <glad/glad.h>


namespace Eu
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		
			// Create an empty vertex shader handle
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			EU_CORE_ASSERT(false,"Vertex shader compilation failed!!: {0}", infoLog.data());
			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			EU_CORE_ASSERT(false, infoLog.data() );
			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RenderID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RenderID, vertexShader);
		glAttachShader(m_RenderID, fragmentShader);

		// Link our program
		glLinkProgram(m_RenderID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RenderID, GL_LINK_STATUS, (int *)&isLinked);
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
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			EU_CORE_ASSERT(false, "shader link compilation failed!!: {0}", infoLog.data());
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RenderID, vertexShader);
		glDetachShader(m_RenderID, fragmentShader);

	}


	Shader::~Shader()
	{
		glDeleteProgram(m_RenderID);
	}

	
	void Shader::Bind() const
	{
		glUseProgram(m_RenderID);
	}

	void Shader::UnBind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniformMatrix4(const glm::mat4& mat4, const char* name)
	{
		GLint loc = glGetUniformLocation(m_RenderID, name);
		if (loc == -1) {
			EU_CORE_ASSERT(false, "Matrix not found at loc: ", loc);
		}
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
	}



	
	void Shader::SetUniformInt(const int index, const char* name)
	{
		GLint loc = glGetUniformLocation(m_RenderID, name);
		if (loc == -1) {
			EU_CORE_ASSERT(false, "Matrix not found at loc: ", loc);
		}
		glUniform1i(loc, index);
	}

}