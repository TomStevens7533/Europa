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

	
		
	

	std::shared_ptr<BaseProgram> ResourceManager::GetProgram(ShaderType type)
	{
		size_t count = m_ProgramMap.count(type);
		if (count == 0) {
			//Program is not in map
			std::shared_ptr<BaseProgram>m_Program;
			m_Program.reset(BaseProgram::Create());

			switch (type)
			{
			case ShaderType::TEXTURE2D_WORLDSPACE_SHADER:
				m_Program->AttachVertexShader("Resources/vertexShader2D.vert");
				m_Program->AttachPixelShader("Resources/fragmentShader2D.frag");
				m_Program->LinkProgram();

				break;
			case ShaderType::CUBETEXTURE_LOCALSPACE_SHADER:
				m_Program->AttachVertexShader("Resources/vertexShaderCUBE.vert");
				m_Program->AttachPixelShader("Resources/fragmentShaderCUBE.frag");
				m_Program->LinkProgram();
				break;
			case ShaderType::TEXTURE2D_UILOCALSPACE_SHADER:
				m_Program->AttachVertexShader("Resources/VertexShaderUI.vert");
				m_Program->AttachPixelShader("Resources/FragmentShaderUI.frag");
				m_Program->LinkProgram();
				break;
			default:
				break;
			
			}
			//put new program in programmap;
			auto it = m_ProgramMap.insert(std::pair{ type, m_Program });
			return (*it.first).second;
			
		}
		else {
			auto it = m_ProgramMap.find(type);
			return (*it).second;
		}
	}

	}


