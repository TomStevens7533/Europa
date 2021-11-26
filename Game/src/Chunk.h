#pragma once
#include <glm/glm.hpp>
#include "BlockStruct.h"
#include <utility>
#include "WorldGeneration.h"



class ChunkManager;
class ChunkMesh;
class Chunk
{
public:

	Chunk(glm::vec3 ChunkPosition, ChunkManager* pchunkManager, std::pair<int,int>chunkIndex, bool setActive);
	~Chunk();

	void Render() const;
	bool IsBlockSolidInChunk(int yIndex, int xIndex, int zIndex) const;
	bool Addblock(glm::vec3 posTo, const BlockTypes type);
	bool DestroyBlock(glm::vec3 posTo);
	inline glm::vec2 GetChunkPosition() { return m_ChunkPosition; }
	inline void SetChunkActiveState(bool isActive) { m_ChunkActive = isActive; }
	inline bool GetChunkActiveState() { return m_ChunkActive; }
	bool HasNeighbours(int xIndex, int yIndex, int zIndex);
	void UpdateMesh();
	bool IsBlockSolid(BlockTypes blockType) const;

private:
	int chunkX = 16;
	int chunkZ = 16;
	int chunkY = 256;

	ChunkMesh* m_ChunkMesh;
	ChunkGeneration m_ChunkGeneration;
	ChunkManager* m_pChunkManager;
	std::pair<int, int> m_ChunkIndex;
	glm::vec3 m_ChunkPosition;
	bool m_ChunkActive;
};

