#pragma once
#include <memory>
#include "BaseMaterial.h"

namespace Eu {
	class MaterialManager {
	public:
		static std::shared_ptr<MaterialManager> GetInstance();
		template<class T>
		std::shared_ptr<T> CreateMaterial()
		{
			std::shared_ptr<T> currMat = std::make_shared<T>();
			if (std::dynamic_pointer_cast<BaseMaterial>(currMat))
			{
				m_MaterialVec.push_back(currMat);
				return currMat;
			}
			return nullptr;
		}
		~MaterialManager();
	private:
		static std::shared_ptr<MaterialManager> m_MaterialMangerSingleton;
		std::vector<std::shared_ptr<BaseMaterial>> m_MaterialVec;

	};
}