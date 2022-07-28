#include "Scenegraph.h"


namespace Eu {

	ScenGraph::ScenGraph()
	{

	}

	ScenGraph::~ScenGraph()
	{

	}

	SceneGraphItem& ScenGraph::AddItemToSceneGraph(GameObject* newSceneObject)
	{

		std::shared_ptr<GameObject>pnewSceneEntry;
		pnewSceneEntry.reset(newSceneObject);

		auto newEntryPair = m_SceneGraphMap.insert({ m_IndexSize, pnewSceneEntry });
		m_IndexSize++;
		return (*(newEntryPair.first));
	}

	void ScenGraph::UpdateScene()
	{
		for (SceneGraphItem& sceneItem : m_SceneGraphMap)
		{
			sceneItem.second->Update();
		}
	}

	void ScenGraph::RenderScene() const
	{
		for (const SceneGraphItem& sceneItem : m_SceneGraphMap)
		{
			sceneItem.second->Render();
		}
	}

}