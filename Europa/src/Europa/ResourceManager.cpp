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

	std::shared_ptr<VertexArray>& ResourceManager::GetModel(const std::string modelPath)
	{
		//check if string is already in map
		size_t count = m_VertexMap.count(modelPath);

		if (count == 0)
		{	//is not in resource map
				//load in mesh
			auto pMesh = std::make_unique<Mesh>(modelPath);

			//create VertexArray to be stored in map
			std::shared_ptr<VertexArray> pVertexArray;
			pVertexArray.reset(VertexArray::Create());


			//Create vertexBuffer for this VertexArray
			auto& vertexBuffer = pMesh->GetVertexBuffer();
			std::shared_ptr<VertexBuffer> pVertexBuffer;
			pVertexBuffer.reset(VertexBuffer::Create(vertexBuffer.data(), vertexBuffer.size()));

			//create bufffer layout, how information is stored in our vertex buffer for example: 
			//(first 3 floats are positions, the next two are color information, etc...)
			BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Color"},
			{ShaderDataType::Float2, "a_Uv"},
			{ShaderDataType::Float3, "a_Normal"},
			};
			pVertexBuffer->SetLayout(layout);

			pVertexArray->AddVertexBuffer(pVertexBuffer);
			//pVertexArray-> AddVertexBuffer(pVertexBuffer);



			//indexbuffer
			auto& indexBuffer = pMesh->GetIndexBuffer();
			std::shared_ptr<IndexBuffer> pIndexBuffer;
			pIndexBuffer.reset(IndexBuffer::Create(indexBuffer.data(), indexBuffer.size()));
			pVertexArray.get()->AddIndexBuffer(pIndexBuffer);

			//AddVertexBuffer generate vertexattrivbutues

			//insert return pair with iterator and if it succeeded
			auto itPair = m_VertexMap.insert(std::pair{ modelPath, pVertexArray });

			//free data on cpu mesh info has been moved to gpu
			pMesh.reset();

			//return const vertexArray* from Resourcemap
			return (*itPair.first).second;

		}
		else {
			auto it = m_VertexMap.find(modelPath);

			//if resoure is already located in std::map
			return (*it).second                                                                  ;
		}
	}


	std::shared_ptr<BaseTexture>& ResourceManager::GetTexture(const std::string texturePath, const TextureTypes type)
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

	
		
	

	const std::shared_ptr<BaseProgram>& ResourceManager::GetProgram(TextureTypes type)
	{
		size_t count = m_ProgramMap.count(type);
		if (count == 0) {
			//Program is not in map
			std::shared_ptr<BaseProgram>m_Program;
			m_Program.reset(BaseProgram::Create());

			switch (type)
			{
			case TextureTypes::TEXTURE2D:
				m_Program->AttachVertexShader("Resources/vertexShader2D.vert");
				m_Program->AttachPixelShader("Resources/fragmentShader2D.frag");
				m_Program->LinkProgram();

				break;
			case TextureTypes::CUBETEXTURE:
				m_Program->AttachVertexShader("Resources/vertexShaderCUBE.vert");
				m_Program->AttachPixelShader("Resources/fragmentShaderCUBE.frag");
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


