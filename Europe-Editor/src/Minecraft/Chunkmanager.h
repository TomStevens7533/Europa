#pragma once
#include <vector>
#include "Chunk.h"
#include "Europa/Core/TimeStep.h"
#include "Europa/camera/CameraController.h"
#include <map>
#include <utility>
#include <memory>
#include "Europa/Components/BaseComponent.h"
#include "../BlockJsonParser.h"
#include <thread>

#define ChunkSizeX 16
#define ChunkSizeY 256
#define ChunkSizeZ 16
#define ChunkMaxHeightGeneration 150
#define ChunkBaseTerrainHeight 30
#define ChunkWaterHeight 40
struct ChunkPosistion {
	int x;
	int y;
	int z;
};
class ChunkComponent;
class ChunkManager final : public Eu::BaseComponent
{
public:
	ChunkManager(Eu::PerspectiveCameraControllerComponent& CameraController);
	~ChunkManager();



	bool IsBlockSolidInChunk(std::pair<int, int> chunkInex, int xIndex, int yIndex, int zIndex) const;
	void Render();

	void Render() const override {};
	void Start() override;
	void Update() override;

	void FixedUpdate() override {};
	bool DeleteBlockAtPos(glm::vec3 posToLook);
	bool AddBlockAtPos(glm::vec3 posToLook, uint8_t type);


	std::pair<int, int> GetChunkIdx(glm::vec3 pos) const;
	ChunkPosistion WorldToLocalChunkPos(glm::vec3 position) const;
	std::pair<int, int> WorldToChunkIndex(glm::vec3 position) const;
private:
	void ReloadNeighbouringChunks(std::pair<int, int> chunkIndex);
	void UpdateChunksAroundPos();


private:


	std::map<std::pair<int, int>, std::shared_ptr<ChunkComponent>> m_ChunkVec;
	std::map<std::pair<int, int>, std::shared_ptr<ChunkComponent>> m_TempChunkMap;
	std::thread m_UpdateChunkThread;
	Eu::PerspectiveCameraControllerComponent* m_pCamera;

	//m_LevelJsonParser.ParseFile();
	unsigned int m_Seed{};
	int m_ChunkDistance = 2;
	DirectX::XMFLOAT3 m_OriginPos;
	std::atomic<float> m_OriginXPos;
	std::atomic<float> m_OriginYPos;
	std::atomic<float> m_OriginZPos;

	std::atomic<bool> m_IsShutdown = false;
	std::atomic<bool> m_IsCycleCreateDone = false;
	std::atomic<bool> m_IsCycleUpdateDone = true;

	//Mult
	std::mutex m_MutexUpdate;


	std::condition_variable cond;

};
