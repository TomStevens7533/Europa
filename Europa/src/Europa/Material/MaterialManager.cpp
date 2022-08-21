#include "Eupch.h"
#include "MaterialManager.h"
#include "BaseMaterial.h"
using namespace Eu;

std::shared_ptr<Eu::MaterialManager> Eu::MaterialManager::m_MaterialMangerSingleton = nullptr;


std::shared_ptr<Eu::MaterialManager> MaterialManager::GetInstance()
{
	if (m_MaterialMangerSingleton == nullptr) {
		//create singleton
		EU_CORE_INFO("Creating Material Manager");
		m_MaterialMangerSingleton = std::make_shared<MaterialManager>();
	}
	return m_MaterialMangerSingleton;
}
Eu::MaterialManager::~MaterialManager()
{
	EU_CORE_INFO("Deleteing Material Manager");

}

