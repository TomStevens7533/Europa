#include "ResourceManager.h"
#include "mesh/Mesh.h"
namespace Eu {

	//TODO MAKE UNORDERED MAP
	std::shared_ptr<ResourceManager> ResourceManager::m_ResourceMangerSingleton = nullptr;



	std::shared_ptr<ResourceManager>& ResourceManager::GetInstance()
	{
		if (m_ResourceMangerSingleton == nullptr) {
			//create singleton
			EU_CORE_INFO("Creating Resource Manager");
			m_ResourceMangerSingleton.reset(new ResourceManager());
		}
		return m_ResourceMangerSingleton;
	}

	

	ResourceManager::~ResourceManager()
	{
	}



	std::shared_ptr<BaseTexture> ResourceManager::GetTexture(const std::string texturePath, const TextureTypes type)
	{
		size_t count = m_TextureMap.count(texturePath);


		if (count == 0) {
			//Texture not in resource map
			std::shared_ptr<BaseTexture> pTexture;
			switch (type)
			{
			case TextureTypes::TEXTURE2D:
				pTexture = (Texture2D::Create(texturePath));
				break;
			case TextureTypes::CUBETEXTURE:
				pTexture = (CubeTexture::Create(texturePath));
				break;
			default:
				break;
			}

			//insert return pair with iterator and if it succeeded
			auto itPair = m_TextureMap.insert(std::pair{ texturePath, pTexture });
			return (*itPair.first).second;


		}
		else {
			auto it = m_TextureMap.find(texturePath);
			return (*it).second;

			//make templated
		}

		
		
		
	}

	
		

	}


