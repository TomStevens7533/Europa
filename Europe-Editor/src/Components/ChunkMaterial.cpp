#include "ChunkMaterial.h"
#include "Europa/ResourceManager.h"


ChunkMaterial::ChunkMaterial() :
	Eu::BaseMaterial("Resources/vertexShader2D.vert", "Resources/fragmentShader2D.frag")
{

}

void ChunkMaterial::UpdateMaterialVariables()
{
	auto m_texture = Eu::ResourceManager::GetInstance()->GetTexture("Resources/minecraft/Textures/newAtlas.png", Eu::TextureTypes::TEXTURE2D);
	m_texture->Bind();


	//auto m_texture = Eu::ResourceManager::GetInstance()->GetTexture("Resources/vehicle_diffuse.png", Eu::TextureTypes::TEXTURE2D);
	//m_texture->Bind();
}

