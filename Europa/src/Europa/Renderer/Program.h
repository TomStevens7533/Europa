#pragma once
#include "Shader.h"
#include "Eupch.h"
#include <map>

namespace Eu {
	class BaseShader;
	class BaseProgram
	{
	public:
		BaseProgram();
		virtual ~BaseProgram() {};

		static BaseProgram* Create();

		enum class ShaderTypes
		{
			T_VertexShader,
			T_PixelShader
		};


		void AttachVertexShader(const std::string& path);
		void AttachPixelShader(const std::string& path);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		void SetUniformMatrix4(const glm::mat4& mat4, const char* name, ShaderTypes type);
		void SetUniformInt(const int index, const char* name, ShaderTypes type) const;



		void ClearShaders();
		virtual void LinkProgram() = 0;

	protected:
		uint32_t m_RenderID;
		std::map<ShaderTypes, std::shared_ptr<BaseShader>> m_ShaderMap;
	};

	
	class OpenGlProgram : public BaseProgram
	{
	public:
		OpenGlProgram();
		virtual ~OpenGlProgram();
		virtual void LinkProgram() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

	};

}
