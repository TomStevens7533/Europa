#pragma once
#include <memory>
#include "BaseMaterial.h"

namespace Eu {
	class MaterialManager {
	public:
		static std::shared_ptr<MaterialManager> GetInstance();
		template<class T>
		inline std::shared_ptr<T> CreateMaterial() noexcept
		{
			std::shared_ptr<T> currMat = std::make_shared<T>();
			for (auto element : m_MaterialVec)
			{
				if (std::is_same<T, decltype(element)>::value)
					return std::dynamic_pointer_cast<T>(element);
			}
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