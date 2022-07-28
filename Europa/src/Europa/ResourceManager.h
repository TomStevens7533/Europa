#pragma once
#include "Eupch.h"
#include <map>
#include <any>
#include "Renderer/VertexArray.h"
#include "Texture.h"
#include "Renderer/Program.h"
#include "mesh/Mesh.h"

namespace Eu {
	class ResourceManager {
	public:
		static std::shared_ptr<ResourceManager>& GetInstance();
		~ResourceManager();
	public:
		//funtions
		std::shared_ptr<BaseTexture>& GetTexture(const std::string texturePath, const TextureTypes type);
		std::shared_ptr<BaseProgram> GetProgram(ShaderType type);
	
	private:
		//Variables
		//map used for outside resources
		std::map<std::string, std::shared_ptr<VertexArray>> m_VertexMap;
		std::map<std::string, std::shared_ptr<BaseTexture>> m_TextureMap;

		std::map<ShaderType, std::shared_ptr<BaseProgram>> m_ProgramMap;

		//singleton object
		static std::shared_ptr<ResourceManager> m_ResourceMangerSingleton;
	private:
		ResourceManager() = default;


	};
}