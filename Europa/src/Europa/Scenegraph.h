#pragma once
#include "GameObject.h"

namespace Eu {
	typedef std::pair<const uint32_t, std::shared_ptr<GameObject>>  SceneGraphItem;

	class ScenGraph
	{
	public:
		ScenGraph();
		~ScenGraph();

		SceneGraphItem& AddItemToSceneGraph(GameObject* newSceneObject);
		void UpdateScene();
		void RenderScene() const;

	private:
		std::map<uint32_t, std::shared_ptr<GameObject>> m_SceneGraphMap;
		uint32_t m_IndexSize = 0;

	};
}