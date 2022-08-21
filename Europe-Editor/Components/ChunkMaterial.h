#pragma once
#include "Europa/Material/BaseMaterial.h"

class ChunkMaterial : public Eu::BaseMaterial
{
public:
	ChunkMaterial();
protected:
private:
	void UpdateMaterialVariables() override;

};
