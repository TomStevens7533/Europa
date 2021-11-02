#pragma once
#include "Eupch.h"
#include <map>
#include <any>
#include "Renderer/VertexArray.h"
#include "Texture.h"
#include "Renderer/Program.h"

namespace Eu {
	class ResourceManager {
	public:
		static ResourceManager* GetInstance();
		~ResourceManager() {
			std::cout << "Resourcemanager Deleteion\n";
		}
	public:
		//funtions
		std::shared_ptr<VertexArray> GetModel(const std::string modelPath);
		std::shared_ptr<BaseTexture> GetTexture(const std::string texturePath, const TextureTypes type);
		const std::shared_ptr<BaseProgram>& GetProgram(TextureTypes type);
	
	private:
		//Variables
		//map used for outside resources
		std::map<std::string, std::any> m_ResourceMap;
		std::map<TextureTypes, std::shared_ptr<BaseProgram>> m_ProgramMap;

		//singleton object
		static ResourceManager* m_ResourceMangerSingleton;
	private:
		ResourceManager() = default;
		// Stop the compiler generating methods of copy the object
		ResourceManager(const ResourceManager& copy) = delete;            // Not Implemented
		ResourceManager& operator=(const ResourceManager& copy) = delete; // Not Implemented

	};
}