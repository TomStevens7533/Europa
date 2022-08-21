#pragma once
#include "Europa/Material/BaseMaterial.h"

class PosTexCol3D : public Eu::BaseMaterial
{
public:
	PosTexCol3D();
protected:
private:
	void UpdateMaterialVariables() override;

};
