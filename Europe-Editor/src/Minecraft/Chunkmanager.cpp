#include "Chunkmanager.h"
#include "glm/gtx/fast_square_root.hpp"
#include "Europa/GameObject.h"
#include "../Components/ChunkComponent.h"

ChunkManager::ChunkManager(Eu::PerspectiveCameraControllerComponent& CameraController) : m_pCamera{&CameraController}
{
	m_IsShutdown = true;
	//Seed calc
	m_Seed = static_cast<unsigned int>(time(NULL));
}
void ChunkManager::Start()
{
	m_UpdateChunkThread = std::thread(&ChunkManager::UpdateChunksAroundPos, this);

}

ChunkManager::~ChunkManager()
{
	m_IsShutdown = false;

	//Wait for update chunk
	//wait till cycle is done
	std::unique_lock<std::mutex> lock1(m_MutexUpdate);
	cond.notify_all();
	cond.wait(lock1, [this]() {return m_IsCycleUpdateDone == true; });
	lock1.unlock();
	m_UpdateChunkThread.join();
}

void ChunkManager::UpdateChunksAroundPos()
{
	while (m_IsShutdown) {

		float newDistance = m_ChunkDistance;
		glm::vec3 position = m_pCamera->GetAttachedGameObject()->GetTransform().GetWorldPosition();
		int xEnd = static_cast<int>(position.x) - (ChunkSizeX * (std::ceil(newDistance)));
		int zEnd = static_cast<int>(position.z) - (ChunkSizeZ * (std::ceil(newDistance)));

		std::unique_lock<std::mutex> lock1(m_MutexUpdate);

		for (int x = 0; x < (newDistance * 2.f); x++)
		{
			for (int z = 0; z < (newDistance * 2.f); z++)
			{
				int xWorldPos = xEnd + (ChunkSizeX * x);
				int zWorldPos = zEnd + (ChunkSizeZ * z);
				lock1.unlock();
				if (m_IsShutdown == false) {
					cond.notify_one();
					m_IsCycleUpdateDone = true;
					return;
				}
				lock1.lock();
				if (m_IsCycleUpdateDone == false && (m_ChunkVec.count(std::make_pair(xWorldPos, zWorldPos)) > 0)) {
					m_IsCycleUpdateDone = false;
					if (m_ChunkVec[std::make_pair(xWorldPos, zWorldPos)]->GetDirtyFlag() == true) {
						m_ChunkVec[std::make_pair(xWorldPos, zWorldPos)]->UpdateMesh();
					}

				}

			}
		}
		if (m_IsCycleUpdateDone == false) {
			m_IsCycleUpdateDone = true;
			m_IsCycleCreateDone = false;
		}



	}
}

void ChunkManager::Update()
{

	if (m_IsCycleUpdateDone) {
		glm::vec3 position = m_pCamera->GetAttachedGameObject()->GetTransform().GetWorldPosition();
		int xEnd = static_cast<int>(position.x) - (ChunkSizeX * m_ChunkDistance);
		int zEnd = static_cast<int>(position.z) - (ChunkSizeZ * m_ChunkDistance);

		std::unique_lock<std::mutex> lock1(m_MutexUpdate);
		for (int x = 0; x < (m_ChunkDistance * 2); x++)
		{
			for (int z = 0; z < (m_ChunkDistance * 2); z++)
			{
				lock1.unlock();
				int xWorldPos = xEnd + (ChunkSizeX * x);
				int zWorldPos = zEnd + (ChunkSizeZ * z);
				if (m_IsShutdown == false) {
					cond.notify_one();
					m_IsCycleCreateDone = true;
					return;
				}
				lock1.lock();
				if (m_IsCycleCreateDone == false && (m_ChunkVec.count(std::make_pair(xWorldPos, zWorldPos)) == 0)) {

					std::shared_ptr<ChunkComponent> newChunk = 
						std::make_shared<ChunkComponent>(
							glm::vec3(static_cast<float>(xWorldPos), 0, static_cast<float>(zWorldPos))
							, this, true);


					std::shared_ptr<Eu::GameObject> newChunkGO = std::make_shared<Eu::GameObject>();
					newChunkGO->AddComponent<ChunkComponent>(newChunk);
					EU_CORE_INFO("CREATING CHUNK AT {0}, {1}", xWorldPos, zWorldPos);
					GetAttachedGameObject()->AddChild(newChunkGO);
					newChunkGO->SetPosition(glm::vec3{ xWorldPos, 0 , zWorldPos });
					m_ChunkVec.insert(std::make_pair(std::make_pair(xWorldPos, zWorldPos), newChunk));

				}


			}
		}
		m_IsCycleCreateDone = true;
		m_IsCycleUpdateDone = false;
		cond.notify_all();
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
	auto chunkIndex = WorldToChunkIndex(posToLook);
	std::pair<int, int> Key = std::make_pair(chunkIndex.first, chunkIndex.second);
	if (m_ChunkVec.count(Key) > 0) {

		ChunkPosistion localPos = WorldToLocalChunkPos(posToLook);

		uint8_t id = m_ChunkVec[Key]->DestroyBlock(glm::vec3{ localPos.x, localPos.y, localPos.z });
		if (id != 0) {
			ReloadNeighbouringChunks(Key);
			return id;

		}
	}
	return 0;

}

bool ChunkManager::AddBlockAtPos(glm::vec3 posToLook, uint8_t type)
{

	auto chunkIdx = WorldToChunkIndex(posToLook);
	std::pair<int, int> Key = std::make_pair(chunkIdx.first, chunkIdx.second);
	if (m_ChunkVec.count(Key) > 0) {

		auto pos = WorldToLocalChunkPos(posToLook);


		if (m_ChunkVec[Key]->Addblock(glm::vec3{pos.x, pos.y, pos.z}, type)) {
			ReloadNeighbouringChunks(Key);
			return true;

		}
	}

	return false;
}

std::pair<int, int> ChunkManager::GetChunkIdx(glm::vec3 pos) const
{
	int mulX = (pos.x < 0 ? static_cast<int>((static_cast<int>(pos.x)) / ChunkSizeX) - 1 : (static_cast<int>(pos.x) / ChunkSizeX));
	int mulZ = (pos.z < 0 ? static_cast<int>((static_cast<int>(pos.z)) / ChunkSizeZ) - 1 : (static_cast<int>(pos.z) / ChunkSizeZ));
	int Chunkx = ChunkSizeX * mulX;
	int Chunkz = ChunkSizeZ * mulZ;


	std::pair<int, int> Key = std::make_pair(Chunkx, Chunkz);
	return Key;
}

ChunkPosistion ChunkManager::WorldToLocalChunkPos(glm::vec3 position) const
{
	auto chunkIndex = WorldToChunkIndex(position);

	int dif = (int)position.x - (chunkIndex.first + (chunkIndex.first >= 0 ? 0 : 1));
	int localX = std::abs(dif) % ChunkSizeX;

	int localy = std::abs(((int)(position.y) % ChunkSizeY));

	dif = (int)position.z - (chunkIndex.second + (chunkIndex.second >= 0 ? 0 : 1));
	int localz = std::abs(dif) % ChunkSizeZ;

	return ChunkPosistion{ localX, localy, localz };
}

std::pair<int, int> ChunkManager::WorldToChunkIndex(glm::vec3 position) const
{

	int mulX = (position.x < 0 ? static_cast<int>((static_cast<int>(position.x)) / ChunkSizeX) - 1 : (static_cast<int>(position.x) / ChunkSizeX));
	int mulZ = (position.z < 0 ? static_cast<int>((static_cast<int>(position.z)) / ChunkSizeZ) - 1 : (static_cast<int>(position.z) / ChunkSizeZ));
	int Chunkx = ChunkSizeX * mulX;
	int Chunkz = ChunkSizeZ * mulZ;

	return std::make_pair(Chunkx, Chunkz);
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

