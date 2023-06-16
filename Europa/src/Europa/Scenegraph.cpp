#include "Scenegraph.h"


namespace Eu {

	ScenGraph::ScenGraph()
	{

	}

	ScenGraph::~ScenGraph()
	{
		
	}

	Eu::SceneGraphItem& ScenGraph::AddItemToSceneGraph(std::shared_ptr<GameObject> newSceneObject)
	{
		auto newEntryPair = m_SceneGraphMap.insert({ m_IndexSize, newSceneObject });
		m_IndexSize++;
		return (*(newEntryPair.first));
	}

	bool ScenGraph::RemoveItemToSceneGraph(Eu::SceneGraphItem* pair)
	{
		if (m_SceneGraphMap.count(pair->first) > 0)
		{
			m_SceneGraphMap.erase(pair->first);
			return true;
		}
		return false;
	}

	void ScenGraph::StartScene()
	{
		for (SceneGraphItem& sceneItem : m_SceneGraphMap)
		{
			sceneItem.second->Start();
		}
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