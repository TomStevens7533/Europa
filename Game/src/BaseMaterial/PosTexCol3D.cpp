#include "PosTexCol3D.h"
#include "Europa/ResourceManager.h"


PosTexCol3D::PosTexCol3D() :
	Eu::BaseMaterial("Resources/vertexShader2D.vert", "Resources/fragmentShader2D.frag")
{

}

void PosTexCol3D::UpdateMaterialVariables()
{
	auto m_texture = Eu::ResourceManager::GetInstance()->GetTexture("Resources/vehicle_diffuse.png", Eu::TextureTypes::TEXTURE2D);
	m_texture->Bind();
}

