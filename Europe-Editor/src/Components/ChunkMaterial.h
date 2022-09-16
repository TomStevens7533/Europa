#pragma once
#include "Europa/Material/BaseMaterial.h"
#include "Europa/Texture.h"

class ChunkMaterial : public Eu::BaseMaterial
{
public:
	ChunkMaterial();
protected:
private:
	void UpdateMaterialVariables() override;
private:
	std::shared_ptr<Eu::BaseTexture> m_TextureArray;


};
