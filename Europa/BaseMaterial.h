#pragma once
#include <string>
#include <memory>
#include "InternalMaterial.h"
namespace Eu {
	class BaseMaterial {
	public:
		BaseMaterial(std::string vertexShader, std::string PixelShader = 0);
		virtual void UpdateMaterialVariables() = 0;



	private:
		std::unique_ptr<InternalMaterial> m_InternalMaterial;
	};
}
