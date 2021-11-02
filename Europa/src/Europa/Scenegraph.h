#pragma once
#include "GameObject.h"

namespace Eu {
	typedef std::pair<uint32_t, BaseGameObject>  SceneGraphItem;

	class ScenGraph
	{
	public:
		ScenGraph();
		~ScenGraph();

		SceneGraphItem& AddItemToSceneGraph(BaseGameObject* newSceneObject);
		void Update();
		void Render() const;

	private:
		std::map<uint32_t, BaseGameObject> m_SceneGraphMap;
	};
}