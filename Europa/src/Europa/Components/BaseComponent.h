#pragma once
#include <limits.h>
#include <memory>
namespace Eu {
	class GameObject;
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

		std::shared_ptr<GameObject> GetAttachedGameObject() const { return m_pParent.lock(); }
		void SetAttachedGo(std::weak_ptr<GameObject> parentGO) { m_pParent = parentGO; }


	protected:
		std::weak_ptr<GameObject> m_pParent{};
	};


};
