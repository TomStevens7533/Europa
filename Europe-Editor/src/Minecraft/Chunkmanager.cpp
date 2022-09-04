#include "Chunkmanager.h"
#include "glm/gtx/fast_square_root.hpp"
#include "Europa/GameObject.h"
#include "../Components/ChunkComponent.h"

ChunkManager::ChunkManager(Eu::PerspectiveCameraControllerComponent& CameraController) : m_pCamera{&CameraController}
{
}

ChunkManager::~ChunkManager()
{
}


void ChunkManager::Update()
{
	//update chunks when crossing chunk border
	glm::vec3 CameraPos = m_pCamera->GetAttachedGameObject()->GetTransform().GetPosition();
	int xQuadrant = (CameraPos.x / m_Xdiff);
	int yQuadrant = (CameraPos.z / m_Zdiff);

	if ((xQuadrant != m_XCameraQuadrant || yQuadrant != m_YCameraQuadrant)) {
		UpdateLoadedChunks(*m_pCamera);
		m_XCameraQuadrant = xQuadrant;
		m_YCameraQuadrant = yQuadrant;
	}
}

bool ChunkManager::IsBlockSolidInChunk(std::pair<int, int> chunkInex, int xIndex, int yIndex, int zIndex) const
{
	auto elementIt = m_ChunkVec.find(chunkInex);
	if (elementIt != m_ChunkVec.end()) {	//chunk exist
		if (elementIt->second->GetChunkActiveState())
			return elementIt->second->IsBlockSolidInChunk(yIndex, xIndex, zIndex);
	}
	return true;
}

void ChunkManager::Render()
{

}


bool ChunkManager::DeleteBlockAtPos(glm::vec3 posToLook)
{
	float xIndex = (posToLook.x / m_Xdiff) ;
	float yIndex = (posToLook.z / m_Zdiff);

	int indexX = ((xIndex < 0) ?static_cast<int>(std::floor(xIndex)) : static_cast<int>(xIndex));
	int indexY = ((yIndex < 0) ? static_cast<int>(std::floor(yIndex)) : static_cast<int>(yIndex));

	if (m_ChunkVec.count({ indexX, indexY }) > 0) {
		if (m_ChunkVec[{indexX, indexY}]->DestroyBlock(posToLook)) {
			ReloadNeighbouringChunks({ indexX, indexY });
			return true;
		}
		else
			return false;
	}
	return true; //assume true if chunk does not exist

}

bool ChunkManager::AddBlockAtPos(glm::vec3 posToLook, uint8_t type)
{
	float xIndex = (posToLook.x / m_Xdiff);
	float yIndex = (posToLook.z / m_Zdiff);

	int indexX = ((xIndex < 0) ? static_cast<int>(std::floor(xIndex)) : xIndex);
	int indexY = ((yIndex < 0) ? static_cast<int>(std::floor(yIndex)) : yIndex);

	if (m_ChunkVec.count({ indexX, indexY }) > 0) {
		if (m_ChunkVec[{indexX, indexY}]->Addblock(posToLook, type)) {
			ReloadNeighbouringChunks({ indexX, indexY });
			return true;
		}
	}
	else {
		EU_CORE_INFO("CREATING Block CHUNK AT INDEX: {0}, {1}, POSITION: x:{2},y:{3}, z:{4}", indexX, indexY, indexX * m_Xdiff, 0, indexY * m_Zdiff);

		std::shared_ptr<ChunkComponent> newChunk = std::make_shared<ChunkComponent>( glm::vec3{indexX * m_Xdiff, 0, indexY * m_Zdiff}, this, std::make_pair(indexX,indexY), true);
		auto carGo = std::make_shared<Eu::GameObject>();
		carGo->AddComponent<ChunkComponent>(newChunk);
		GetAttachedGameObject()->AddChild(carGo);
		newChunk->Allocate();
		newChunk->Addblock(posToLook, type);
		m_ChunkVec.insert({ {indexX, indexY},newChunk });
		ReloadNeighbouringChunks({ indexX, indexY });
		newChunk->UpdateMesh();




	
	}
	return false;
}

void ChunkManager::UpdateLoadedChunks(Eu::PerspectiveCameraControllerComponent& CameraController)
{
	glm::vec3 cameraPos = m_pCamera->GetAttachedGameObject()->GetTransform().GetPosition();

	auto it = m_ChunkVec.begin();

	while (it != m_ChunkVec.end())
	{
		if (glm::fastDistance((*it).second->GetChunkPosition(), { cameraPos.x, cameraPos.z }) > (m_ChunkLoadDistance * 2.f)) {
			EU_CORE_TRACE("DEACTIVING CHUNK AT INDEX: {0}, {1}", (*it).first.first, (*it).first.second);
			GetAttachedGameObject()->RemoveChild((*it).second->GetAttachedGameObject());
			++it;
		}
		else
			++it;
	}

	bool isLoaded = false;
	glm::vec2 CurrentLoadPos = { cameraPos.x - m_ChunkLoadDistance, cameraPos.z - m_ChunkLoadDistance };
	while (!isLoaded)
	{
		int xIndex = static_cast<int>(CurrentLoadPos.x / m_Xdiff);
		int yIndex = static_cast<int>(CurrentLoadPos.y / m_Zdiff);

		if (CurrentLoadPos.x >= cameraPos.x + m_ChunkLoadDistance && CurrentLoadPos.y <= cameraPos.z + m_ChunkLoadDistance) {
			CurrentLoadPos.y += m_Zdiff;
			CurrentLoadPos.x = cameraPos.x - m_ChunkLoadDistance;
		}
		else
			CurrentLoadPos.x += m_Xdiff;

		if (CurrentLoadPos.x > (cameraPos.x + m_ChunkLoadDistance) && CurrentLoadPos.y > (cameraPos.z + m_ChunkLoadDistance))
			isLoaded = true;
		auto chunkIt = m_ChunkVec.find({ xIndex, yIndex });
		if (chunkIt == m_ChunkVec.end()) {
			std::shared_ptr<ChunkComponent> newChunk =  std::make_shared<ChunkComponent>(glm::vec3{ xIndex * m_Xdiff, 0, yIndex * m_Zdiff}, this, std::make_pair(xIndex, yIndex), true);
			auto carGo = std::make_shared<Eu::GameObject>();
			carGo->AddComponent<ChunkComponent>(newChunk);
			GetAttachedGameObject()->AddChild(carGo);

			m_ChunkVec.insert({ {xIndex, yIndex},newChunk });
			EU_CORE_INFO("CREATING CHUNK AT INDEX: {0}, {1}, POSITION: x:{2},y:{3}, z:{4}", xIndex, yIndex, xIndex * m_Xdiff, 0, yIndex * m_Zdiff);
			//reload neighbouring meshes to fill in missing meshes
			newChunk->UpdateMesh();

			ReloadNeighbouringChunks({ xIndex, yIndex });
		}
		else {
	/*		(*chunkIt).second->SetChunkActiveState(true);
			(*chunkIt).second->Allocate();
			(*chunkIt).second->UpdateMesh();*/


		}




	}
}

void ChunkManager::ReloadNeighbouringChunks(std::pair<int, int> chunkIndex)
{
	for (size_t i = 0; i < 4; i++)
	{
		std::pair<int, int> lookUpIndex = chunkIndex;
		if (i < 2) {
			lookUpIndex.first += (i % 2 == 1) ? 1 : -1;

		}
		else {
			lookUpIndex.second += (i % 2 == 1) ? 1 : -1;
		}

		auto it = m_ChunkVec.find(lookUpIndex);
		if (it != m_ChunkVec.end()) //found chunk
		{
			if (it->second->GetChunkActiveState()) {
				it->second->Allocate();
				it->second->UpdateMesh();
			}
		}


	}
}

void ChunkManager::Start()
{
	UpdateLoadedChunks(*m_pCamera);

}

