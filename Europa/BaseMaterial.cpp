#include "BaseMaterial.h"
#include <string>
#include "InternalMaterial.h"
#pragma once
using namespace Eu;
Eu::BaseMaterial::BaseMaterial(std::string vertexShader, std::string PixelShader /*= 0*/)
{
	m_InternalMaterial = (InternalMaterial::GetInternalMaterial());
	m_InternalMaterial->AttachVertexShader(vertexShader);
	m_InternalMaterial->AttachPixelShader(PixelShader);
}

void BaseMaterial::UnBind()
{
	m_InternalMaterial->UnBind();
}

void BaseMaterial::Bind()
{
	m_InternalMaterial->Bind();

}

void BaseMaterial::SetUniformVec4(const glm::vec4& vec4Uniform, const char* name) const
{
	m_InternalMaterial->SetUniformVec4(vec4Uniform, name);
}

void BaseMaterial::SetUniformVec2(const glm::vec2 index, const char* name) const
{
	m_InternalMaterial->SetUniformVec2(index, name);

}

void BaseMaterial::SetUniformInt(const int index, const char* name) const
{
	m_InternalMaterial->SetUniformInt(index, name);

}

void BaseMaterial::SetUniformMatrix4(const glm::mat4& mat4, const char* name)
{
	m_InternalMaterial->SetUniformMatrix4(mat4, name);

}

void BaseMaterial::UpdateMaterialVariables()
{

}

