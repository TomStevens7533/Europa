#include "BaseMaterial.h"
#include <string>
#include "InternalMaterial.h"
#pragma once
using namespace Eu;
Eu::BaseMaterial::BaseMaterial(std::string vertexShader, std::string PixelShader /*= 0*/)
{
	m_InternalMaterial->AttachVertexShader(vertexShader);
	m_InternalMaterial->AttachPixelShader(PixelShader);
}
