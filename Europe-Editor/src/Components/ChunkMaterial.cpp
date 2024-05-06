#include "ChunkMaterial.h"
#include "Europa/ResourceManager.h"


ChunkMaterial::ChunkMaterial() :
	Eu::BaseMaterial("Resources/vertexShader2D.vert", "Resources/fragmentShader2D.frag")
{
	std::vector<std::string> paths;
	paths.push_back("Resources/Blocks/dirt.png");
	paths.push_back("Resources/Blocks/dirt_grass.png");
	paths.push_back("Resources/Blocks/grass_top.png");
	paths.push_back("Resources/Blocks/greystone.png");
	paths.push_back("Resources/Blocks/steen.png");
	paths.push_back("Resources/Blocks/wood.png");


	m_TextureArray = Eu::ResourceManager::GetInstance()->GetTexture(paths, Eu::TextureTypes::TEXTUREARRAY);


}

void ChunkMaterial::UpdateMaterialVariables()
{
	//SetUniform();
	SetUniformTexture(m_TextureArray.get(), "my_sampler");
	
	//m_texture->Bind();
}

