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