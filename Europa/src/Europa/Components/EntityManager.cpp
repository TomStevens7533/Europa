#include "EntityManager.h"

namespace Eu {

	EntityManager::~EntityManager()
	{
		for (auto mapPair : m_ComponentSet)
		{
			mapPair.reset();
		}
	}


	void EntityManager::Start()
	{
		for (auto mapPair : m_ComponentSet)
		{
			mapPair->Start();
		}
	}

	void EntityManager::Update()
	{
		for (auto mapPair : m_ComponentSet)
		{
			mapPair->Update();
		}
	}

	void EntityManager::FixedUpdate()
	{
		for (auto mapPair : m_ComponentSet)
		{
			mapPair->FixedUpdate();
		}
	}

	void EntityManager::Render() const
	{
		for (auto mapPair : m_ComponentSet)
		{
			mapPair->Render();
		}
	}

}
