#pragma once
#include <glm/glm.hpp>
#include <utility>
#include "../src/Minecraft/WorldGeneration.h"
#include "Europa/Components/BaseComponent.h"



class ChunkManager;
class ChunkMeshComponent;
class BlockInfromation;
class ChunkComponent final : public Eu::BaseComponent
{
public:

	ChunkComponent(glm::vec3 ChunkPosition, ChunkManager* pchunkManager, std::pair<int, int>chunkIndex, bool setActive);
	~ChunkComponent();

	bool IsBlockSolidInChunk(int yIndex, int xIndex, int zIndex) const;
	bool Addblock(glm::vec3 posTo, const uint8_t type);
	bool DestroyBlock(glm::vec3 posTo);
	inline glm::vec2 GetChunkPosition() { return m_ChunkPosition; }
	inline void SetChunkActiveState(bool isActive) { m_ChunkActive = isActive; }
	inline bool GetChunkActiveState() { return m_ChunkActive; }
	bool HasNeighbours(int xIndex, int yIndex, int zIndex);
	void UpdateMesh();
	bool IsBlockSolid(uint8_t blockType) const;
	void DellaocateData();
	void Allocate();

	void Start() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() const;


private:
	int chunkX = 16;
	int chunkZ = 16;
	int chunkY = 256;

	std::shared_ptr<ChunkMeshComponent> m_pChunkMesh = nullptr;
	ChunkGeneration m_ChunkGeneration;
	const ChunkManager* m_pChunkManager;
	std::pair<int, int> m_ChunkIndex;
	glm::vec3 m_ChunkPosition;
	bool m_ChunkActive;
};

#pragma once
