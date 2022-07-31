#include "BlockJsonParser.h"
#include "rapidjson/document.h"
#include "Europa/ResourceManager.h"
#include <fstream>
#include "Europa/Texture.h"


std::shared_ptr<BlockJsonParser> BlockJsonParser::m_BlockResources;


std::shared_ptr<BlockJsonParser> BlockJsonParser::GetInstance()
{
	if (m_BlockResources == nullptr) {
		//create singleton
		EU_CORE_INFO("Creating Resource Manager");
		m_BlockResources.reset(new BlockJsonParser(L"Resources/Minecraft/Block.json"));
	}
	return m_BlockResources;
}

const std::vector<glm::vec2>* BlockJsonParser::GetUVOfType(uint8_t id, Faces face) const
{	
	EU_CORE_ASSERT((m_BlockMap.count(id) > 0), "lol");

	return &m_BlockMap.at(id).uvCoords.at(face);
	
}

bool BlockJsonParser::IsSolid(uint8_t id) const
{


	if (m_BlockMap.count(id) > 0) {
		return m_BlockMap.find(id)->second.IsSolid;
	}
	return false;
}

bool BlockJsonParser::IsCube(uint8_t id) const
{

	if (m_BlockMap.count(id) > 0) {
		return m_BlockMap.find(id)->second.IsCube;
	}
	return false;
}

std::string BlockJsonParser::GetName(uint8_t id)
{
	if (m_BlockMap.count(id) > 0) {
		return m_BlockMap.find(id)->second.name;
	}
	return "None";
}

void BlockJsonParser::ParseFile(std::wstring path)
{	
	using namespace rapidjson;
	std::ifstream file{ path };
	if (!file.is_open())
		throw ParserException("Unable to open file");

	// read the file contents
	std::stringstream contents;
	contents << file.rdbuf();

	Document document;
	document.Parse(contents.str().c_str());
	GenericObject fullobj  = document.GetObj();

	
	std::string texturePath = fullobj.FindMember("TexturePath")->value.GetString();
	m_pTextureAtlas = Eu::ResourceManager::GetInstance()->GetTexture(texturePath, Eu::TextureTypes::TEXTURE2D);
	;
	int textureAtlasTotalCol = fullobj.FindMember("TotalCol")->value.GetInt();
	int textureAtlasTotalRow = fullobj.FindMember("TotalRow")->value.GetInt();
	//Get BlockInformation
	GenericArray blockArr = fullobj.FindMember("BlockInfo")->value.GetArray();

	for (int i = 0; i < static_cast<int>(blockArr.Size()); i++)
	{
		BlockInformation info;
		GenericObject blockObj = blockArr[i].GetObj();
		uint8_t blockID = static_cast<uint8_t>(blockObj.FindMember("BlockID")->value.GetUint());
		info.name = blockObj.FindMember("name")->value.GetString();
		info.IsSolid = blockObj.FindMember("IsSolid")->value.GetBool();
		info.IsCube = blockObj.FindMember("IsCube")->value.GetBool();
		GenericArray UVarray = blockObj.FindMember("UV")->value.GetArray();
		GenericObject arrayOBj = UVarray.begin()->GetObj();
		
		int idx = 0;
		for (auto uvIt = arrayOBj.begin(); uvIt < arrayOBj.end(); uvIt++)
		{
			
			GenericObject obj = uvIt->value.GetObj();
			std::string name = uvIt->name.GetString();

			int currCol = obj.FindMember("AtlasCol")->value.GetInt();
			int currRow = obj.FindMember("AtlasRow")->value.GetInt();

			float texWidth = static_cast<float>(m_pTextureAtlas->GetWidth() / textureAtlasTotalCol) / m_pTextureAtlas->GetWidth();
			float texHeight = static_cast<float>(m_pTextureAtlas->GetHeigh() / textureAtlasTotalRow) / m_pTextureAtlas->GetHeigh();


			glm::vec2 uvCoordsTopRight{ (texWidth * currCol),
				texHeight * currRow };

			glm::vec2 uvCoordsTopLeft{ uvCoordsTopRight.x - texWidth, uvCoordsTopRight.y };

			glm::vec2 uvCoordsBotLeft{ uvCoordsTopRight.x, uvCoordsTopRight.y - texHeight };

			glm::vec2 uvCoordsBotRight{ uvCoordsTopRight.x - texWidth, uvCoordsTopRight.y - texHeight };

			switch (idx)
			{
			case 0:
				info.uvCoords[Faces::TOP].reserve(4);
				info.uvCoords[Faces::TOP].push_back(uvCoordsTopLeft);
				info.uvCoords[Faces::TOP].push_back(uvCoordsTopRight);
				info.uvCoords[Faces::TOP].push_back(uvCoordsBotLeft);
				info.uvCoords[Faces::TOP].push_back(uvCoordsBotRight);
				break;
			case 1:
				info.uvCoords[Faces::BOT].reserve(4);
				info.uvCoords[Faces::BOT].push_back(uvCoordsTopLeft);
				info.uvCoords[Faces::BOT].push_back(uvCoordsTopRight);
				info.uvCoords[Faces::BOT].push_back(uvCoordsBotLeft);
				info.uvCoords[Faces::BOT].push_back(uvCoordsBotRight);
				break;
			case 2:
				info.uvCoords[Faces::LEFT].reserve(4);
				info.uvCoords[Faces::LEFT].push_back(uvCoordsTopLeft);
				info.uvCoords[Faces::LEFT].push_back(uvCoordsTopRight);
				info.uvCoords[Faces::LEFT].push_back(uvCoordsBotLeft);
				info.uvCoords[Faces::LEFT].push_back(uvCoordsBotRight);
				break;
			case 3:
				info.uvCoords[Faces::RIGHT].reserve(4);
				info.uvCoords[Faces::RIGHT].push_back(uvCoordsTopLeft);
				info.uvCoords[Faces::RIGHT].push_back(uvCoordsTopRight);
				info.uvCoords[Faces::RIGHT].push_back(uvCoordsBotLeft);
				info.uvCoords[Faces::RIGHT].push_back(uvCoordsBotRight);
				break;
			case 4:
				info.uvCoords[Faces::FRONT].reserve(4);
				info.uvCoords[Faces::FRONT].push_back(uvCoordsTopLeft);
				info.uvCoords[Faces::FRONT].push_back(uvCoordsTopRight);
				info.uvCoords[Faces::FRONT].push_back(uvCoordsBotLeft);
				info.uvCoords[Faces::FRONT].push_back(uvCoordsBotRight);
				break;
			case 5:
				info.uvCoords[Faces::BACK].reserve(4);
				info.uvCoords[Faces::BACK].push_back(uvCoordsTopLeft);
				info.uvCoords[Faces::BACK].push_back(uvCoordsTopRight);
				info.uvCoords[Faces::BACK].push_back(uvCoordsBotLeft);
				info.uvCoords[Faces::BACK].push_back(uvCoordsBotRight);
				break;
			default:
				break;
			}
			idx++;
		}

		m_BlockMap.insert(std::make_pair(blockID, info));
	}

	file.close();
}

