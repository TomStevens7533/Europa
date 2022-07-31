#pragma once
#include "../BaseMaterial.h"

class ChunkMaterial : public Eu::BaseMaterial
{
public:
	ChunkMaterial();
protected:
private:
	void UpdateMaterialVariables() override;

};
