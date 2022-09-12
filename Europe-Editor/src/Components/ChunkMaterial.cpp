#include "ChunkMaterial.h"
#include "Europa/ResourceManager.h"


ChunkMaterial::ChunkMaterial() :
	Eu::BaseMaterial("Resources/vertexShader2D.vert", "Resources/fragmentShader2D.frag")
{
	std::vector<std::string> m_TextureArray{};
	m_TextureArray.push_back("Resources/minecraft/Textures/Blocks/dirt.png");
	m_TextureArray.push_back("Resources/minecraft/Textures/Blocks/dirt_grass.png");
	m_TextureArray.push_back("Resources/minecraft/Textures/Blocks/grass_top.png");
	m_TextureArray.push_back("Resources/minecraft/Textures/Blocks/greystone.png");


	m_Texture = Eu::ResourceManager::GetInstance()->GetTexture(m_TextureArray, Eu::TextureTypes::TEXTUREARRAY);;
}

void ChunkMaterial::UpdateMaterialVariables()
{
	//SetUniform();
	//m_Texture->Bind();


	auto m_texture = Eu::ResourceManager::GetInstance()->GetTexture("Resources/vehicle_diffuse.png", Eu::TextureTypes::TEXTURE2D);
	//m_texture->Bind();
}

